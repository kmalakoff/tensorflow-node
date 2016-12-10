#include <map>
#include "utils.h"
namespace lib {

std::map<std::string, int> unique_ids;

std::string uniqueId(const char* key) {
  std::map<std::string, int>::iterator it = unique_ids.find(key);
  if (it == unique_ids.end()) unique_ids[key] = 0;
  return std::string(key + unique_ids[key]++);
}

} // namespace lib
