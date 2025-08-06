#pragma once

#include "Config.h"
#include "SmtpClient.h"

struct EmailJob {
  EmailMessage msg;
  std::string attachment;
};

class Mailer {
public:
  Mailer(const Config &config);
  void Send(const EmailJob &job);

private:
  SmtpClient smtp;
  const Config &config;
};
