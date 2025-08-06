#pragma once

#include <fstream>
#include <iostream>
#include <optional>
#include <signal.h>
#include <unistd.h>

inline const char *PID_FILE = "/tmp/sendr.pid";

inline std::optional<pid_t> ReadPidFile() {
  std::ifstream pid_file(PID_FILE);
  pid_t pid;
  if (!(pid_file >> pid)) {
    return std::nullopt;
  }
  if (kill(pid, 0) == 0) {
    return pid;
  }
  return std::nullopt;
}

inline bool IsDaemonSpawn() { return ReadPidFile().has_value(); }

inline void WritePidFile() {
  std::ofstream pid_file(PID_FILE);
  pid_file << getpid();
}

inline void KillDaemon() {
  auto opt_pid = ReadPidFile();
  if (!opt_pid) {
    std::cerr << "daemon not running\n";
    return;
  }

  pid_t pid = *opt_pid;
  if (kill(pid, SIGTERM) == 0) {
    std::cout << "sendr daemon killed.\n";
    unlink(PID_FILE);
  } else {
    perror("[ERR] kill sendr daemon");
  }
}
