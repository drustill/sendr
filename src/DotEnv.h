#pragma once

#include <string>
#include <vector>

class DotEnv
{
  public:
    DotEnv();
    ~DotEnv();

    void LoadDotEnv();

  private:
    std::string path = ".env";
    std::vector<std::string> split(const std::string& s, const std::string& delimiter);
};
