#ifndef CW_INCLUDE_GAME_UNIT
#define CW_INCLUDE_GAME_UNIT


#include "../std/pair.hpp"
#include "../std/vector.hpp"
#include "../std/size_t.hpp"

//extern std::string get_Element_Name(const int x);
//extern double parse_Expression(const std::string& exp);

namespace ClockWorks {
  namespace game {
    class Unit {
    protected:

      long** gauges; 
      //This is a array of 2-element arrays.
      //index[i][0] is the current value
      //index[i][1] is the maximum value

      long* gauge_modifiers;
      //long* gauge_bonus_modifiers;
      //Additive modifiers to the gauges.

      std::vector<float>* gauge_multipliers;
      //in case of bonuses declare here

      int level; //Level of Unit
      int xp[2]; //Very special XP Gauge.


      int* currency;


      long* statistics;
      long* statistic_modifiers;
      std::vector<float>* statistic_multipliers;


      float** elemental_parameters;
      float** elemental_parameter_modifiers;
      std::vector<float>** elemental_parameter_multipliers;

		
      std::vector<std::pair<std::string,int>> statuses;
      
      //int Ability_Flags[8]; //All-purpose ability flags.

      std::pair<std::string,int>* equipment;

      //Taking out Known Abilities: That is to be determined by an Ability Controller.


      //Same goes with Items: That should be external
		
      int growth_table;


      //Passives and Attack Type/Commands are going elsewhere.


      void init();
      bool init(std::string data); //Loads data from a string

      void zero_Out_Modifiers(); //Initializes Modifiers to 0.


    public:	

      const std::string ID; //Unit ID. Assumed to be unique.
      std::string Name; //The name of the unit
      std::vector<std::String> Descrip; //Various Descriptors go here.

      //static std::string UNIT_FILE;
      //static std::string GROWTH_FILE;

      //constructor/destructor

      Unit();

      ~Unit(); //destructor  so a Unit pointer can resolve properly.

      //start off with get/set functions




      /*

      long** gauges; 
      long* gauge_modifiers;
      
      std::vector<float>* gauge_multipliers;

      int level; //Level of Unit
      int xp[2]; //Very special XP Gauge.

      int* currency;

      long* statistics;
      long* statistic_modifiers;
      std::vector<float>* statistic_multipliers;

      float** elemental_parameters;
      float** elemental_parameter_modifiers;
      std::vector<float>** elemental_parameter_multipliers;
		
      std::vector<std::pair<std::string,int>>* statuses;
      
      std::pair<std::string,int> equipment;

      //Taking out Known Abilities: That is to be determined by an Ability Controller.


      //Same goes with Items: That should be external
		
      int growth_table;


      //Passives and Attack Type/Commands are going elsewhere.


      void init();
      bool init(std::string data); //Loads data from a string

      void zero_Out_Modifiers(); //Initializes Modifiers to 0.

       */


      // This function reads out the two values for a given gauge, and sports 4 operating modes.
      // It can either spit out the modded maximum value or the unmodded value.
      // Modifications are of the form (Base + Modifier)*Multipliers.
      std::pair<long,long> read_gauge(size_t gauge, boolean modded = true);

      // Takes a gauge, and shifts it by a certain value.
      // If respect true, then maximum gauge limits will be respected.
      void shift_gauge(size_t gauge, long value, bool respect = true);

      



      inline int get_HP() const{return HP[0];} //gets current HP
      inline int get_MP() const{return MP[0];} //gets current MP

      void set_HP(const int x);
      void set_MP(const int x);

      inline int get_Raw_HP() const{return HP[1];}
      inline int get_HP_Bonus() const{return HP_Bonus;}
      inline int get_HP_Modifier() const{return HP_Modifier;}
      int get_Base_HP() const; //(Raw+Bonus)*Bonus
      int get_Max_HP() const; //(Raw+Bonus+Mod)*Bonus*Mod

      float get_HP_Bonus_Multiplier() const;
      float get_HP_Modifier_Multiplier() const;


      inline void set_Raw_HP(const int x) {HP[1]=x;}
      inline void set_HP_Bonus(const int x) {HP_Bonus=x;}
      inline void set_HP_Modifier(const int x) {HP_Modifier=x;}
      //void set_Base_HP(); //raw + bonus
      //void set_Max_HP(); //raw + bonus + mod

