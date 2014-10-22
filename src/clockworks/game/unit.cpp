#include <utility> //for pair and get
#include <vector>
#include <string>
#include <cstdlib>

#include <stdexcept>

#include "../../../include/clockworks/game/unit.hpp"


namespace {

  template<class T, typename U>
  T array_fetch(const std::valarray<T>& arr, std::size_t index, const T& mod, const std::vector<U>& mults, bool modon) {
    if(index >= arr.size()) throw std::out_of_range("Error: Index out of bounds");
    T returnme = arr[index];
    
    if(modon) {
      returnme += mod;
      for (U u: mults) 
	returnme *= u;
    }
    
    return returnme;
  }


  template<class T>
  void array_scribe(std::valarray<T>& arr, std::size_t index, const T& newguy) {
    if(index >= arr.size()) throw std::out_of_range("Error: Index out of bounds");
    arr[index] = newguy;
  }


  template<typename T>
  bool vector_remove(std::vector<T> vector, const T& target) {
    for(std::size_t i = 0; i < vector.size(); i++) {
      if (vector[i] == target) {
	vector.erase(vector.begin()+i);
	return true;
      }
    }
    return false;
  }


}


namespace ClockWorks {
  namespace game {
    
    //protected
   
    std::size_t unit::_NUM_GAUGES;
    std::size_t unit::_NUM_STATISTICS;
    std::size_t unit::_NUM_ELEMENTS;
    std::size_t unit::_NUM_ELEMENTAL_PARAMETERS;
    std::size_t unit::_NUM_STATUSES;
    std::size_t unit::_NUM_STATUS_PARAMETERS;
    
    bool unit::_initialized = false; //Initializing here.

    void unit::enforce_respect(std::size_t gauge) {
      int compareme = std::get<1>(gauges[gauge]);
      compareme += gauge_modifiers[gauge];
      // Let's be pessimistic and floor everything.
      for(float f : gauge_multipliers[gauge]) compareme *= f;
      
      if(std::get<0>(gauges[gauge]) >= compareme) std::get<0>(gauges[gauge]) = compareme;
      
    }

    
    //public

    
    void unit::init(std::size_t gauge, std::size_t stats, 
		    std::size_t elements, std::size_t elemparams, 
		    std::size_t status, std::size_t statusparams) {
      
      if(_initialized) throw std::exception(); //"PASTA ERROR: Unit Construct Already Initialized!!\n";

      _NUM_GAUGES = gauge;
      _NUM_STATISTICS = stats;
      _NUM_ELEMENTS = elements; 
      _NUM_ELEMENTAL_PARAMETERS = elemparams; 
      _NUM_STATUSES = status;
      _NUM_STATUS_PARAMETERS = statusparams;

      _initialized = true;

    }
    
    std::pair<int,int> unit::read_gauge(std::size_t gauge, bool modded) const {
      
      std::pair<int, int> returnme = gauges[gauge];
      
      //If we make it here, then we're in range
      //so stop checking for std::out_of_range
      
      if(modded) {
	std::get<1>(returnme) += gauge_modifiers[gauge];
	// Let's be pessimistic and floor everything.
	for(float f : gauge_multipliers[gauge]) std::get<1>(returnme) *= f;
      }

      return returnme;
    }


    void unit::set_gauge(std::size_t gauge, const std::pair<int,int>& newgauge, bool respect) {
      array_scribe(gauges, gauge, newgauge);
      if(respect) enforce_respect(gauge);
    }

    void unit::shift_gauge(std::size_t gauge, int value, bool respect) {
      if(gauge >= gauges.size()) throw std::out_of_range("Error: Gauge index out of bounds");
      std::get<0>(gauges[gauge]) += value;
      if(respect) enforce_respect(gauge);
    }

    void unit::modify_gauge(std::size_t gauge, int value, bool respect) {
      if(gauge >= gauge_modifiers.size()) throw std::out_of_range("Error: Gauge index is out of bounds");
      gauge_modifiers[gauge] += value;
      if(respect) enforce_respect(gauge);
    }

    void unit::add_gauge_multiplier(std::size_t gauge, float value, bool respect) {
      if(gauge >= gauges.size()) throw std::out_of_range("Error: Gauge index out of bounds");
      gauge_multipliers[gauge].push_back(value);
      if(respect) enforce_respect(gauge);
    }

    bool unit::remove_gauge_multiplier(std::size_t gauge, float value, bool respect) {
      if(gauge >= gauges.size()) throw std::out_of_range("Error: Gauge index out of bounds");
      bool returnme = vector_remove(gauge_multipliers[gauge],value);
      if(respect) enforce_respect(gauge);
      return returnme;
    }
    
    
    
