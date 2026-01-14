#include "SearchClient.h"

#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

std::string SearchClient::BuildUrl(const std::string &base,
                                   const SearchParams &params) const {
  std::ostringstream oss;
  char *encoded =
      curl_easy_escape(nullptr, params.query.c_str(), params.query.size());
  oss << base << "?index=&page=" << params.page << "&q=" << encoded
      << "&display=table";

  for (auto format : params.formats) {
    oss << "&ext=" << format;
  }

  if (params.lang) {
    oss << "&lang=" << *params.lang;
  }
  return oss.str();
}

RowVector SearchClient::Search(const SearchParams &params) const {
  for (const auto &base : base_urls) {
    try {
      auto url = BuildUrl(base, params);
      auto response = client.Get(url);
      if (response.status_code == 200) {
        return reader.Parse(response.body, params.max_results);
      }
    } catch (...) {
      continue;
    }
  }
  throw std::runtime_error(
      std::format("Failed to search on {} domains", base_urls.size()));
}
