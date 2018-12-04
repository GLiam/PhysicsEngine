//*!--------------------------------!*//
//*!	Date: Feb 7 2018
//*!	Last edit: Dec 4 2018
//*!	Programmer : Liam Gates
//*!	Role: Main Dev
//*!	
//*!	Programmer : @apscodes
//*!	Role: Memory leak fixer
//*!--------------------------------!*//


#include "Physics_EngineApp.h"

int main() {
	
	// allocation
	auto app = new Physics_EngineApp();

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}
