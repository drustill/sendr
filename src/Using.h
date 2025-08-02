#pragma once

#include "EventListener.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

using Listeners = std::vector<EventListener *>;
using KEvent = struct kevent;
using WatchMap = std::map<int, std::string>;

struct Row;
using RowVector = std::vector<Row>;
