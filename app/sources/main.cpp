#include <iostream>
#include <thread>
#define _AMD64_
#include <windows.h>

#include "VoiceChangerApp.hpp"

void loop()
{
	if (RegisterHotKey(
		NULL,
		1,
		MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT,
		VK_F20) && RegisterHotKey(NULL, 2, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, VK_F24))
	{
		std::cout << "Hotkeys registered: loop starts now." << std::endl;

		MSG msg = { 0 };
		while (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			if (msg.message == WM_HOTKEY)
			{
				switch (msg.wParam)
				{
				case 1: /// G1
					break;
				case 2:  /// G6
					return;
				default:
					break;
				}
			}
		}
	}
}

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

	loop();
	return 0;
}