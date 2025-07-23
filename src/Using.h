#pragma once

#include "EventListener.h"

#include <memory>
#include <string>
#include <vector>

using Listener = std::unique_ptr<EventListener>;
using Listeners = std::vector<Listener>;
