#define CATCH_CONFIG_MAIN

#include "DotEnv.h"
#include "Utils.h"

#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <fstream>

int OVERWRITE = 1;

struct EnvScope
{
  private:
    const char* key;
    std::string old;

  EnvScope(const char* k) : key(k), old(std::getenv(k)?std::string(std::getenv(k)):"") {}
  ~EnvScope()
  {
    if (old.empty()) unsetenv(key);
    else setenv(key, old.c_str(), OVERWRITE);
  }
};

TEST_CASE("split succeeds with format key=value", "[DotEnv]")
{
  DotEnv dotenv;
  auto tokens = util::split("EnvironmentKey=EnvironmentValue", "=");
  const auto& key = tokens[0];
  const auto& value = tokens[1];
  CHECK(key == "EnvironmentKey");
  CHECK(value == "EnvironmentValue");
}
