#pragma once

#include "EventListener.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

using Listeners = std::vector<EventListener*>;
using KEvent = struct kevent;
using WatchMap = std::map<int, std::string>;

struct Node;

using NodePtr = std::unique_ptr<Node>;