      inline void add_HP_Bonus_Multiplier(const float x){HP_Bonus_Mult.push_back(x);}
      inline void clear_HP_Bonus_Multiplier(){HP_Bonus_Mult.clear();}
      bool remove_HP_Bonus_Multiplier(const float x);

      inline void add_HP_Modifier_Multiplier(const float x){HP_Modifier_Mult.push_back(x);}
      inline void clear_HP_Modifier_Multiplier(){HP_Modifier_Mult.clear();}
      bool remove_HP_Modifier_Multiplier(const float x);

      inline int get_Raw_MP() const{return MP[1];}
      inline int get_MP_Bonus() const{return MP_Bonus;}
      inline int get_MP_Modifier() const{return MP_Modifier;}
      int get_Base_MP() const; //raw + bonus
      int get_Max_MP() const; //raw + bonus + mod

      float get_MP_Bonus_Multiplier() const;
      float get_MP_Modifier_Multiplier() const;

      inline void set_Raw_MP(const int x){MP[1] = x;}
      inline void set_MP_Bonus(const int x){MP_Bonus=x;}
      inline void set_MP_Modifier(const int x){MP_Modifier=x;}
      //void set_Base_MP(); //raw + bonus
      //void set_Max_MP(); //raw + bonus + mod

      inline void add_MP_Bonus_Multiplier(const float x){HP_Bonus_Mult.push_back(x);}
      inline void clear_MP_Bonus_Multiplier(){HP_Bonus_Mult.clear();}
      bool remove_MP_Bonus_Multiplier(const float x);

      inline void add_MP_Modifier_Multiplier(const float x){MP_Modifier_Mult.push_back(x);}
      inline void clear_MP_Modifier_Multiplier(){MP_Modifier_Mult.clear();}
      bool remove_MP_Modifier_Multiplier(const float x);


      inline int get_Level() const{return Level;}
      inline void set_Level(const int x){Level=x;}


      inline int get_Affinity() const{return Affinity;}
      inline void set_Affinity(const int x){Affinity=x;}

      int get_Raw_Statistic(const int x) const;
      int get_Statistic_Bonus(const int x) const;
      int get_Statistic_Modifier(const int x) const;
      int get_Base_Statistic(const int x) const;
      int get_Statistic(const int x) const;

      void set_Raw_Statistic(const int x, const int y);
      void set_Statistic_Bonus(const int x, const int y);
      void set_Statistic_Modifier(const int x, const int y);

      void add_Statistic_Bonus_Multiplier(const int x, const float y);
      void clear_Statistic_Bonus_Multiplier(const int x);
      bool remove_Statistic_Bonus_Multiplier(const int x, const float y);

      void add_Statistic_Modifier_Multiplier(const int x, const float y);
      void clear_Statistic_Modifier_Multiplier(const int x);
      bool remove_Statistic_Modifier_Multiplier(const int x, const float y);


      float get_Raw_Elemental_Attack(const int x) const; //Elem ATK
      float get_Base_Elemental_Attack(const int x) const; //Elem ATK with Bonus Mults
      float get_Elemental_Attack(const int x) const; //Elem ATK with all Mults
      void set_Raw_Elemental_Attack(const int x, const int y);

      void add_Elemental_Attack_Bonus_Multiplier(const int x, const float y);
      void clear_Elemental_Attack_Bonus_Multiplier(const int x);
      bool remove_Elemental_Attack_Bonus_Multiplier(const int x, const float y);

      void add_Elemental_Attack_Modifier_Multiplier(const int x, const float y);
      void clear_Elemental_Attack_Modifier_Multiplier(const int x);
      bool remove_Elemental_Attack_Modifier_Multiplier(const int x, const float y);

		
      float get_Raw_Elemental_Defense(const int x) const; //Elem ATK
      float get_Base_Elemental_Defense(const int x) const; //Elem ATK with Bonus Mults
      float get_Elemental_Defense(const int x) const; //Elem ATK with all Mults
      void set_Raw_Elemental_Defense(const int x, const int y);

      void add_Elemental_Defense_Bonus_Multiplier(const int x, const float y);
      void clear_Elemental_Defense_Bonus_Multiplier(const int x);
      bool remove_Elemental_Defense_Bonus_Multiplier(const int x, const float y);

