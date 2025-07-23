#define CATCH_CONFIG_MAIN
#include "DotEnv.h"

#include <catch2/catch.hpp>

#include <cstdint>
#include <fstream>

int OVERWRITE = 1

struct EnvScope
{
  private:
    const char* key;
    std::string old;

  EnvScope(const char* k) : key(k), old(std::getenv(k)?std::string(std::getenv(k)):"") {}
  ~EnvScope()
  {
    if (old.empty()) std::unsetenv(key);
    else std::setenv(key, old.c_str(), OVERWRITE);
  }
}

TEST_CASE("split succeeds with format key=value", "[DotEnv]")
{
  DotEnv dotenv;
  auto key, value = dotenv.split("EnvironmentKey=EnvironmentValue", "=");
  CHECK(key == "EnvironmentKey");
  CHECK(value == "EnvironmentValue");
}
