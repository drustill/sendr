#pragma once

#include "HttpClient.h"
#include "RowReader.h"

#include <optional>
#include <string>

/// @brief Possible params for a search
struct SearchParams {
  std::string query;
  std::optional<std::string> lang;
  std::optional<std::string> format;
  int page = 1;
  int max_results = 0;
};

/// @brief High level client to perform a search on Annas Archive
///
/// Functionality to build a request with filters, make the request
/// through lower level HttpClient and then return parsed results in
/// a RowVector
class SearchClient {
private:
  std::string BuildUrl(const SearchParams &params) const;

  RowReader reader;
  HttpClient client;
  std::string base_url;

public:
  explicit SearchClient(std::string base_url = "http://annas-archive.li/search")
      : base_url(std::move(base_url)) {}

  RowVector Search(const SearchParams &params) const;
};
