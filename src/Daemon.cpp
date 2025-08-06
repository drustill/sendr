#include "Config.h"
#include "KQueueListener.h"
#include "Mailer.h"
#include "MailerListener.h"
#include "Pid.h"

#include <fcntl.h>
#include <unistd.h>

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
