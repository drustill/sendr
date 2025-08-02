#pragma once

#include "Using.h"

#include <string>
#include <vector>

struct Row
{
  std::string md5, title, author, format, size;
};

class RowReader
{
  public:
    RowVector Parse(const std::string& html) const;
};
