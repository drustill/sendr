#include "HttpClient.h"
#include "KQueueListener.h"
#include "LoggingListener.h"
#include "RowReader.h"

#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: main <url>.\n";
    exit(EXIT_FAILURE);
  }
  const std::string url = argv[1];
  HttpClient client;
  HttpResponse response = client.Get(url);

  if (response.status_code != 200) {
    std::cout << "URL " << url << " bad request!\n";
    std::cout << "Err " << response.status_code << "\n";
    exit(EXIT_FAILURE);
  }

  RowReader reader;
  RowVector rows = reader.Parse(response.body);

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