    int unit::get_statistic(std::size_t statistic, bool modded) const{
      return array_fetch(statistics,statistic,statistic_modifiers[statistic], statistic_multipliers[statistic], modded);
    }

    void unit::set_statistic(std::size_t statistic, int value) {
      array_scribe(statistics,statistic,value);
    }

    void unit::modify_statistic(std::size_t statistic, int value) {
      if(statistic >= statistics.size()) throw std::out_of_range("Error: Statistic index out of bounds");
      statistic_modifiers[statistic] += value;
    }
    void unit::add_statistic_multiplier(std::size_t statistic, float value) {
      if(statistic >= statistics.size()) throw std::out_of_range("Error: Statistic index out of bounds");
      statistic_multipliers[statistic].push_back(value);
    }
    bool unit::remove_statistic_multiplier(std::size_t statistic, float value) {
      if(statistic >= statistics.size()) throw std::out_of_range("Error: Statistic index out of bounds");
      return vector_remove(statistic_multipliers[statistic],value);
    }
    
    
    int unit::get_elemental_parameter(std::size_t element, std::size_t parameter, bool modded) const {
      if(element >= elemental_parameters.size()) throw std::out_of_range("Error: Element index out of bounds");
      return array_fetch(elemental_parameters[element],parameter,elemental_parameter_modifiers[element][parameter], elemental_parameter_multipliers[element][parameter], modded);
    }

    void unit::set_elemental_parameter(std::size_t element, std::size_t parameter, float value) {
      if(element >= elemental_parameters.size()) throw std::out_of_range("Error: Element index out of bounds");
      return array_scribe(elemental_parameters[element],parameter,value);
    }

    void unit::modify_elemental_parameter(std::size_t element, std::size_t parameter, int value) {
      if(element >= elemental_parameters.size()) throw std::out_of_range("Error: Element index out of bounds");
      if(parameter >= elemental_parameters[element].size()) throw std::out_of_range("Error: Parameter index out of bounds");
      elemental_parameter_modifiers[element][parameter] += value;
    }

    void unit::add_elemental_multiplier(std::size_t element, std::size_t parameter, float value) {
      if(element >= elemental_parameters.size()) throw std::out_of_range("Error: Element index out of bounds");
      if(parameter >= elemental_parameters[element].size()) throw std::out_of_range("Error: Parameter index out of bounds");
      elemental_parameter_multipliers[element][parameter].push_back(value);
    }

    bool unit::remove_elemental_multiplier(std::size_t element, std::size_t parameter, float value) {
      if(element >= elemental_parameters.size()) throw std::out_of_range("Error: Element index out of bounds");
      if(parameter >= elemental_parameters[element].size()) throw std::out_of_range("Error: Parameter index out of bounds");
      return vector_remove(elemental_parameter_multipliers[element][parameter], value);
    }





    int unit::get_status_parameter(std::size_t status, std::size_t parameter, bool modded) const {
      if(status >= status_parameters.size()) throw std::out_of_range("Error: Status index out of bounds");
      return array_fetch(status_parameters[status],parameter,status_parameter_modifiers[status][parameter], status_parameter_multipliers[status][parameter], modded);
    }

    void unit::set_status_parameter(std::size_t status, std::size_t parameter, float value) {
      if(status >= status_parameters.size()) throw std::out_of_range("Error: Status index out of bounds");
      return array_scribe(status_parameters[status],parameter,value);
    }

    void unit::modify_status_parameter(std::size_t status, std::size_t parameter, int value) {
      if(status >= status_parameters.size()) throw std::out_of_range("Error: Status index out of bounds");
      if(parameter >= status_parameters[status].size()) throw std::out_of_range("Error: Parameter index out of bounds");
      status_parameter_modifiers[status][parameter] += value;
    }

    void unit::add_status_multiplier(std::size_t status, std::size_t parameter, float value) {
      if(status >= status_parameters.size()) throw std::out_of_range("Error: Status index out of bounds");
      if(parameter >= status_parameters[status].size()) throw std::out_of_range("Error: Parameter index out of bounds");
      status_parameter_multipliers[status][parameter].push_back(value);
    }

    bool unit::remove_status_multiplier(std::size_t status, std::size_t parameter, float value) {
      if(status >= status_parameters.size()) throw std::out_of_range("Error: Status index out of bounds");
      if(parameter >= status_parameters[status].size()) throw std::out_of_range("Error: Parameter index out of bounds");
      return vector_remove(status_parameter_multipliers[status][parameter], value);
    }    
    
  };

};

