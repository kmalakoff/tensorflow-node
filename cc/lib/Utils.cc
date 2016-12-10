#include <map>
#include <sstream>
#include "Utils.h"
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

} // namespace lib
