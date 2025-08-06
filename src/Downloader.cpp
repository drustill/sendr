#include "Downloader.h"

#include <fstream>
#include <iostream>
#include <string>

Downloader::Downloader(const Config &config) : config(config) {}

std::string Downloader::GetDownloadUrl(const std::string &md5) const {
  std::string url =
      "https://annas-archive.org/dyn/api/fast_download.json?md5=" + md5 +
      "&key=" + config.Get().api_key;

  HttpResponse response = client.Get(url);

  auto key = std::string("\"download_url\":");
  auto start = response.body.find(key);
  if (start == std::string::npos) {
    throw std::runtime_error("Missing download_url in response");
  }

  start = response.body.find('"', start + key.length());
  if (start == std::string::npos) {
    throw std::runtime_error("Malformed download_url key");
  }
  start++;

  auto end = response.body.find('"', start);
  if (end == std::string::npos) {
    throw std::runtime_error("Unterminated download_url value");
  }

  return response.body.substr(start, end - start);
}

void Downloader::Download(const std::string &md5,
                          const std::string &path) const {
  std::remove(path.c_str());
  std::string url = GetDownloadUrl(md5);

  HttpResponse response = client.Get(url);
  if (response.status_code != 200) {
    throw std::runtime_error("HTTPClient Fail : " + md5);
    return;
  }

  std::ofstream out(path, std::ios::binary);
  out.write(response.body.data(), response.body.size());
  out.close();
}
