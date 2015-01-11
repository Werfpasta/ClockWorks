#ifndef CW_INCLUDE_GAME_ITEM
#define CW_INCLUDE_GAME_ITEM

#include <utility> //this nets one std::pair and std::get
#include <vector>
#include <valarray>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <map>

namespace ClockWorks {
  namespace game {

    class item {

    protected:


    public:

      // This is the associative array of the item's properties.
      // Designed this way for flexibility reasons.
      std::map<std::string,std::string> properties;

      item();
      item(const char* s);
      item(const std::string& str);

      std::string str() const;


    };


  }
}
#endif





