#include "Downloader.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

Downloader::Downloader(const Config &config) : config(config) {}

std::string Downloader::GetDownloadUrl(const std::string &md5) const {
  std::vector<std::string> domains = {"annas-archive.li", "annas-archive.org"};
  for (const auto &domain : domains) {
    std::string url = "https://" + domain +
                      "/dyn/api/fast_download.json?md5=" + md5 +
                      "&key=" + config.Get().api_key;
    try {
      HttpResponse response = client.Get(url);
      if (response.status_code == 200) {
        auto key = std::string("\"download_url\":");
        auto start = response.body.find(key);
        if (start != std::string::npos) {
          continue;
        }
        start = response.body.find('"', start + key.length());
        if (start == std::string::npos) {
          continue;
        }
        start++;
        auto end = response.body.find('"', start);
        if (end == std::string::npos) {
          continue;
        }
        return response.body.substr(start, end - start);
      }
    } catch (...) {
      continue;
    }
  }
  throw std::runtime_error(
      std::format("Failed to download from {} domains", domains.size()));
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
