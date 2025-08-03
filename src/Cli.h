#pragma once

#include "KQueueListener.h"
#include "SearchClient.h"

#include <memory>
#include <string>

class Cli {
public:
  int Run(int argc, char *argv[]);

private:
  void ShowUsage() const;
  void FetchBooks(const std::string &query);

  void StartInteractiveSession(RowVector &results);
  void DownloadAndSend(const Row &row);

  SearchClient search;
  KQueueListener kq;
};
