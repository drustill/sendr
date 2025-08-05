#include "Cli.h"
#include "LoggingListener.h"

#include <chrono>
#include <iostream>
#include <limits>
#include <thread>

Cli::Cli(DownloaderInterface *downloader, const Config &config)
    : downloader(downloader), config(config) {}

int Cli::Run(int argc, char *argv[]) {
  if (argc < 2) {
    ShowUsage();
    return 1;
  }

  std::string cmd = argv[1];
  if (cmd == "get") {
    std::string query;
    for (int i = 2; i < argc; ++i) {
      if (!query.empty())
        query += " ";
      query += argv[i];
    }

    FetchBooks(query);
    return 0;
  }

  ShowUsage();
  return 1;
}

void Cli::ShowUsage() const {
  std::cout << "Usage: sendr get <search query>...\n";
}

void Cli::FetchBooks(const std::string &query) {
  SearchParams params;
  params.query = query;
  params.max_results = 5;

  try {
    RowVector results = search.Search(params);
    if (results.empty()) {
      std::cout << "Nothing matched your query!\n";
      return;
    }
    StartInteractiveSession(results);
  } catch (const std::exception &e) {
    std::cerr << "Error : " << e.what() << "\n";
  }
}

void Cli::StartInteractiveSession(RowVector &results) {
  std::cout << "Select a book to download & send\n";
  for (size_t i = 0; i < results.size(); ++i) {
    std::cout << i + 1 << ". " << results[i].title << " by "
              << results[i].author << "\n";
  }

  int pick = 0;
  while (true) {
    std::cout << "Pick (1-" << results.size() << "): ";
    std::cin >> pick;
    if (pick >= 1 && (size_t)pick <= results.size())
      break;
    std::cout << "Bad choice. Try again\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  const Row &chosen = results[pick - 1];
  DownloadAndSend(chosen);
}

void Cli::DownloadAndSend(const Row &row) {
  std::cout << "Downloading " << row.title << "...\n";

  kq.AddListener(new LoggingListener());
  std::string dir = config.Get().download_dir;

  kq.WatchDir(dir);
  kq.Start();

  downloader->Download(row.md5, dir + "temp.txt");

  kq.Stop();
}
