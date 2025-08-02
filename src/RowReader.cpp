#include "RowReader.h"
#include "Utils.h"

RowVector RowReader::Parse(const std::string& html) const {
  GumboOutputWrapper doc(html);
  RowVector rows;

  static const std::regex md5_re(R"(^/md5/([0-9a-fA-F]{32}))");

  std::function<void(GumboNode*)> walk = [&](GumboNode* node) {
    if (node->type != GUMBO_NODE_ELEMENT)
      return;

    if (node->v.element.tag == GUMBO_TAG_TR &&
        util::has_class(node, "group")) {

      Row row;
      row.md5 = util::search_for_links(node, md5_re);
      std::vector<GumboNode*> cells;
      GumboVector* children = &node->v.element.children;

      for (unsigned int i = 0; i < children->length; ++i) {
        GumboNode* child = static_cast<GumboNode*>(children->data[i]);
        if (child->type == GUMBO_NODE_ELEMENT &&
            child->v.element.tag == GUMBO_TAG_TD) {
          cells.push_back(child);
        }
      }

      for (const auto& fm : field_map) {
        if (cells.size() > fm.index) {
          row.*(fm.member) = util::cleantext(cells[fm.index]);
        }
      }

      rows.push_back(std::move(row));
    }

    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
      walk(static_cast<GumboNode*>(children->data[i]));
    }

  };

  walk(doc.Root());
  return rows;
};
