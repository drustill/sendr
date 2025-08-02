#include "GumboHtmlParser.h"
#include "Utils.h"

#include <gumbo.h>
#include <algorithm>
#include <cctype>
#include <regex>
#include <sstream>
#include <functional>

  // std::regex md5_re(R"(^/md5/([0-9a-fA-F]{32}))");

RowVector RowReader::Parse(const std::string& html) const
{
  GumboOutput* output = gumbo_parse(html.c_str());
  RowVector vec;
  return vec;
};
