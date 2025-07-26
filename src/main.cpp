#include "KQueueListener.h"
#include "LoggingListener.h"

#include <iostream>

int main()
{
  KQueueListener kq;
  LoggingListener ll;

  kq.AddListener(&ll);
  std::string dir = std::string(std::getenv("HOME")) + "/KQueueListenerTest";
  kq.WatchDir(dir);

  kq.Start();

  std::cout << "Watching " << dir << "\n- press <Ctrl+C> to quit.\n";
  std::cin.get();

  kq.Stop();
  std::cout << "Stopped.\n";
  return 0;
};
