#pragma once

#include "Using.h"

#include <string>
#include <vector>

struct Node {
  std::string tag;
  std::string text;
  std::vector<NodePtr> children;
};

class HtmlParser
{
  public:
    HtmlParser(const std::string &src): s(src), pos(0) {}
    NodePtr Parse();

  private:
    const std::string &s;
    size_t pos;

    void SkipWhitespace();
    bool StartsWith(const std::string &t);

    std::string ReadText();
    std::string ReadTagName();

    NodePtr ParseNode();
};
