#include "Config.h"
#include "Utils.h"

#include <cstdlib>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>

const std::string Config::default_path =
    std::string(std::getenv("HOME")) + "/.config/sendr/sendr.conf";

const std::string Config::default_download_dir =
    std::string(std::getenv("HOME")) + "/sendr/lib/";

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

    if (key == "annas_archive_key") {
      settings.api_key = val;
    } else if (key == "smtp_user") {
      settings.smtp_user = val;
    } else if (key == "smtp_pass") {
      settings.smtp_pass = val;
    } else if (key == "kindle_email") {
      settings.kindle_email = val;
    } else if (key == "download_dir") {
      settings.download_dir = val;
    }
  }
}

void Config::WriteDefault(const std::string &path) {
  std::cout << path << "\n";
  std::filesystem::create_directories(
      std::filesystem::path(path).parent_path());

  std::filesystem::create_directories(
      std::filesystem::path(Config::default_download_dir).parent_path());

  std::ofstream out(path);

  if (!out.is_open()) {
    std::cerr << "[ERROR] Cannot create default config!\n";
    return;
  }

  out << std::format(R"(# Configure sendr

# annas archive
annas_archive_key =

# mail
smtp_host =
smtp_port =
smtp_user =
smtp_pass =
kindle_email =

# library
download_dir = {}
)",
                     Config::default_download_dir);

  out.close();
  std::cout << "[INFO] Wrote default config to: " << path << "\n";
}
