#define CATCH_CONFIG_MAIN

#include "Utils.h"

#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <fstream>

TEST_CASE("split succeeds with format key=value", "[Utils]")
{
  auto tokens = util::split("EnvironmentKey=EnvironmentValue", "=");
  const auto& key = tokens[0];
  const auto& value = tokens[1];
  CHECK(key == "EnvironmentKey");
  CHECK(value == "EnvironmentValue");
}
