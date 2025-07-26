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

class EventListener {
public:
    virtual void OnEvent(const FileEvent& e) = 0;
    virtual ~EventListener() = default;
};
