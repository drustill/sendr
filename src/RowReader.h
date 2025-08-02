#pragma once

#include "Using.h"

#include <gumbo.h>
#include <string>
#include <vector>

/// Represents a single <tr> element in the Anna's Archive search results table.
///
/// Fields are found from:
///   - md5        : Extracted from the <a href="/md5/...">
///   - title      : Column 0
///   - author     : Column 1
///   - publisher  : Column 2
///   - year       : Column 3
///   - lang       : Column 6
///   - format     : Column 8
///   - size       : Column 9
///
/// @see RowReader::parse, RowReader::FieldMap
struct Row {
  std::string md5, title, author, publisher, year, lang, format, size;
};

/// Parses Annas Archive search result html doc into a RowVector.
///
/// Usage:
///   RowReader reader;
///   RowVector rows = reader.Parse(html);
///
/// Extracts data from each <tr> using Gumbo and makes a Row
class RowReader {
private:
  /// Maps <td> index to Row member
  struct FieldMap {
    size_t index;
    std::string Row::*member;
  };
  static constexpr size_t FIELDS = 7;
  static constexpr std::array<FieldMap, FIELDS> field_map{{{1, &Row::title},
                                                           {2, &Row::author},
                                                           {3, &Row::publisher},
                                                           {4, &Row::year},
                                                           {7, &Row::lang},
                                                           {9, &Row::format},
                                                           {10, &Row::size}}};

public:
  /// Uses Gumbo to parse html into a vector of Rows.
  ///
  /// Walks the tree recursively using a lambda, each
  /// <tr> becomes one Row in the output
  RowVector Parse(const std::string &html) const;
};

/// RAII wrapper for Gumbo parser
///
/// Runs gumbo_parse on construction and gumbo_destroy_output on
/// destruction. Root() exposes the root of the html tree
///
/// Usage:
///   std::string html =
///     "<p>this is how I learned what RAII means</p>"
///   GumboOutputWrapper doc(html);
///   GumboNode* root = doc.root();
///
/// @see https://github.com/google/gumbo-parser/blob/master/src/gumbo.h
class GumboOutputWrapper {
private:
  GumboOutput *output;

public:
  explicit GumboOutputWrapper(const std::string &html)
      : output(gumbo_parse(html.c_str())) {}

  ~GumboOutputWrapper() { gumbo_destroy_output(&kGumboDefaultOptions, output); }

  /// Convenience access to root
  GumboNode *Root() const { return output->root; }
};
