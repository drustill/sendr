#pragma once

#include <atomic>
#include <set>

#include "Using.h"

class KQueueListener
{
  private:
    void EventLoop();
    int kqfd, dirfd;

    std::atomic<bool> running;
    Listeners listeners;
    std::set<std::string> seen;
  public:
    KQueueListener();
    ~KQueueListener();

    void Start();
    void Stop();
    void AddListener(Listener listener);
    void WatchDir(const std::string& path);
};
