#include "KQueueListener.h"
#include "LoggingListener.h"
#include "RowReader.h"

#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: main <html filename>.\n";
    exit(EXIT_FAILURE);
  }
  const char* filename = argv[1];
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (!in) {
    std::cout << "File " << filename << " not found!\n";
    exit(EXIT_FAILURE);
  }

  std::ostringstream buffer;
  buffer << in.rdbuf();
  std::string html = buffer.str();

  RowReader reader;
  RowVector rows = reader.Parse(html);

  for (const auto& row : rows) {
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
