#pragma once

#include "DownloaderInterface.h"
#include <fstream>
#include <string>

class MockDownloader : public DownloaderInterface {
public:
  explicit MockDownloader(const Config &config);
  std::string GetDownloadUrl(const std::string &md5) const override {
    return "https://example.com/" + md5;
  }

  void Download(const std::string &md5,
                const std::string &path) const override {
    std::ofstream out(path);
    out << "Mock data : " << md5 << "\n";
    out.close();
  }

private:
  std::string api_key;
};
