#pragma once

#include <string>

class DownloaderInterface {
public:
  virtual ~DownloaderInterface() = default;
  virtual std::string GetDownloadUrl(const std::string &md5) const = 0;
  virtual void Download(const std::string &md5,
                        const std::string &path) const = 0;
}
