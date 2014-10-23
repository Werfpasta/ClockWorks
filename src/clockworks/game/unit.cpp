#include <utility> //for pair and get
#include <vector>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <sstream>

#include "clockworks/game/unit.hpp"
#include "clockworks/util/escape_quotes.hpp"

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


  template<typename T>
  T read_buffer(const char* &s) {
    
    std::stringstream strm;
    //strm.reserve(initsize);
    bool escaped = false;

    for(; escaped || *s != ','; s++) {
      if(!escaped && *s == '\\') {
	escaped = true;
	continue;
      }
      strm.put(*s);
      escaped = false;

    }

    s++;
 
    T returnme;
    strm >> returnme; //DON'T SKIP WHITESPACE!!!
    return returnme;

  }


  std::string read_buffer(const char* &s) {
    
    std::stringstream strm;
    //strm.reserve(initsize);
    bool escaped = false;

    for(; escaped || *s != ','; s++) {
      if(!escaped && *s == '\\') {
	escaped = true;
	continue;
      }
      strm.put(*s);
      escaped = false;

    }

    s++;

    return strm.str();

  }


}


namespace ClockWorks {
  namespace game {
 
    // nonmembers
    std::ostream& operator<< (std::ostream& strm, const ClockWorks::game::unit& A) {
      return strm << A.str();
    }
    
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


    unit::unit() {
      if(!_initialized) throw std::exception(); //"PASTA ERROR: Unit Construct Not Yet Initialized!!\n";

      gauges.resize(_NUM_GAUGES);
      gauge_modifiers.resize(_NUM_GAUGES);
      gauge_multipliers.resize(_NUM_GAUGES);

      statistics.resize(_NUM_STATISTICS);
      statistic_modifiers.resize(_NUM_STATISTICS);
      statistic_multipliers.resize(_NUM_STATISTICS);

      elemental_parameters.resize(_NUM_ELEMENTS);
      elemental_parameter_modifiers.resize(_NUM_ELEMENTS);
      elemental_parameter_multipliers.resize(_NUM_ELEMENTS);


      for(std::valarray<float>& a: elemental_parameters) {
	a.resize(_NUM_ELEMENTAL_PARAMETERS);
      }

      for(std::valarray<float>& a: elemental_parameter_modifiers) {
	a.resize(_NUM_ELEMENTAL_PARAMETERS);
      }

      for(std::valarray<std::vector<float> >& a: elemental_parameter_multipliers) {
	a.resize(_NUM_ELEMENTAL_PARAMETERS);
      }

      status_parameters.resize(_NUM_STATUSES);
      status_parameter_modifiers.resize(_NUM_STATUSES);
      status_parameter_multipliers.resize(_NUM_STATUSES);

      for(std::valarray<float>& a: status_parameters) {
	a.resize(_NUM_STATUS_PARAMETERS);
      }

      for(std::valarray<float>& a: status_parameter_modifiers) {
	a.resize(_NUM_STATUS_PARAMETERS);
      }

      for(std::valarray<std::vector<float> >& a: status_parameter_multipliers) {
	a.resize(_NUM_STATUS_PARAMETERS);
      }

    }
    
    
    unit::unit(const char* s) : unit() {
      
      //std::stringstream ss;
      std::size_t i,I;
      
      name = read_buffer(s);
      I = read_buffer<std::size_t>(s);
      for(i=0; i<I; i++)
	description.push_back(read_buffer(s));

      level = read_buffer<int>(s);
      std::get<0>(xp) = read_buffer<int>(s);
      std::get<1>(xp) = read_buffer<int>(s);

      for(std::pair<int,int>& g: gauges) {
	std::get<0>(g) = read_buffer<int>(s);
	std::get<1>(g) = read_buffer<int>(s);
      }

      for(int& x : gauge_modifiers)
	x = read_buffer<int>(s);

      for(std::vector<float>& v: gauge_multipliers) {
	I = read_buffer<std::size_t>(s);
	for(i=0; i<I; i++)
	  v.push_back(read_buffer<float>(s));
      }


      //Statistics

      for(int& x : statistics) 
	x = read_buffer<int>(s);

      for(int& x : statistic_modifiers)
	x = read_buffer<int>(s);

      for(std::vector<float>& v: statistic_multipliers) {
	I = read_buffer<std::size_t>(s);
	for(i=0; i<I; i++)
	  v.push_back(read_buffer<float>(s));
      }


      //Elements

      for(std::valarray<float>& a: elemental_parameters)
	for(float& f : a)
	  f = read_buffer<float>(s);

      for(std::valarray<float>& a: elemental_parameter_modifiers)
	for(float& f:a)
	  f = read_buffer<float>(s);

      for(std::valarray<std::vector<float> >& a : elemental_parameter_multipliers)
	for(std::vector<float>& v : a) {
	  I = read_buffer<std::size_t>(s);
	  for(i=0; i<I; i++)
	    v.push_back(read_buffer<float>(s));
	}


      //Statuses

      for(std::valarray<float>& a: status_parameters)
	for(float& f:a)
	  f = read_buffer<float>(s);

      for(std::valarray<float>& a: status_parameter_modifiers)
	for(float& f:a)
	  f = read_buffer<float>(s);

      for(std::valarray<std::vector<float> >& a : status_parameter_multipliers)
	for(std::vector<float>& v : a) {
	  I = read_buffer<std::size_t>(s);
	  for(i=0; i<I; i++)
	    v.push_back(read_buffer<float>(s));
	}
 
    }

