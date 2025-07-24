#include "KQueueListener.h"

#include <iostream>
#include <sys/event.h>

KQueueListener::KQueueListener() {}
KQueueListener::~KQueueListener() {}

void KQueueListener::EventLoop()
{
  int kq = kqueue();
  struct kevent evSet;
}
