#pragma once

#include "CommunicationLogger.h"
#include "Config.h"

#include <openssl/err.h>
#include <openssl/ssl.h>
#include <string>

struct EmailMessage {
  std::string from;
  std::string to;
  std::string subject;
  std::string body;
};

enum class SmtpError {
  Ok = 0,
  GetAddrInfoError = -1,
  SocketCreationError = -2,
  ConnectError = -3,
  RecvError = -4,
};

class SmtpClient {
public:
  SmtpClient(const Config &config);
  ~SmtpClient();

  static constexpr size_t Base64LineLimit = 76;
  static constexpr size_t ResponseBufferSize = 2048;

  CommunicationLogger logger;

  SmtpError Connect();
  void StartTLS();
  void Authenticate();
  void SendMail(const EmailMessage &msg, const std::string &attachment);
  void Disconnect();

private:
  int socketfd;
  SSL_CTX *ssl_ctx;
  SSL *ssl;

  const Config config;

  void SendLine(const std::string &data);
  void UpgradeToTLS();
  std::string ReadResponse();
  std::string ReadResponseTLS();
  std::string BuildMIMEMessage(const EmailMessage &msg,
                               const std::string &attachment);
};
