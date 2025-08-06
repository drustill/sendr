#pragma once

#include <cstdlib>
#include <gumbo.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>
#include <regex>
#include <string>
#include <vector>

namespace util {
inline std::vector<std::string> split(const std::string &s,
                                      const std::string &delimiter) {
  std::vector<std::string> tokens;
  size_t start = 0, pos;
  auto dsz = delimiter.size();
  std::string token;
  while ((pos = s.find(delimiter, start)) != std::string::npos) {
    tokens.emplace_back(s.substr(start, pos - start));
    start = pos + dsz;
  }
  tokens.emplace_back(s.substr(start));
  return tokens;
}

inline void rtrim(std::string &s) {
  s.erase(s.find_last_not_of(" \n\r\t") + 1);
}

inline void ltrim(std::string &s) {
  size_t start = s.find_first_not_of(" \n\r\t");
  if (start != std::string::npos) {
    s.erase(0, start);
  } else {
    s.clear();
  }
}

inline void strip_comments(std::string &s) {
  size_t comment = s.find("#");
  if (comment != std::string::npos)
    s = s.substr(0, comment);
}

inline bool has_class(GumboNode *node, const char *cls_name) {
  if (node->type != GUMBO_NODE_ELEMENT)
    return false;
  GumboAttribute *cls_attr =
      gumbo_get_attribute(&node->v.element.attributes, "class");
  return cls_attr && strstr(cls_attr->value, cls_name) != nullptr;
}

inline std::string cleantext(GumboNode *node) {
  if (node->type == GUMBO_NODE_TEXT) {
    return std::string(node->v.text.text);
  } else if (node->type == GUMBO_NODE_ELEMENT &&
             node->v.element.tag != GUMBO_TAG_SCRIPT &&
             node->v.element.tag != GUMBO_TAG_STYLE) {
    std::string contents = "";
    GumboVector *children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
      const std::string text =
          cleantext(static_cast<GumboNode *>(children->data[i]));
      if (i != 0 && !text.empty()) {
        contents.append(" ");
      }
      contents.append(text);
    }
    return contents;
  } else {
    return "";
  }
}

inline std::string search_for_links(GumboNode *node, std::regex filter) {
  if (node->type != GUMBO_NODE_ELEMENT)
    return "";

  GumboAttribute *href;
  if (node->v.element.tag == GUMBO_TAG_A &&
      (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
    std::smatch m;
    std::string val = href->value;
    if (std::regex_search(val, m, filter))
      return m.str(1);
  }

  GumboVector *children = &node->v.element.children;
  for (unsigned int i = 0; i < children->length; ++i) {
    std::string link =
        search_for_links(static_cast<GumboNode *>(children->data[i]), filter);
    if (!link.empty())
      return link;
  }

  return "";
}

inline std::string escape_new_lines(const std::string &s) {
  std::string out = s;
  size_t pos = 0;
  while ((pos = out.find("\r\n", pos)) != std::string::npos) {
    out.replace(pos, 2, "\\r\\n");
    pos += 4;
  }
  return out;
}

inline std::string base64_encode(const std::string &s) {
  BIO *bio, *b64;
  BUF_MEM *bufferptr;
  b64 = BIO_new(BIO_f_base64());
  bio = BIO_new(BIO_s_mem());
  bio = BIO_push(b64, bio);

  BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
  BIO_write(bio, s.data(), s.size());
  BIO_flush(bio);
  BIO_get_mem_ptr(bio, &bufferptr);

  std::string out(bufferptr->data, bufferptr->length);
  BIO_free_all(bio);
  return out;
}

} // namespace util
