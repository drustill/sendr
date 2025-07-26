#pragma once

#include <atomic>
#include <thread>

#include "Using.h"

/**
 * @brief kqueue file-system watcher
 *
 * Opens directories, registers them with kqueue
 * and exposes an event loop to deliver events on
 * a single background thread
 *
 * @see man 2 kqueue
 * @see man 2 kevent
 */
class KQueueListener
{
  private:
    int kqfd;
    std::thread evloop;
    std::atomic<bool> running;

    WatchMap watched;
    Listeners listeners;

    /**
     * @brief Block in kevent() and emit to registered listeners.
     */
    void EventLoop();

  public:
    /**
     * @brief Create kqueue descriptor
     *
     * @note No directory is watched until WatchDir is called.
     */
    KQueueListener();


    /**
     * @brief Calls Stop and closes all file descriptors.
     */
    ~KQueueListener();


    /**
     * @brief Start the event loop on a thread.
     */
    void Start();


    /**
     * @brief Join the event loop thread
     */
    void Stop();


    /**
     * @brief Register a listener to receive event notifications.
     */
    void AddListener(EventListener* l);


    /**
     * @brief Begin watching a directory for changes.
     *
     * Get an event notification descriptor through open(O_EVTONLY)
     * and populates the kevent with EV_SET.
     *
     * EV_CLEAR resets the kevent automatically
     *
     * @see man 2 open    O_EVTONLY
     * @see man 2 kevent  EV_SET, EVFILT_VNODE, NOTE flags
     */
    int WatchDir(const std::string& path);
};