    unit::unit(const std::string& str) : unit(str.c_str()) {}



    void unit::generate_test_unit() {
      name = "Test Unit";

      description.resize(0); //clear vector

      description.push_back("This is a test unit.");
      description.push_back("If you are seeing this text, it means you have generated a debug unit to test something!");
      description.push_back("Warning: this unit is not fit for actual combat.");


      level = 0;
      std::get<0>(xp) = 123;
      std::get<1>(xp) = 321;


      //Gauges
      for(std::pair<int,int>& g: gauges) {
	std::get<0>(g) = 0; 
	std::get<1>(g) = 1;
      }

      for(std::size_t i=0; i<_NUM_GAUGES; i++) {
	gauge_modifiers[i] = i+1;

	gauge_multipliers[i].clear();
	for(std::size_t j = 0; j<=i; j++)
	  gauge_multipliers[i].push_back((i+1.0)*10.0/100.0);
      }

      //Statistics
      for(std::size_t i=0; i<_NUM_STATISTICS; i++) {
	statistics[i] = i+1;
	statistic_modifiers[i] = i+1;

	statistic_multipliers[i].clear();
	for(std::size_t j = 0; j<=i; j++)
	  statistic_multipliers[i].push_back((i+1.0)*10.0/100.0);
      }


      //Elements
      for(std::size_t i=0; i<_NUM_ELEMENTS; i++)
	for(std::size_t j=0; j<_NUM_ELEMENTAL_PARAMETERS; j++) {
	  elemental_parameters[i][j] = (i+1)*1000+j;
	  elemental_parameter_modifiers[i][j] = (i+1)*100+j;


	  elemental_parameter_multipliers[i][j].clear();
	  for(std::size_t k = 0; k<=j; k++)
	    elemental_parameter_multipliers[i][j].push_back((k+1.0)*10.0/100.0);
	
	}


      //Statuses
      for(std::size_t i=0; i<_NUM_STATUSES; i++) 
	for(std::size_t j=0; j<_NUM_STATUS_PARAMETERS; j++) {
	  status_parameters[i][j] = (i+1)*1000+j;
	  status_parameter_modifiers[i][j] = (i+1)*100+j;


	  status_parameter_multipliers[i][j].clear();
	  for(std::size_t k = 0; k<=j; k++)
	    status_parameter_multipliers[i][j].push_back((k+1.0)*10.0/100.0);
	}
    }               
    
    
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


    std::string unit::str() const{
      
      std::stringstream strm;

      strm << Util::escape_quotes(name) << ',';
      strm << description.size() << ',';
      for(const std::string& s: description)
	strm << Util::escape_quotes(s) << ',';
      //strm << '\"' << s << "\",";
      strm << level << ',' << std::get<0>(xp) << ',' << std::get<1>(xp) << ',';
      
      //Gauges
      for(const std::pair<int,int>& g: gauges)
	strm << std::get<0>(g) << ',' << std::get<1>(g) << ',';
      for(const int& i: gauge_modifiers)
	strm << i << ',';
      for(const std::vector<float>& v: gauge_multipliers) {
	strm << v.size() << ',';
	for(const float& f: v)
	  strm << f << ',';
      }
      
      //Statistics
      for(const int& i: statistics)
	strm << i << ',';
      for(const int& i: statistic_modifiers)
	strm << i << ',';
      for(const std::vector<float>& v: statistic_multipliers) {
	strm << v.size() << ',';
	for(const float& f: v)
	  strm << f << ',';
      }

     
 
      //Elements
      for(const std::valarray<float>& a: elemental_parameters)
	for(const float& f: a)
	  strm << f << ',';
      
      for(const std::valarray<float>& a: elemental_parameter_modifiers)
	for(const float& f: a)
	  strm << f << ',';
      
      for(const std::valarray<std::vector<float> >& a : elemental_parameter_multipliers)
	for(const std::vector<float>& v : a) {
	  strm << v.size() << ',';
	  for(const float& f: v)
	    strm << f << ',';
	}
      
      //Statuses
      for(const std::valarray<float>& a: status_parameters)
	for(const float& f: a)
	  strm << f << ',';
      
      for(const std::valarray<float>& a: status_parameter_modifiers)
	for(const float& f: a)
	  strm << f << ',';
      
      for(const std::valarray<std::vector<float> >& a : status_parameter_multipliers)
	for(const std::vector<float>& v : a) {
	  strm << v.size() << ',';
	  for(const float& f: v)
	    strm << f << ',';
	}
      
      return strm.str();


    }
    
  };

};

