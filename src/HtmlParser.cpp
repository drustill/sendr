#include "HtmlParser.h"

void HtmlParser::SkipWhitespace()
{
  while (pos < s.size() && isspace((unsigned char)s[pos]))
    pos++;
}

bool HtmlParser::StartsWith(const std::string &t)
{
  return s.compare(pos, t.size(), t) == 0;
}

std::string HtmlParser::ReadText()
{
  size_t start = pos;
  while (pos < s.size() && s[pos] != '<')
    pos++;

  size_t end = pos;
  while (end > start && isspace((unsigned char)s[end - 1]))
    end--;

  return s.substr(start, end - start);
}

std::string HtmlParser::ReadTagName()
{
  size_t start = pos;
  while (pos < s.size() && isalnum((unsigned char)s[pos]))
    pos++;
  return s.substr(start, pos - start);
}

NodePtr HtmlParser::ParseNode()
{
  SkipWhitespace();

  if (pos >= s.size())
    return nullptr;

  if (s[pos] == '<')
  {
    if (StartsWith("</"))
      return nullptr;

    pos++; // <
    std::string tag = ReadTagName();
    pos++; // >

    auto node = std::make_unique<Node>();
    node->tag = tag;

    while (true)
    {
      SkipWhitespace();

      // 3 = </ >
      if (StartsWith("</" + tag))
      {
          pos += 3 + tag.size();
          break;
      }

      auto child = ParseNode();
      if (!child)
        break;

      node->children.push_back(std::move(child));
    }

    return node;

  }

  auto txt = ReadText();
  auto node = std::make_unique<Node>();
  node->text = txt;

  return node;
}

NodePtr HtmlParser::Parse() {
  auto root = std::make_unique<Node>();

  while (pos < s.size()) {
    if (auto n = ParseNode())
      root->children.push_back(std::move(n));
      continue;
    pos++;
  }

  return root;
}
