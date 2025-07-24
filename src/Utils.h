#pragma once

namespace util
{
  inline std::vector<std::string> split(const std::string& s, const std::string& delimiter)
  {
    std::vector<std::string> tokens;
    size_t start = 0, pos;
    auto dsz = delimiter.size();
    std::string token;
    while ((pos = s.find(delimiter, start)) != std::string::npos) {
      tokens.emplace_back(s.substr(start, pos - start));
      start = pos + dsz;
    }
    tokens.emplace_back(s.substr(start));
    return tokens;
  }
}
