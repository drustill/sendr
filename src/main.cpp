#include "Cli.h"
#include "Config.h"
#include "Daemon.h"
#include "Downloader.h"
#include "Pid.h"
// #include "MockDownloader.h"

#include <fstream>
#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc >= 2) {
    std::string cmd = argv[1];
    if (cmd == "daemon") {
      SpawnDaemon();
      return 0;
    } else if (cmd == "reset") {
      KillDaemon();
      pid_t pid = fork();
      if (pid == 0) {
        execl("/usr/bin/env", "env", "sendr", "daemon", (char *)nullptr);
        _exit(1);
      }
      std::cout << "sendr daemon reloaded.\n";
      return 0;
    } else if (cmd == "stop") {
      KillDaemon();
      return 0;
    }
  }

  if (!IsDaemonSpawn()) {
    pid_t pid = fork();
    if (pid == 0) {
      execl("/usr/bin/env", "env", "sendr", "daemon", (char *)nullptr);
      _exit(1);
    }
    sleep(1);
  }

  Config config;
  Downloader downloader(config);
  // MockDownloader downloader;
  Cli cli(&downloader, config);
  return cli.Run(argc, argv);
}
