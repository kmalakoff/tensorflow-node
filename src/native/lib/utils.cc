#include <map>
#include <string>
#include <sstream>
#include <vector>
#include "utils.h"

namespace lib {

std::map<std::string, int> unique_ids;

std::string uniqueId(const char* key) {
  std::map<std::string, int>::iterator it = unique_ids.find(key);
  if (it == unique_ids.end()) unique_ids[key] = 0;
  std::ostringstream oss;
  oss << key;
  oss << unique_ids[key]++;
  return oss.str();
}

void split(const std::string &s, char delim, std::vector<std::string> &elems) { // TODO: remove after headers match for node name
  std::stringstream ss;
  ss.str(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
    if (elems.size() > 1) break;
  }
}

std::string nodeName(const tensorflow::Node* node) { // TODO: remove after headers match for node name
  std::vector<std::string> parts;
  split(node->DebugString(), '\'', parts);
  return parts[1];
}

} // namespace lib
