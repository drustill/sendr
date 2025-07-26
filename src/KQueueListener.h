#pragma once

#include <atomic>
#include <thread>

#include "Using.h"

class KQueueListener
{
  private:
    int kqfd, dirfd;

    std::atomic<bool> running;
    std::thread evloop;

    Listeners listeners;
    WatchMap watched;

    void EventLoop();

  public:
    KQueueListener();
    ~KQueueListener();

    void Start();
    void Stop();
    void AddListener(EventListener* l);
    int WatchDir(const std::string& path);
};
