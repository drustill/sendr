#include "KQueueListener.h"

#include <iostream>
#include <sys/event.h>

void KQueueListener::EventLoop()
{
  int kq = kqueue();
  struct kevent evSet;
  EV_SET(&evSet,
}
