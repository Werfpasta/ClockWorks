#if !defined(CW_INCLUDE_UTILS_ESCAPEQUOTES)
#define CW_INCLUDE_UTILS_ESCAPEQUOTES

#include <string>

namespace ClockWorks {
  namespace Util {

    std::string escape_quotes(const std::string &before) {
      std::string after;
      after.reserve(before.length() * 2);
      
      for (std::string::size_type i = 0; i < before.length(); ++i) {
	switch (before[i]) {
	case '"':
	case '\\':
	case ',':
	  after += '\\';
	  // Fall through.
	  
	default:
	  after += before[i];
	}
      }
      
      return after;
    }
    
  }
} 

#endif
