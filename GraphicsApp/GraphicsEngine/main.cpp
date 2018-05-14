#include "GraphicsEngineApp.h"

int main() {
	
	// allocation
	auto app = new GraphicsEngineApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}