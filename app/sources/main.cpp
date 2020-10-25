#include <iostream>
#include "VoiceChangerApp.hpp"

int main(void)
{
	Chelmi::VoiceChangerApp app;
	if (!app.initialize())
		return 1;

	app.start();

	//f/*or (auto i = 0; i < 10; i++)
	//{
	//	std::cout << "Sleeping... " << i << std::endl;

	//	std::this_thread::sleep_for(std::chrono::seconds(1));
	//}*/

	return 0;
}