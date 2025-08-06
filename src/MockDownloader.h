#pragma once

#include "DownloaderInterface.h"

#include <cstdio>
#include <fstream>
#include <string>

class MockDownloader : public DownloaderInterface {
public:
  std::string GetDownloadUrl(const std::string &md5) const override {
    return "https://example.com/" + md5;
  }

  void Download(const std::string &md5,
                const std::string &path) const override {
    std::remove(path.c_str());
    std::ofstream out(path);
    out << "Mock data : " << md5 << "\n";
    out.close();
  }
};
