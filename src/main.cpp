
#include "clockworks/game/unit.hpp"


int main() {
  ClockWorks::game::unit::init(2,12,8,2,26,2);
  
  ClockWorks::game::unit alice;
  alice.generate_test_unit();

  ClockWorks::game::unit bob(alice.str());

  std::cout << alice << std::endl << std::endl;
  std::cout << bob << std::endl << std::endl;

  std::cout << "alice is " << ( (alice.str() == bob.str()) ? "equal (YAY!)" : "NOT EQUAL (Boo!)" )<< " to bob." << std::endl;

  return 0;
}



/*
//Commenting out Ryan's main to preserve it while I hijack it.

#pragma warning(disable : 4426) //'constexpr' was ignored (class literal types are not yet supported)

#include "clockworks/tinycpp.hpp"
#include "clockworks/util/delegate.hpp"
#include "clockworks/util/dispatcher.hpp"
#include "clockworks/display/window.hpp"
#include "clockworks/std/printf.hpp"
#include "clockworks/std/pair.hpp"

bool MainLoop = true;
bool OnClose() {
	MainLoop = false;
	return false;
}

int main(int argc, char **argv) {
	(void)argc, argv;
	ClockWorks::std::printf("Welcome to ClockWorks, a (one day) cross-platform, forward-compatable,/n/tOpenGL 2.1 3D game libray.\n\n"
							"Sorry there isn't much to see!\n");
	ClockWorks::Display::Window win;
	win.OnClose.push_back(ClockWorks::Util::Delegate<bool()>::FromFunction<&OnClose>());
	win.Show();
	do { win.PumpOSQueue(); }
	while(MainLoop)  ;
	return 0;
}

*/
