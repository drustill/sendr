#pragma once

#include "DownloaderInterface.h"
#include <fstream>

class MockDownloader {
public:
  std::string GetDownloadUrl(const std::string &md5) const override {
    return "https://example.com/" + md5;
  }

  void Download(const std::string &md5,
                const std::string &path) const override {
    std::ofstream out(path);
    out << "Mock data : " << md5 << "\n";
    out.close();
  }
}
