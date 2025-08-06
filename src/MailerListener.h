#pragma once

#include "EventListener.h"

class MailerListener : public EventListener {
public:
  MailerListener(Config &config, Mailer &mailer)
      : config(config), mailer(mailer) {}

  /// TODO: IMPLEMENT!
  void OnEvent(const FileEvent &e) override {
    if (false) {
      EmailJob job;
      mailer.Send(job);
    }
  }

private:
  Config &config;
  Mailer &mailer;
};
