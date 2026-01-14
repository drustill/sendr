#pragma once

#include "HttpClient.h"
#include "RowReader.h"

#include <optional>
#include <string>

/// @brief Possible params for a search
struct SearchParams {
  std::string query;
  std::optional<std::string> lang;
  std::vector<std::string> formats;
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
  std::string BuildUrl(const std::string &base,
                       const SearchParams &params) const;

  RowReader reader;
  HttpClient client;
  std::vector<std::string> base_urls;

public:
  explicit SearchClient(
      std::vector<std::string> base_urls = {"http://annas-archive.li/search"
                                            "http://annas-archive.org/search"})
      : base_urls(std::move(base_urls)) {}

  RowVector Search(const SearchParams &params) const;
};
