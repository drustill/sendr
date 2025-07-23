#pragma once

#include <string>

class EventListener
{
  public:
    virtual void OnEvent(const std::string e) = 0; // Change to a FileEvent object
    virtual ~EventListener() = default;
}
