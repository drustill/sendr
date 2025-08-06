#pragma once

enum class DaemonCommand {
  Stop,
  Start,
  Status,
  Restart,
  Unknown,
};

void SpawnDaemon();
void EnsureDaemonSpawn();
int HandleDaemonCommand(int argc, char *argv[]);
DaemonCommand ParseDaemonCommand(const std::string &cmd);
