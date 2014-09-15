#ifndef SOURCE_CB_UNIT_CB_UNIT_HPP
#define SOURCE_CB_UNIT_CB_UNIT_HPP
#include <string>
#include <vector>

  namespace ClockWorks
  {
   namespace Game
   {
     class Unit
     {
     protected:

       std::string Name; //The name of the unit
       int ID; //Unit ID. Assumed to be unique.
       int AI; //Controller of the Unit. 0 = player.

       int HP[2]; //Current and Max HP of the Unit
       int MP[2]; //Cur/Max MP

       int HP_Modifier; 
       int MP_Modifier;

		 int HP_Bonus; //HP bonus from Equipment
		 int MP_Bonus; //MP Bonus from Equipment

		 std::vector<float> HP_Bonus_Mult;
		 std::vector<float> MP_Bonus_Mult;
		 std::vector<float> HP_Modifier_Mult;
		 std::vector<float> MP_Modifier_Mult;


		 int Level; //Level of Unit
		 int Affinity; //Affinity of Unit

		 int XP; //for PCs, this represents total EXP accrued. For NPCs, this represents EXP Gained when defeated in battle.
		 int NextLVL; //EXP required to level up
		 int GP; //Amount of money

		 /***************************************************************/
		 /*                         Statistics                          */
		 /***************************************************************/
		 /*      These values hold the 11 Base Character Statistics (7  */
		 /* visible and 4 hidden) that play their own specific roles to */
		 /* nearly everything a Unit does in-game. They are as follows: */
		 /***************************************************************/
		 /*                     Array Index Listing                     */
		 /* [0] - Attack (ATK)                                          */
		 /* [1] - Defense (DEF)                                         */
		 /* [2] - Power (Magic Attack) (PWR)                            */
		 /* [3] - Resistance (Magic Defense) (RES)                      */
		 /* [4] - Speed (SPD)                                           */
		 /* [5] - Evasion (EVA)                                         */
		 /* [6] - Accuracy (ACC)                                        */
		 /* [7] - Critical%                                             */
		 /* [8] - Spark% (Spell Critical)                               */
		 /* [9] - Fizzle%                                               */
		 /* [10] - Block% (Spell Block)                                 */
		 /* [11] - Initiative                                           */
		 /* [12] - Constitution                                         */
		 /***************************************************************/

		 int Statistics[13]; //The Base Stats
		 int Statistic_Modifier[13]; //Modifiers will affect these parameters
		 int Statistic_Bonus[13]; //Stat Bonuses from Equipment
		 std::vector<float> Statistic_Modifier_Mult[13]; //The in-battle mults
		 std::vector<float> Statistic_Bonus_Mult[13]; //The gear multipliers

		 /***************************************************************/
		 /*                       Elemental Stats                       */
		 /***************************************************************/
		 /*      These values control Elemental Attack, Defense, Absorb */
		 /* (Being healed by an element) and Immunity. All of these     */
		 /* will be implemented as an array of 7 variables, each being  */
		 /* associated to one, and only one, element, as follows:       */
		 /***************************************************************/
		 /*                     Array Index Listing                     */
		 /* [0] - Anything that is supposed to heal.                    */
		 /* [1] - Fire                                                  */
		 /* [2] - Air                                                   */
		 /* [3] - Water                                                 */
		 /* [4] - Earth                                                 */
		 /* [5] - Light                                                 */
		 /* [6] - Dark                                                  */
		 /* [7] - Base (Nonelemental)                                   */
		 /***************************************************************/

		 float Elemental_Attack[8]; // Elemental Attack
		 float Elemental_Defense[8]; // Elemental Defense


		 //int Elemental_Attack_Bonus[7]; // Elemental Attack Modifiers   
		 //int Elemental_Defense_Bonus[7]; // Elemental Defense Modifiers
		 std::vector<float> Elemental_Attack_Bonus_Mult[8]; //The gear multipliers
		 std::vector<float> Elemental_Defense_Bonus_Mult[8]; //The gear multipliers
		 //int Elemental_Attack_Bonus[7]; // Elemental Attack Modifiers   
		 //int Elemental_Defense_Bonus[7]; // Elemental Defense Modifiers

		 //int Elemental_Attack_Modifier[7]; // Elemental Attack Modifiers   
		 //int Elemental_Defense_Modifier[7]; // Elemental Defense Modifiers
		 std::vector<float> Elemental_Attack_Modifier_Mult[8]; //The battle multipliers
		 std::vector<float> Elemental_Defense_Modifier_Mult[8]; //The battle multipliers







		 //Absorb/Nullify flags: Healing, F, A, W, E, L, D. Absb>Null



		 /***************************************************************/
		 /*                     Status Effect Flags                     */
		 /***************************************************************/
		 /*      These flags control the presence and duration of any   */
		 /* status effect in this game that cannot be handled simply    */
		 /* by stat modifiers. Enclosed is a list of each index in the  */
		 /* array and what they WILL control. Refer to this list in the */
		 /* case of a discrepency.                                      */
		 /***************************************************************/
		 /*                     Array Index Listing                     */
		 /* [0] - POISON Flag, Intensity, Status is permanent           */
		 /* [1] - BURN Flag, Intensity                                  */
		 /* [2] - SLEEP Flag, Turns                                     */
		 /* [3] - BLIND Flag, Status is permanent                       */
		 /* [4] - HALT Timer, Time Units (SPD=1)                        */
		 /* [5] - SILENCE Flag, status is permanent                     */
		 /* [6] - STONE Flag, Status is permanent                       */
		 /* [7] - FORCED COMMAND flag, number represents forced command */
		 /* [8] - DOOM/DEAD flag (Turns, -1 for dead)                   */
		 /* [9] - IMPERVIOUS Timer, Turns                               */
		 /* [10] - BLESS Layers                                         */
		 /* [11] - REFLECT Flag, Iterations                             */
		 /* [12] - VANTAGE Flag, One Turn (as in Defend-Strike)         */
		 /* [13] - HASTE/SLOW Flag, Status is permanent                 */
		 /* [14] - DAMAGE SHIELD Intensity, Status is permanent         */
		 /* [15] - SHIELD Timer, Turns                                  */
		 /* [16] - REGEN Intensity, Status is permanent                 */
		 /* [17] - CALM Intensity, Status is permanent                  */
		 /* [18] - BLISS Intensity, (Intensity/Turns)                   */
		 /* [19] - IMAGE Layers                                         */
		 /* [20] - INVIS Timer, Turns                                   */
		 /* [21] - ANGEL Flag (revive amount/Turns)                     */
		 /* [22] - ABSORB Amount, Status is permanent                   */
		 /* [23] - BARRIER Threshold, Status is permanent               */
		 /***************************************************************/

		 float Status_Attack[24]; // Elemental Attack
		 float Status_Defense[24]; // Elemental Defense
		 std::vector<float> Status_Attack_Bonus_Mult[24]; //The gear multipliers
		 std::vector<float> Status_Defense_Bonus_Mult[24]; //The gear multipliers
		 std::vector<float> Status_Attack_Modifier_Mult[24]; //The battle multipliers
		 std::vector<float> Status_Defense_Modifier_Mult[24]; //The battle multipliers


		 int Status_Effect_Flag[24];	
		 int Status_Effect_Default[24]; //Status Defaults (Or rather, initial values...)
		 int Status_Effect_Default_Bonus[24]; //Status Defaults (Or rather, initial values...)

		 bool is_Fleeing; //defaulted to false

		 int Cast_Speed; //NOT the same as normal speed!

		 int Charge_Time[2]; //Time Element [0] = Normal, [1] = Casting

		 int Current_Ability; //The Spell currently being cast

		 // get rid of below line
		 int Ability_Flags[8]; //All-purpose ability flags.

		 int Current_Target; //The Target of Spell
		 /***************************************************************/
		 /*              Sentinel Values for CurrentTarget              */
		 /***************************************************************/
		 /* -1 = ALLY PARTY                                             */
		 /* -2 = ENEMY PARTY                                            */
		 /* -3 = NO TARGET (either self only or target everything)      */
		 /* -4 = NO TARGET (spell will fizzle)                          */
		 /***************************************************************/

		 std::string Equipment[5]; //The equipment slots.
		 std::vector<int> Equipment_Types[5]; //THe types of everything
		 std::vector<int> Equipment_Modifiers[5]; //Add-ons via equipment.
		 //std::string Weapon_Equipped;
		 //std::vector<int> Weapon_Types;
		 //std::string Shield_Equipped; //Or other weapon.
		 //std::vector<int> Shield_Types;
		 //std::string Helm_Equipped;
		 //std::vector<int> Helm_Types;
		 //std::string Armor_Equipped;
		 //std::vector<int> Armor_Types;
		 //std::string Access_Equipped;
		 //std::vector<int> Access_Types;



		 std::vector<int> Abilities_Known; 
		 std::vector<int> Ability_Modifiers;

	     //std::vector<int> Auxiliary_Flags;
		 //std::vector<int> Auxiliary_Flag_Bonuses;
		 //std::vector<int> Auxiliary_Flag_Modifiers;


		 int Item_Capacity;
		 std::vector<std::string> Items;

		 int Growth_Table; //ID of the growth table used.

		 std::vector<int> Passives_Known; //Passives the Unit knows
		 std::vector<int> Passive_Modifiers; //Modifier to Known Passives.

		 int Passive_Capacity; //Number of Passives Character may equip.
		 std::vector<int> Passives; //Passives currently in use
		 std::vector<int> Innate_Passives; //Passives granted by equipment or nature




		 int Attack_Command; //The Command used to Attack
		 int Passive_Command; //The Command that does NOT halt casting. Usually WAIT.

		 int Attack_Type[2]; //there's a lot going into this one...
		 int Attack_Type_Default[2]; //Defaults.

		 int Command_Capacity; //Maximum number of commands. For Clock_Bridges Proper, this will be 3.
		 std::vector<int> Command_List; //This excludes Attack



		 void init(); //for failure
		 bool init(std::string data); //Loads data from a string

		 void zero_Out_Modifiers(); //Initializes Modifiers to 0.

		 void resolve_Battle_Effects(); //Resolves Battle stuff like statuses.



	 public:	

		 static std::string UNIT_FILE;
		 static std::string GROWTH_FILE;

		 //constructor/destructor

		 Unit();

		 Unit(const int ID);

		 ~Unit(); //destructor  so a Unit pointer can resolve properly.

		 //start off with get/set functions


		 std::string Parse_Combat_Statistics(const std::string& parseme, bool modify = false);
		 std::string Parse_Noncombat_Statistics(const std::string& parseme);

		 inline std::string get_Name() const{return Name;}
		 inline void set_Name(const std::string& new_name){Name = new_name;}

		 inline int get_ID() const{return ID;}

		 //void set_ID(const int x);



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





