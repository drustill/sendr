#pragma once

#include <string>

enum class FileAction {
    Created,
    Modified,
    Deleted,
    Renamed
};

struct FileEvent {
    std::string    path;
    FileAction     action;
    std::string    oldPath{};
};

/**
 * @brief Abstract Base Class for event listeners
 *
 * Implementing classes can be registered as listeners
 * to a KQueueListener
 */
class EventListener {
public:
    virtual void OnEvent(const FileEvent& e) = 0;
    virtual ~EventListener() = default;
};
