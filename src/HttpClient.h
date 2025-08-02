#pragma once

#include <string>

struct HttpResponse {
  long status_code;
  std::string body;
};

/// Tiny HttpClient used to make requests to Annas Archive.
///
/// GET is the only supported method. Responses are wrapped
/// in an HttpResponse
class HttpClient {
public:
  HttpClient();
  ~HttpClient();
  HttpResponse Get(const std::string &url) const;

private:
  HttpResponse Request(const std::string &url) const;
};
