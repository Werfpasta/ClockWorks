#ifndef CW_INCLUDE_GAME_UNIT
#define CW_INCLUDE_GAME_UNIT

#include <utility> //this nets one std::pair and std::get
#include <vector>
#include <valarray>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <iostream>

namespace ClockWorks {
  namespace game {
    class unit {
    protected:


      // CONFIGURATION VARIABLES
      // These are the variables to which the ClockWorks::game::unit
      // constructors will refer whenever a new unit is constructed.
      // Therefore, These will only ever be set once, and the
      // _initialized variable will enforce that.

      static std::size_t _NUM_GAUGES; //2
      static std::size_t _NUM_STATISTICS; //12
      static std::size_t _NUM_ELEMENTS; //8
      static std::size_t _NUM_ELEMENTAL_PARAMETERS; //2
      static std::size_t _NUM_STATUSES; //26
      static std::size_t _NUM_STATUS_PARAMETERS; //2

      // Initialization Test Value.
      static bool _initialized;

      //This is a array of 2-element arrays.
      //index[i][0] is the current value
      //index[i][1] is the maximum value
      std::valarray<std::pair<int,int> > gauges;
      std::valarray<int> gauge_modifiers;
      std::valarray<std::vector<float> > gauge_multipliers;


      int level; //Level of Unit
      std::pair <int,int> xp; //Very special XP Gauge.


      std::valarray<int> statistics;
      std::valarray<int> statistic_modifiers;
      std::valarray<std::vector<float> > statistic_multipliers;

      //Element-Major
      std::valarray<std::valarray<float> > elemental_parameters;
      std::valarray<std::valarray<float> > elemental_parameter_modifiers;
      std::valarray<std::valarray<std::vector<float> > > elemental_parameter_multipliers;

      //Status-Major
      std::valarray<std::valarray<float> > status_parameters;
      std::valarray<std::valarray<float> > status_parameter_modifiers;
      std::valarray<std::valarray<std::vector<float> > > status_parameter_multipliers;

      void enforce_respect(std::size_t gauge);

    public:	

      //const std::string ID; //Unit ID. Assumed to be unique.
      // ID will be determined by higher-level constructs, such
      // as Managers and the like

      std::string name; //The name of the unit
      std::vector<std::string> description; //Various Descriptors go here.

      //static std::string UNIT_FILE;
      //static std::string GROWTH_FILE;

      //constructor/destructor
      //TODO(JT): WRITE UP CONSTRUCTORS/DESTRUCTORS

      unit();
      unit(const char* s);
      unit(const std::string& str);

      //Temporary function - initializes Unit to Test Parameters
      void generate_test_unit();

      //Must specify all 3 - Managing own memory
      //~unit(); //destructor  so a Unit pointer can resolve properly.
      //unit(const unit& other); //Copy Constructor
      //unit& operator=(const unit& rhs);
     
      // OUTPUT FUNCTION //
      friend std::ostream& operator<< (std::ostream&, const ClockWorks::game::unit&);

      // INITIALIZATION FUNCTION //
      // This function MUST be called before any units are
      // constructed by the game. Otherwise, the configuration
      // will not work and your game will break.
      static void init(std::size_t gauge, std::size_t stats, 
		       std::size_t elements, std::size_t elemparams, 
		       std::size_t status, std::size_t statusparams);




      


      // GAUGE FUNCTION DESCRIPTION //
      // These five functions operate on the gauges, i.e.
      // the HP/MP/AP/etc, that may be present in-game 
      // (Not EXP, though, that's handled differently by default)

      // If any of these operate on a gauge that does not exist,
      // std::out_of_range WILL be thrown.

      // Common arguments across this set:
      // *std::size_t gauge: the index of the gauge you wish to access.
      // *bool respect: If respect, then that gauge will be forced
      // to respect its maximum (i.e. if curr > max, then curr = max)


      // GAUGE FUNCTION CALLS //

      // Grabs current/maximum value for the specified gauge. If
      // modded set, applies modifier, and then all multipliers,
      // to maximum value before returning.
      std::pair<int,int> read_gauge(std::size_t gauge, bool modded = true) const;

      // Replaces the gauge at index gauge with a new gauge, as defined
      // by an std::pair, with <0> as current and <1> as maximum.
      void set_gauge(std::size_t gauge, const std::pair<int,int>& newgauge, bool respect = true);

      // Increments the current value of the gauge at index gauge by value.
      void shift_gauge(std::size_t gauge, int value, bool respect = true);

      // Increments the total additive modifier of the maximum
      // value of the gauge at index gauge by value.
      void modify_gauge(std::size_t gauge, int value, bool respect = true);

      // Adds value to the multiplicative modifier stack for the
      // maximum value of the gauge at index gauge by value.
      void add_gauge_multiplier(std::size_t gauge, float value, bool respect = true);

      // Attempts to remove value from the multiplicative modifier
      // stack for maximum value of the gauge at index gauge.
      // Returns true if value is found and removed.
      // Returns false if value is not found.
      bool remove_gauge_multiplier(std::size_t gauge, float value, bool respect = true);
      

      // TODO: Document the rest of this.

      int get_statistic(std::size_t statistic, bool modded = true) const;
      void set_statistic(std::size_t statistic, int value);
      void modify_statistic(std::size_t statistic, int value);
      void add_statistic_multiplier(std::size_t statistic, float value);
      bool remove_statistic_multiplier(std::size_t statistic, float value);


      int get_elemental_parameter(std::size_t element, std::size_t parameter, bool modded = true) const;
      void set_elemental_parameter(std::size_t element, std::size_t parameter, float value);
      void modify_elemental_parameter(std::size_t element, std::size_t parameter, int value);
      void add_elemental_multiplier(std::size_t element, std::size_t parameter, float value);
      bool remove_elemental_multiplier(std::size_t element, std::size_t parameter, float value);


      int get_status_parameter(std::size_t status, std::size_t parameter, bool modded = true) const;
      void set_status_parameter(std::size_t status, std::size_t parameter, float value);
      void modify_status_parameter(std::size_t status, std::size_t parameter, int value);
      void add_status_multiplier(std::size_t status, std::size_t parameter, float value);
      bool remove_status_multiplier(std::size_t status, std::size_t parameter, float value);


      std::string str() const;


    };

  }
}
#endif






