#include "SearchClient.h"

#include <curl/curl.h>
#include <iostream>
#include <sstream>

std::string SearchClient::BuildUrl(const SearchParams &params) const {
  std::ostringstream oss;
  char *encoded =
      curl_easy_escape(nullptr, params.query.c_str(), params.query.size());
  oss << base_url << "?index=&page=" << params.page << "&q=" << encoded
      << "&display=table";
  if (params.format) {
    oss << "&ext=" << *params.format;
  }
  if (params.lang) {
    oss << "&lang=" << *params.lang;
  }
  return oss.str();
}

RowVector SearchClient::Search(const SearchParams &params) const {
  auto url = BuildUrl(params);
  std::cout << url << "\n";
  auto response = client.Get(url);
  if (response.status_code != 200) {
    throw std::runtime_error("Search failed : " +
                             std::to_string(response.status_code));
  }
  auto rows = reader.Parse(response.body);
  if (params.max_results > 0 && rows.size() > params.max_results) {
    rows.resize(params.max_results);
  }
  return rows;
}
