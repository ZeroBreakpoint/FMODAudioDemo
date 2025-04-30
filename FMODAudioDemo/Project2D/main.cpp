#include "Application2D.h"
#include "SoundManager.h"

int main() {

	// Allocate the application object
	auto app = new Application2D();

	// Initialise the app and enter the main loop
	app->run("Bradley Robertson - Audio Programming", 1280, 720, false);

	// Deallocate the app object to free memory
	delete app;

	system("pause");

	return 0;
}