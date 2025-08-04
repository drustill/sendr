#pragma once

#include "DownloaderInterface.h"
#include "KQueueListener.h"
#include "SearchClient.h"

#include <memory>
#include <string>

class Cli {
public:
  Cli(DownloaderInterface *downloader, const Config &config);
  int Run(int argc, char *argv[]);

private:
  void ShowUsage() const;
  void FetchBooks(const std::string &query);

  void StartInteractiveSession(RowVector &results);
  void DownloadAndSend(const Row &row);

  KQueueListener kq;
  SearchClient search;
  DownloaderInterface *downloader;
  const Config &config;
};
