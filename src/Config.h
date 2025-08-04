#pragma once

#include <optional>
#include <string>
#include <unordered_map>

class Config {
public:
  static const std::string default_path;

  explicit Config(const std::string &path = default_path);

  std::optional<std::string> Get(const std::string &key) const;
  bool Has(const std::string &key) const;

  static void WriteDefault(const std::string &path = default_path);

private:
  std::unordered_map<std::string, std::string> values;
};
