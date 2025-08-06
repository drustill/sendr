#include "SmtpClient.h"
#include "Utils.h"

#include <arpa/inet.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <netdb.h>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>

SmtpClient::SmtpClient(const Config &config)
    : config(config), socketfd(-1), ssl_ctx(nullptr), ssl(nullptr) {}

SmtpClient::~SmtpClient() { Disconnect(); }

SmtpError SmtpClient::Connect() {
  logger.Reset();
  struct addrinfo hints{}, *res;

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  std::string host = config.Get().smtp_host;
  int port = config.Get().smtp_port;

  int status =
      getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &res);
  if (status != 0) {
    logger.Log(CommunicationLogger::ErrPrefix, strerror(status));
    return SmtpError::GetAddrInfoError;
  }

  socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (socketfd < 0) {
    logger.Log(CommunicationLogger::ErrPrefix, strerror(status));
    freeaddrinfo(res);
    return SmtpError::SocketCreationError;
  }

  if (connect(socketfd, res->ai_addr, res->ai_addrlen) < 0) {
    logger.Log(CommunicationLogger::ErrPrefix, strerror(errno));
    close(socketfd);
    freeaddrinfo(res);
    return SmtpError::ConnectError;
  }

  freeaddrinfo(res);

  std::ostringstream oss;
  oss << "OK " << host << ":" << port;
  logger.Log(CommunicationLogger::LogPrefix, oss.str());

  std::string response = ReadResponse();
  logger.Log(CommunicationLogger::LogPrefix, response);

  return SmtpError::Ok;
}

std::string SmtpClient::ReadResponse() {
  char buffer[ResponseBufferSize];
  ssize_t bytes = recv(socketfd, buffer, sizeof(buffer) - 1, 0);
  if (bytes < 0) {
    throw std::runtime_error(strerror(errno));
  }
  buffer[bytes] = '\0';
  return std::string(buffer);
}

std::string SmtpClient::ReadResponseTLS() {
  char buffer[ResponseBufferSize];
  int bytes = SSL_read(ssl, buffer, sizeof(buffer) - 1);
  if (bytes <= 0) {
    throw std::runtime_error(strerror(errno));
  }
  buffer[bytes] = '\0';
  return std::string(buffer);
}

void SmtpClient::Disconnect() {
  if (ssl)
    SSL_free(ssl);
  if (ssl_ctx)
    SSL_CTX_free(ssl_ctx);
  if (socketfd != -1)
    close(socketfd);
}

void SmtpClient::SendLine(const std::string &data) {
  std::string line = data + "\r\n";
  if (ssl) {
    SSL_write(ssl, line.c_str(), line.size());
  } else if (send(socketfd, line.c_str(), line.size(), 0) < 0) {
    throw std::runtime_error(strerror(errno));
  }
  logger.Log(CommunicationLogger::LogPrefix,
             "Sent " + std::to_string(line.size()));
}

void SmtpClient::StartTLS() {
  SendLine("EHLO sendr.com");
  std::string response = ReadResponse();
  logger.Log(CommunicationLogger::LogPrefix, response);

  if (response.find("STARTTLS") == std::string::npos) {
    throw std::runtime_error("STARTTLS not supported!");
  }

  SendLine("STARTTLS");
  std::string starttls_response = ReadResponse();
  logger.Log(CommunicationLogger::LogPrefix, starttls_response);

  if (!starttls_response.starts_with("220")) {
    throw std::runtime_error("STARTTLS rejected!");
  }

  UpgradeToTLS();
}

void SmtpClient::UpgradeToTLS() {
  SSL_library_init();
  OpenSSL_add_all_algorithms();
  SSL_load_error_strings();

  ssl_ctx = SSL_CTX_new(TLS_client_method());
  if (!ssl_ctx) {
    throw std::runtime_error("SSL_CTX");
  }

  ssl = SSL_new(ssl_ctx);
  if (!ssl) {
    throw std::runtime_error("SSL");
  }

  SSL_set_fd(ssl, socketfd);

  if (SSL_connect(ssl) <= 0) {
    ERR_print_errors_fp(stderr);
    throw std::runtime_error("SSL_connect");
  }

  logger.Log(CommunicationLogger::LogPrefix, "TLS OK");
}

