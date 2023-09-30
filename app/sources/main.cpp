#include <iostream>
#include "VoiceChangerApp.hpp"

int main(void)
{
	Chelmi::VoiceChangerApp app;
	if (!app.initialize())
		return 1;

	app.start();

	return 0;
}