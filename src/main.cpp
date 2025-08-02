#include "KQueueListener.h"
#include "LoggingListener.h"
#include "SearchClient.h"

#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: main <query>.\n";
    exit(EXIT_FAILURE);
  }

  SearchClient client;
  SearchParams params;

  params.query = argv[1];
  params.max_results = 5;
  params.lang = "en";

  RowVector rows = client.Search(params);

  for (const auto &row : rows) {
    std::cout << "MD5: " << row.md5 << "\n";
    std::cout << "Title: " << row.title << "\n";
    std::cout << "Author: " << row.author << "\n";
    std::cout << "Publisher: " << row.publisher << "\n";
    std::cout << "Year: " << row.year << "\n";
    std::cout << "Lang: " << row.lang << "\n";
    std::cout << "Format: " << row.format << "\n";
    std::cout << "Size: " << row.size << "\n";
    std::cout << "-------------------------\n";
  }

  return 0;
};

// int main()
// {
//   KQueueListener kq;
//   LoggingListener ll;

//   kq.AddListener(&ll);
//   std::string dir = std::string(std::getenv("HOME")) + "/KQueueListenerTest";
//   kq.WatchDir(dir);

//   kq.Start();

//   std::cout << "Watching " << dir << "\n- press <Ctrl+C> to quit.\n";
//   std::cin.get();

//   kq.Stop();
//   std::cout << "Stopped.\n";
//   return 0;
// };
