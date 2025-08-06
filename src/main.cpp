#include "Cli.h"
#include "Config.h"
#include "Daemon.h"
#include "Downloader.h"
#include "Pid.h"
#include "Using.h"

// #include "MockDownloader.h"

#include <fstream>
#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    Cli::ShowUsage();
    return 1;
  }

  std::string top_cmd = argv[1];

  if (top_cmd == "daemon") {
    return HandleDaemonCommand(argc, argv);
  }

  EnsureDaemonSpawn();

  Config config;
  Downloader downloader(config);
  Cli cli(&downloader, config);

  return cli.Run(argc, argv);
}
