#pragma once

#include <string>

class CommunicationLogger {
public:
  CommunicationLogger();
  ~CommunicationLogger();

  static constexpr std::string LogPrefix = "[LOG]";
  static constexpr std::string ErrPrefix = "[ERR]";
  static constexpr size_t InitLogLength = 4096;

  void Reset();
  void Log(const std::string &prefix, const std::string &item);
  const char *Data() const;
  size_t Capacity() const;

  CommunicationLogger(const CommunicationLogger &) = delete;
  CommunicationLogger &operator=(const CommunicationLogger &) = delete;
  CommunicationLogger(CommunicationLogger &&) = delete;
  CommunicationLogger &operator=(CommunicationLogger &) = delete;

private:
  char *log;
  size_t size;
};
