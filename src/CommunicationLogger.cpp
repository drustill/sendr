#include "CommunicationLogger.h"
#include "Utils.h"

#include <cstring>
#include <iostream>
#include <sstream>

CommunicationLogger::CommunicationLogger() : log(nullptr), size(0) {}

CommunicationLogger::~CommunicationLogger() { delete[] log; }

void CommunicationLogger::Reset() {
  delete[] log;
  log = new char[InitLogLength];
  size = InitLogLength;
  log[0] = '\0';
}

void CommunicationLogger::Log(const std::string &prefix,
                              const std::string &item) {
  std::ostringstream oss;
  oss << "\n" << prefix << ": " << util::escape_new_lines(item);
  const std::string &line = oss.str();
  size_t current = std::strlen(log);
  size_t required = current + line.size() + 1;

  if (required > size) {
    size_t new_size = required + InitLogLength;
    char *new_log = new char[new_size];
    std::strncpy(new_log, log, current);
    new_log[current] = '\0';
    delete[] log;
    log = new_log;
    size = new_size;
  }

  std::strncat(log, line.c_str(), size - current - 1);
  log[size - 1] = '\0';
}

const char *CommunicationLogger::Data() const { return log; }

size_t CommunicationLogger::Capacity() const { return size; }
