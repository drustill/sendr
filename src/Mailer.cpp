#include "Mailer.h"

#include <fstream>

Mailer::Mailer(const Config &config) : smtp(config), config(config) {
  smtp.Connect();
  smtp.StartTLS();
  smtp.Authenticate();
}

void Mailer::Send(const EmailJob &job) {
  smtp.SendMail(job.msg, job.attachment);
  std::ofstream log("/tmp/sendr.log", std::ios::app);
  log << "[SMTP] " << smtp.logger.Data() << "\n";
  smtp.logger.Reset();
}
