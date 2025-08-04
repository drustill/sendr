#include "KQueueListener.h"

#include <fcntl.h>
#include <iostream>
#include <sys/event.h>
#include <unistd.h>

namespace {
// Note that NOTE_WRITE will be the fflag
// for file creates on a watched directory
FileAction actionFromFFlags(unsigned long fflags) {
  if (fflags & NOTE_DELETE)
    return FileAction::Deleted;
  if (fflags & NOTE_RENAME)
    return FileAction::Renamed;
  if (fflags & NOTE_LINK)
    return FileAction::Created;
  if (fflags & (NOTE_WRITE | NOTE_EXTEND | NOTE_ATTRIB))
    return FileAction::Modified;

  perror("actionFromFFlags : unrecognized NOTE");
  return FileAction::Modified;
}
} // namespace

KQueueListener::KQueueListener() : kqfd(-1), running(false) {
  kqfd = kqueue();
  if (kqfd == -1) {
    perror("KQueueListener Constructor : Bad File Descriptor");
    return;
  }
}

KQueueListener::~KQueueListener() {
  Stop();
  if (kqfd >= 0)
    close(kqfd);
  for (auto &[fd, _] : watched)
    close(fd);
}

void KQueueListener::EventLoop() {
  KEvent event;
  while (running.load()) {
    int ev = kevent(kqfd, nullptr, 0, &event, 1, nullptr);
    if (ev < 0)
      break;

    if (ev > 0) {
      auto it = watched.find(event.ident);
      if (it == watched.end())
        continue;

      const std::string &path = it->second;
      FileAction action = actionFromFFlags(event.fflags);

      for (auto *l : listeners) {
        l->OnEvent(FileEvent{path, action});
      }
    }
  }
}

void KQueueListener::Start() {
  running = true;
  evloop = std::thread(&KQueueListener::EventLoop, this);
}

void KQueueListener::Stop() {
  if (!running)
    return;

  running = false;
  KEvent evSet;
  EV_SET(&evSet, 0, EVFILT_USER, EV_ENABLE | EV_ADD | EV_ONESHOT, NOTE_TRIGGER,
         0, nullptr);
  kevent(kqfd, &evSet, 1, NULL, 0, NULL);

  if (evloop.joinable())
    evloop.join();
}

void KQueueListener::AddListener(EventListener *l) { listeners.push_back(l); }

int KQueueListener::WatchDir(const std::string &path) {
  int dirfd = open(path.c_str(), O_EVTONLY);
  if (dirfd < 0) {
    perror(("KQueueListener::WatchDir : Bad open " + path).c_str());
    return dirfd;
  }
  watched[dirfd] = path;
  KEvent evSet;
  EV_SET(&evSet, dirfd, EVFILT_VNODE, EV_ADD | EV_CLEAR,
         NOTE_WRITE | NOTE_EXTEND | NOTE_ATTRIB | NOTE_LINK | NOTE_RENAME |
             NOTE_DELETE,
         0, nullptr);
  if (kevent(kqfd, &evSet, 1, NULL, 0, NULL) < 0) {
    perror("KQueueListener::WatchDir : Bad kevent register");
    return -1;
  }

  return 0;
}
