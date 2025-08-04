#pragma once

#include <optional>
#include <string>
#include <unordered_map>

struct Settings {
  std::string api_key;
  std::string smtp_user;
  std::string smtp_pass;
  std::string kindle_email;
  std::string download_dir;
};

class Config {
public:
  static const std::string default_path;

  explicit Config(const std::string &path = default_path);

  const Settings &Get() const { return settings; }

  static void WriteDefault(const std::string &path = default_path);

private:
  Settings settings;
};
