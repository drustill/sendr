#pragma once

#include <optional>
#include <string>
#include <unordered_map>

struct Settings {
  std::string api_key;
  std::string smtp_user;
  std::string smtp_pass;
  std::string smtp_host;
  int smtp_port;
  std::string kindle_email;
  std::string download_dir;
};

class Config {
public:
  static const std::string default_path;
  static const std::string default_download_dir;
  static const std::string default_smtp_host;
  static const int default_smtp_port;

  explicit Config(const std::string &path = default_path);

  const Settings &Get() const { return settings; }

  static void WriteDefault(const std::string &path = default_path);

private:
  Settings settings;
};