      void add_Elemental_Defense_Modifier_Multiplier(const int x, const float y);
      void clear_Elemental_Defense_Modifier_Multiplier(const int x);
      bool remove_Elemental_Defense_Modifier_Multiplier(const int x, const float y);



      float get_Raw_Status_Attack(const int x) const; //Elem ATK
      float get_Base_Status_Attack(const int x) const; //Elem ATK with Bonus Mults
      float get_Status_Attack(const int x) const; //Elem ATK with all Mults
      void set_Raw_Status_Attack(const int x, const int y);

      void add_Status_Attack_Bonus_Multiplier(const int x, const float y);
      void clear_Status_Attack_Bonus_Multiplier(const int x);
      bool remove_Status_Attack_Bonus_Multiplier(const int x, const float y);

      void add_Status_Attack_Modifier_Multiplier(const int x, const float y);
      void clear_Status_Attack_Modifier_Multiplier(const int x);
      bool remove_Status_Attack_Modifier_Multiplier(const int x, const float y);


      float get_Raw_Status_Defense(const int x) const; //Elem ATK
      float get_Base_Status_Defense(const int x) const; //Elem ATK with Bonus Mults
      float get_Status_Defense(const int x) const; //Elem ATK with all Mults
      void set_Raw_Status_Defense(const int x, const int y);

      void add_Status_Defense_Bonus_Multiplier(const int x, const float y);
      void clear_Status_Defense_Bonus_Multiplier(const int x);
      bool remove_Status_Defense_Bonus_Multiplier(const int x, const float y);

      void add_Status_Defense_Modifier_Multiplier(const int x, const float y);
      void clear_Status_Defense_Modifier_Multiplier(const int x);
      bool remove_Status_Defense_Modifier_Multiplier(const int x, const float y);



      //Elemental  Attack

      int get_Status_Effect_Flag(const int x) const;
      void set_Status_Effect_Flag(const int x, const int y);

      int get_Raw_Status_Effect_Default(const int x) const;
      int get_Status_Effect_Default_Bonus(const int x) const;
      int get_Status_Effect_Default(const int x) const;

      void set_Status_Effect_Default(const int x, const int y);
      void set_Status_Effect_Default_Bonus(const int x, const int y);
		

		

      inline int get_Item_Capacity() const{return Item_Capacity;}
      void set_Item_Capacity(const int x);
		
		
		
      inline int get_XP() const{return XP;}
      void set_XP(const int x);

      //TO Consider: making this stat unsigned?
      inline int get_GP() const{return GP;}
      inline void set_GP(const int x){GP = x;}

      inline int get_Cast_Speed() const{return Cast_Speed;}
      inline void set_Cast_Speed(const int x){Cast_Speed = x;}

      inline int get_Current_Ability() const {return Current_Ability;}
      inline int get_Current_Target() const {return Current_Target;}

      inline void set_Current_Ability(const int x) {Current_Ability = x;}
      inline void set_Current_Target(const int x) {Current_Target = x;}


      /*
	int get_Raw_Auxiliary_Flag(const unsigned int x) const;
	int get_Auxiliary_Flag_Bonus(const unsigned int x) const;
	int get_Auxiliary_Flag_Modifier(const unsigned int x) const;
	int get_Base_Auxiliary_Flag(const unsigned int x) const;
	int get_Auxiliary_Flag(const unsigned int x) const;
	void set_Raw_Auxiliary_Flag(const unsigned int x, const int y);
	void set_Auxiliary_Flag_Bonus(const unsigned int x, const int y);
	void set_Auxiliary_Flag_Modifier(const unsigned int x, const int y);
      */

      inline int get_Raw_Charge_Time() const {return Charge_Time[0];}
      inline void set_Raw_Charge_Time(const int x) {Charge_Time[0] = x;}

      inline int get_Cast_Time() const {return Charge_Time[1];}
      inline void set_Cast_Time(const int x) {Charge_Time[1] = x;}

      int get_Charge_Time() const;
      void set_Charge_Time(const int x);
		
      std::string to_String() const;
      //Basic get/sets done,

		
      //This function will return the Casting CT if the unit is casting (Charge_Time[1] > 0), otherwise, it will return normal CT.

