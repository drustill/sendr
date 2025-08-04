#pragma once

#include "DownloaderInterface.h"
#include "HttpClient.h"

class Downloader : public DownloaderInterface {
public:
  explicit Downloader(std::string api_key);
  std::string GetDownloadUrl(const std::string &md5) const override;
  void Download(const std::string &md5, const std::string &path) const override;

private:
  std::string api_key;
  HttpClient client;
}
