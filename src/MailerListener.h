#pragma once

#include "Config.h"
#include "EventListener.h"
#include "Mailer.h"
#include "Utils.h"

#include <filesystem>
#include <iostream>

class MailerListener : public EventListener {
public:
  MailerListener(const Config &config, Mailer &mailer)
      : config(config), mailer(mailer) {}

  void OnEvent(const FileEvent &e) override {
    std::cerr << "MailerListener Called " << e.path << "\n";
    if (e.action != FileAction::Created) {
      return;
    }

    if (!std::filesystem::exists(e.path)) {
      std::cerr << "MailerListener PATH FAIL\n";
      return;
    }

    std::cerr << "MailerListener Emailing\n";

    EmailJob job;
    job.msg = EmailMessage{.from = config.Get().smtp_user,
                           .to = config.Get().kindle_email,
                           .subject = "Sendr Send Book",
                           .body = "Sendr Send Body"};
    job.attachment = e.path;

    mailer.Send(job);
    std::cerr << "Mailer SENT!\n";
  }

private:
  const Config &config;
  Mailer &mailer;
};
