/// @brief kqueue file-system watcher
///
/// Opens directories, registers them with kqueue
/// and exposes an event loop to deliver events on
/// a single background thread
///
/// @see man 2 kqueue
/// @see man 2 kevent
#pragma once

#include <atomic>
#include <thread>

#include "Using.h"

class KQueueListener
{
  private:
    int kqfd;
    std::thread evloop;
    std::atomic<bool> running;


    WatchMap watched;
    Listeners listeners;


    /// Block in kevent() and emit to registered listeners.
    void EventLoop();

  public:
    /// Create kqueue descriptor.
    /// @note No directory is watched until WatchDir is called.
    KQueueListener();


    /// Stop event loop and close all file descriptors.
    ~KQueueListener();


    /// Start the event loop on a background thread.
    void Start();


    /// Join the event loop thread and stop processing events.
    void Stop();


    /// Register a listener to receive event notifications.
    void AddListener(EventListener* l);


    /// Begin watching a directory for changes.
    ///
    /// Opens the directory with O_EVTONLY and registers it
    /// using EV_SET with EVFILT_VNODE and NOTE_* flags.
    /// EV_CLEAR ensures edge-triggered behavior.
    /// @see man 2 open    (O_EVTONLY)
    /// @see man 2 kevent  (EV_SET, EVFILT_VNODE, NOTE flags)
    int WatchDir(const std::string& path);
};
