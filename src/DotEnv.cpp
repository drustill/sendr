#include "DotEnv.h"

#include <cstdlib>
#include <iostream>

void DotEnv::LoadDotEnv()
{
  std::ifstream dotfile(env);
  if !(dotfile.is_open())
    return

  std::string line;
  while (std::getline(dotfile, line))
  {
    key, value = split(line, "=");
    std::setenv(key, value)
  }
}

std::vector<std::string> DotEnv::split(const std::string& s, const std::string& delimiter)
{
  std::vector<std::string> tokens;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
      token = s.substr(0, pos);
      tokens.push_back(token);
      s.erase(0, pos + delimiter.length());
  }
  tokens.push_back(s);

  return tokens;
}
