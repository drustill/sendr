#include "Daemon.h"
#include "Cli.h"
#include "Config.h"
#include "KQueueListener.h"
#include "Mailer.h"
#include "MailerListener.h"
#include "Pid.h"

#include <fcntl.h>
#include <unistd.h>

DaemonCommand ParseDaemonCommand(const std::string &cmd) {
  static const DaemonCommandMap cmd_map = {
      {"stop", DaemonCommand::Stop},
      {"start", DaemonCommand::Start},
      {"status", DaemonCommand::Status},
      {"restart", DaemonCommand::Restart},
  };

  auto it = cmd_map.find(cmd);
  return it != cmd_map.end() ? it->second : DaemonCommand::Unknown;
}

void EnsureDaemonSpawn() {
  if (IsDaemonSpawn())
    return;
  pid_t pid = fork();
  if (pid == 0) {
    execl("/usr/bin/env", "env", "sendr", "daemon", (char *)nullptr);
    _exit(1);
  }
  sleep(1);
}

void SpawnDaemon() {
  int fd = open("/tmp/sendr.log", O_CREAT | O_WRONLY | O_APPEND, 0644);
  if (fd != 1) {
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);
    close(fd);
  }

  Config config;
  Mailer mailer(config);
  MailerListener ml(config, mailer);

  WritePidFile();
  KQueueListener kq;
  kq.WatchDir(config.Get().download_dir);
  kq.AddListener(&ml);
  kq.Start();

  while (true) {
    pause();
  }
}

void DaemonStatus() {
  std::cout << "Not Implemented!\n";
  return;
}

int HandleDaemonCommand(int argc, char *argv[]) {
  if (argc == 2) {
    SpawnDaemon();
    return 0;
  } else if (argc < 3) {
    Cli::ShowUsage();
    return 1;
  }

  DaemonCommand cmd = ParseDaemonCommand(argv[2]);
  switch (cmd) {
  case DaemonCommand::Stop:
    KillDaemon();
    break;

  case DaemonCommand::Start:
    EnsureDaemonSpawn();
    break;

  case DaemonCommand::Status:
    DaemonStatus();
    break;

  case DaemonCommand::Restart:
    KillDaemon();
    EnsureDaemonSpawn();
    break;

  default:
    Cli::ShowUsage();
    return 1;
  }

  return 0;
}
