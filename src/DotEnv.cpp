#include "DotEnv.h"
#include "Utils.h"

#include <fstream>
#include <iostream>

DotEnv::DotEnv() {}
DotEnv::~DotEnv() {}

void DotEnv::LoadDotEnv()
{
  std::ifstream dotfile(path);
  if (!dotfile.is_open())
    return;
  std::string line;
  while (std::getline(dotfile, line))
  {
    auto tokens = util::split(line, "=");
    const auto& key = tokens[0];
    const auto& value = tokens[0];
    setenv(key.c_str(), value.c_str(), 1);
  }
}
