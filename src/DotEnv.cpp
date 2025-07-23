#include "DotEnv.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

void DotEnv::LoadDotEnv()
{
  std::ifstream dotfile(path);
  if (!dotfile.is_open())
    return;

  std::string line;
  while (std::getline(dotfile, line))
  {
    auto tokens = split(line, "=");
    const auto& key = tokens[0];
    const auto& value = tokens[0];
    setenv(key.c_str(), value.c_str(), 1);
  }
}

std::vector<std::string> DotEnv::split(const std::string& s, const std::string& delimiter)
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
