#pragma once

#include "DownloaderInterface.h"
#include "SearchClient.h"

#include <memory>
#include <optional>
#include <string>
#include <unordered_set>

struct SearchOptions {
  int max_results = 5;
  std::vector<std::string> formats = {"epub"};
  bool dry_run = false;
  std::string query;
  bool query_given = false;
};

class Cli {
public:
  Cli(DownloaderInterface *downloader, const Config &config);
  ~Cli();
  int Run(int argc, char *argv[]);
  static void ShowUsage();

private:
  SearchClient search;
  DownloaderInterface *downloader;
  const Config &config;

  static inline const std::unordered_set<std::string> SupportedFormats = {
      "epub", "pdf", "mobi", "azw3"};

  int RunSearch(const SearchOptions &opts);
  int HandleSearchCommand(int argc, char *argv[]);

  void StartInteractiveSession(RowVector &results);
  void DownloadAndSend(const Row &row);

  void PrintBookResults(const RowVector &results);
};