      void increment_Charge_Time();
      //This function will increment CT by SPD, or Casting CT by Cast Speed, both of which are affected by SLOW and HASTE. If Frozen, it decrements the HALT flag by one.

      inline bool get_Flee_Flag() const{return is_Fleeing;}
      inline void set_Flee_Flag(const bool b){is_Fleeing = b;}



      //void decrement_Turn(); //unknown if needed
      //Sets Casting CT to 0 and decrements normal CT by 1000.



		

		

		
      inline int get_Attack_Command() const{return Attack_Command;}
      inline void set_Attack_Command(const int x){Attack_Command = x;}
      inline int get_Passive_Command() const{return Passive_Command;}
      inline void set_Passive_Command(const int x){Passive_Command = x;}
		
      inline int get_Command_Capacity() const{return Command_Capacity;}
      void set_Command_Capacity(const int x);

      int get_Command(const int x) const;
      void set_Command(const int x, const int y);

      int get_Attack_Type(const int x) const;
      void set_Attack_Type(const int x, const int y);
      int get_Attack_Type_Default(const int x) const;
      void set_Attack_Type_Default(const int x, const int y);
		
      bool Knows_Equip_Type(const int x, const int y) const;
      void Learn_Equip_Type(const int x, const int y);
      void Unlearn_Equip_Type(const int x, const int y);
      void add_Equip_Type(const int x, const int y);
      void remove_Equip_Type(const int x, const int y);


      bool Knows_Ability(const int x) const;
      void Learn_Ability(const int x);
      void Unlearn_Ability(const int x);
      void add_Ability(const int x);
      void remove_Ability(const int x);


      bool Knows_Passive(const int x) const;
      void Learn_Passive(const int x);
      void Unlearn_Passive(const int x);
      void add_Passive(const int x);
      void remove_Passive(const int x);


		

      inline int get_Passive_Capacity() const{return Passive_Capacity;}
      void set_Passive_Capacity(const int x);

      inline int get_Passive(const int x) const;// {return Passives.at(x);}
      inline void set_Passive(const int x, const int y);//{Passives.at(x)=y;}
      inline int get_Innate_Passive(const int x=0) const {return Innate_Passives.at(x);}
      inline void set_Innate_Passive(const int x, const int y){Innate_Passives.at(x)=y;}

      //Removes the Passive Ability at that slot. Can throw std::out_of_range


      //void acquire_Passive(const int x); //Adds the Passive to list of Passives
      //void delete_Passive(const int x); //removes Passive from list of Passive
      bool has_Passive(const int x) const; //checks for existence of a Passive (either in normal or innate list)

      void add_Innate_Passive(const int x); //Adds to list of Innate Passives
      void remove_Innate_Passive(const int x); //Removes from list of Innate Passives
      bool has_Innate_Passive(const int x) const; //checks for existence of Innate Passive
		
      //
      //inline bool is_Using_Passive(const int x) const {return has_Innate_Passive(x) || has_Passive(x);}
		

      //These functions to be defined in the Item module
      int get_Item(const int x) const;
      void set_Item(const int x, const int y);

      std::string Equip_Item(const int x, const std::string& item); //returns Item code of what was previously there
      std::string Unequip_Item(const int slot); //release the Item at a certain slot.
      //To release an item, Hold an empty string.

      std::string Obtain_Equip(const int x, const std::string& equipme); //Non-strict equip
      std::string Release_Equip(const int x); //non-strict unequip
		

      inline std::string Equip_Weapon(const std::string& equipme){return Equip_Item(0,equipme);} //returns the Item code of what was previously there
		
      /*
	std::string Equip_Armor(const std::string& equipme); //same return semantic
	std::string Equip_Access(const std::string& equipme);

	std::string Unequip_Weapon();
	std::string Unequip_Armor();
	std::string Unequip_Access();
      */


      //These functions to be defined in the Growth file
      void Level_Up();
      void Level_Down();

      std::string Scan(int scanlevel);



    };

  };
#endif



  /*
    int get_Active_Ability(const int x);
    void set_Active_Ability(const int x, const int y); //technically not an override. Placing here to match with it's get function.





    int get_Weapon();
    void set_Weapon(const int x);
    int get_Armor();
    void set_Armor(const int x);
    int get_Access();
    void set_Access(const int x);


  */




