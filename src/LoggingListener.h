#include "EventListener.h"
#include <iostream>

class LoggingListener : public EventListener {
public:
  void OnEvent(const FileEvent &e) override {
    std::cout << "[LOG] ";
    switch (e.action) {
    case FileAction::Created:
      std::cout << "Created ";
      break;
    case FileAction::Modified:
      std::cout << "Modified ";
      break;
    case FileAction::Deleted:
      std::cout << "Deleted ";
      break;
    case FileAction::Renamed:
      std::cout << "Renamed ";
      break;
    }
    std::cout << e.path;
    if (e.action == FileAction::Renamed)
      std::cout << " (was " << e.oldPath << ")";
    std::cout << "\n";
  }
};
