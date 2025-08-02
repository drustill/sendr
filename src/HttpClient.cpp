#include "HttpClient.h"

#include <curl/curl.h>
#include <stdexcept>

namespace {
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
  auto *body = static_cast<std::string *>(userp);
  body->append(static_cast<char *>(contents), size * nmemb);
  return size * nmemb;
}
} // namespace

HttpClient::HttpClient() { curl_global_init(CURL_GLOBAL_ALL); }

HttpClient::~HttpClient() { curl_global_cleanup(); }

HttpResponse HttpClient::Get(const std::string &url) const {
  return Request(url);
}

HttpResponse HttpClient::Request(const std::string &url) const {
  CURL *curl = curl_easy_init();
  if (!curl) {
    throw std::runtime_error("Bad CURL");
  }

  HttpResponse response;

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.body);

  CURLcode res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    curl_easy_cleanup(curl);
    throw std::runtime_error(std::string("Bad request ") +
                             curl_easy_strerror(res));
  }

  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.status_code);
  curl_easy_cleanup(curl);
  return response;
};
