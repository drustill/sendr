#include "Cli.h"
#include "LoggingListener.h"
#include "Mailer.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <thread>

#define CYAN "\033[1;36m"
#define GREY "\033[2;37m"
#define RESET "\033[0m"

Cli::Cli(DownloaderInterface *downloader, const Config &config)
    : downloader(downloader), config(config) {}

Cli::~Cli() {}

void Cli::ShowUsage() {
  std::cout << R"(Usage:
  sendr search [options] <search terms…>
  sendr daemon <start|stop|restart|status>

Fetch Options:
  --max <N>           limit to top N matches (default: 1)
  --format <fmt>      desired format: epub, pdf (default: epub)
  --dry-run           print download URL, don’t download or send
  --query <query>     search query in quotes

Daemon Commands:
  start               launch the daemon process
  stop                stop the running daemon
  status              print daemon status (running or not)
  restart             restart the daemon
)";
}

int Cli::Run(int argc, char *argv[]) {
  if (argc < 2) {
    ShowUsage();
    return 1;
  }

  std::string cmd = argv[1];
  if (cmd == "search") {
    return HandleSearchCommand(argc - 2, argv + 2);
  }

  ShowUsage();
  return 1;
}

int Cli::HandleSearchCommand(int argc, char *argv[]) {
  SearchOptions opts;

  for (int i = 0; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "--max" && i + 1 < argc) {
      opts.max_results = std::stoi(argv[++i]);
    } else if (arg == "--format" && i + 1 < argc) {
      std::string fmt = argv[++i];
      opts.formats.clear();
      std::stringstream ss(fmt);
      std::string item;
      while (std::getline(ss, item, ',')) {
        if (SupportedFormats.contains(item)) {
          opts.formats.push_back(item);
        }
      }
    } else if (arg == "--dry-run") {
      opts.dry_run = true;
    } else if (arg == "--query" && i + 1 < argc) {
      opts.query = argv[++i];
      opts.query_given = true;
    } else {
      std::cerr << "Unknown flag: " << arg << "\n";
      ShowUsage();
      return 1;
    }
  }

  if (!opts.query_given) {
    std::cout << "Enter your search query: ";
    std::getline(std::cin, opts.query);
  }

  return RunSearch(opts);
}

int Cli::RunSearch(const SearchOptions &opts) {
  SearchParams params;
  params.query = opts.query;
  params.max_results = opts.max_results;
  params.formats = opts.formats;

  try {
    RowVector results = search.Search(params);
    if (opts.dry_run) {
      PrintBookResults(results);
      return 0;
    }

    StartInteractiveSession(results);
    return 0;

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}

static std::string Truncate(const std::string &s, size_t width) {
  if (s.size() <= width)
    return s;
  return s.substr(0, width - 3) + "...";
}

void Cli::PrintBookResults(const RowVector &results) {
  std::cout << GREY << "\nFound " << results.size() << " result"
            << (results.size() > 1 ? "s" : "") << RESET << ":\n\n";

  std::cout << CYAN << std::setw(4) << "No." << std::setw(42) << "Title"
            << std::setw(26) << "Author" << std::setw(20) << "Publisher"
            << std::setw(6) << "Year" << std::setw(6) << "Lang" << std::setw(8)
            << "Format" << std::setw(8) << "Size"
            << "\n";

  std::cout << GREY << std::string(120, '-') << RESET << "\n";

  int i = 1;
  for (const auto &row : results) {
    std::cout << std::setw(4) << i++ << std::setw(42) << Truncate(row.title, 40)
              << std::setw(26) << Truncate(row.author, 24) << std::setw(20)
              << Truncate(row.publisher, 12) << std::setw(6)
              << Truncate(row.year, 8) << std::setw(6) << row.lang
              << std::setw(8) << row.format << std::setw(8) << row.size << "\n";
  }
  std::cout << "\n";
}

void Cli::StartInteractiveSession(RowVector &results) {
  PrintBookResults(results);

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
  std::string path = config.Get().download_dir + row.title + "." + row.format;

  std::cout << "\nPreparing to download and send:\n"
            << "  Title     : " << row.title << "\n"
            << "  Author    : " << row.author << "\n"
            << "  Publisher : " << row.publisher << "\n"
            << "  Year      : " << row.year << "\n"
            << "  Format    : " << row.format << "\n"
            << "  Size      : " << row.size << "\n\n"
            << "Saving to: " << path << "\n"
            << "File will be sent after download completes.\n\n";

  try {
    downloader->Download(row.md5, path);
    std::cout << "Sent!\n\n";
  } catch (const std::exception &e) {
    std::cerr << "[ERROR] Failed to download file: " << e.what() << "\n";
  }
}
