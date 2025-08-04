#include "Config.h"
#include "Utils.h"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

const std::string Config::default_path =
    std::string(std::getenv("HOME")) + "/.config/sendr/sendr.conf";

Config::Config(const std::string &path) {
  std::ifstream f(path);
  if (!f.is_open()) {
    std::cerr << "[WARN] sendr.conf not found! " << path << "\n";
    return;
  }

  std::string line;
  while (std::getline(f, line)) {
    util::ltrim(line);
    util::rtrim(line);
    util::strip_comments(line);
    if (line.empty())
      continue;

    size_t eq = line.find('=');
    if (eq == std::string::npos)
      continue;
    std::string key = line.substr(0, eq);
    std::string val = line.substr(eq + 1);

    util::ltrim(key);
    util::ltrim(val);
    util::rtrim(key);
    util::rtrim(val);

    values[key] = val;
  }
}

std::optional<std::string> Config::Get(const std::string &key) const {
  auto it = values.find(key);
  if (it == values.end())
    return nullptr;
  return it->second;
}

bool Config::Has(const std::string &key) const { return values.count(key) > 0; }

void Config::WriteDefault(const std::string &path) {
  std::cout << path << "\n";
  std::filesystem::create_directories(
      std::filesystem::path(path).parent_path());
  std::ofstream out(path);

  if (!out.is_open()) {
    std::cerr << "[ERROR] Cannot create default config!\n";
    return;
  }

  out << R"(# Configure sendr

# annas archive
annas_archive_key =

# mail
smtp_host =
smtp_port =
smtp_user =
smtp_pass =
kindle_email =

# library
download_dir =
)";
  out.close();
  std::cout << "[INFO] Wrote default config to: " << path << "\n";
}
