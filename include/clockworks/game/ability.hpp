#ifndef CW_INCLUDE_GAME_ABILITY
#define CW_INCLUDE_GAME_ABILITY

#include <utility> //this nets one std::pair and std::get
#include <vector>
#include <valarray>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <iostream>

namespace ClockWorks {
  namespace game {

    class ability {

    protected:
      
      unit* agent; //The unit that caused the ability

    public:

      virtual void apply(unit& target) = 0;
      virtual std::string get_mame() = 0;
      virtual std::string get_description() = 0;

    };


  }
}
#endif