void SmtpClient::Authenticate() {
  std::string user = config.Get().smtp_user;
  std::string pass = config.Get().smtp_pass;

  SSL_write(ssl, "AUTH LOGIN\r\n", 12);
  logger.Log(CommunicationLogger::LogPrefix, "AUTH LOGIN");

  std::string auth_response = ReadResponseTLS();
  logger.Log(CommunicationLogger::LogPrefix, auth_response);
  if (!auth_response.starts_with("334")) {
    throw std::runtime_error("AUTH");
  }

  std::string b64_user = util::base64_encode(user) + "\r\n";
  SSL_write(ssl, (b64_user).c_str(), b64_user.size());
  logger.Log(CommunicationLogger::LogPrefix, "<base64_user>");

  std::string user_response = ReadResponseTLS();
  logger.Log(CommunicationLogger::LogPrefix, user_response);
  if (!user_response.starts_with("334")) {
    throw std::runtime_error("USERNAME");
  }

  std::string b64_pass = util::base64_encode(pass) + "\r\n";
  SSL_write(ssl, (b64_pass).c_str(), b64_pass.size());
  logger.Log(CommunicationLogger::LogPrefix, "<base64_pass>");

  std::string pass_response = ReadResponseTLS();
  logger.Log(CommunicationLogger::LogPrefix, pass_response);
  if (!pass_response.starts_with("235")) {
    throw std::runtime_error("LOGIN FAIL");
  }
}

void SmtpClient::SendMail(const EmailMessage &msg,
                          const std::string &attachment) {
  SendLine("MAIL FROM:<" + msg.from + ">");
  logger.Log(CommunicationLogger::LogPrefix, ReadResponseTLS());

  SendLine("RCPT TO:<" + msg.to + ">");
  logger.Log(CommunicationLogger::LogPrefix, ReadResponseTLS());

  SendLine("DATA");
  std::string response = ReadResponseTLS();
  logger.Log(CommunicationLogger::LogPrefix, response);
  if (!response.starts_with("354")) {
    throw std::runtime_error("DATA");
  }

  std::string email = BuildMIMEMessage(msg, attachment);

  SendLine(email);
  logger.Log(CommunicationLogger::LogPrefix, ReadResponseTLS());
}

std::string SmtpClient::BuildMIMEMessage(const EmailMessage &msg,
                                         const std::string &attachment) {
  std::ifstream file(attachment, std::ios::binary);
  if (!file) {
    throw std::runtime_error(attachment);
  }

  std::ostringstream email;
  std::string boundary = "SENDR_BOUNDARY";
  std::string filename = std::filesystem::path(attachment).filename().string();

  std::ostringstream file_content_readable;
  file_content_readable << file.rdbuf();
  std::string encoded = util::base64_encode(file_content_readable.str());

  email << "From: " << msg.from << "\r\n";
  email << "To: " << msg.to << "\r\n";
  email << "Subject: " << msg.subject << "\r\n";
  email << "MIME-Version: 1.0\r\n";
  email << "Content-Type: multipart/mixed; boundary=" << boundary << "\r\n";
  email << "\r\n";
  email << "--" << boundary << "\r\n";
  email << "Content-Type: text/plain; charset=UTF-8\r\n";
  email << "Content-Transfer-Encoding: 7bit\r\n";
  email << "\r\n";
  email << msg.body << "\r\n";
  email << "--" << boundary << "\r\n";
  email << "Content-Type: application/octet-stream; name=\"" << filename
        << "\"\r\n";
  email << "Content-Transfer-Encoding: base64\r\n";
  email << "Content-Disposition: attachment; filename=\"" << filename
        << "\"\r\n";
  email << "\r\n";

  for (size_t i = 0; i < encoded.length(); i += Base64LineLimit) {
    email << encoded.substr(i, Base64LineLimit) << "\r\n";
  }
  email << "--" << boundary << "--\r\n";
  email << "\r\n.\r\n";

  return email.str();
}
