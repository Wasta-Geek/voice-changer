// voice-changer.cpp : définit le point d'entrée de l'application.
//

#include "VoiceChangerApp.hpp"

namespace Chelmi
{
	VoiceChangerApp::VoiceChangerApp()
	{

	}

	VoiceChangerApp::~VoiceChangerApp()
	{
	}

	///TODO Shouldn't be included here
	#include <windows.h>
	bool VoiceChangerApp::initialize()
	{
		bool port_audio_initialized = _port_audio_wrapper.initialize() && _port_audio_wrapper.createStream();
		bool hotkey_manager_initialized = _hotkey_manager.addHotkeyEvent({ VK_F20, std::bind(&VoiceChangerApp::_show, this) })
			&& _hotkey_manager.addHotkeyEvent({ VK_F24, std::bind(&VoiceChangerApp::quit, this) });
		return port_audio_initialized && hotkey_manager_initialized;
	}

	void VoiceChangerApp::start()
	{
		_hotkey_manager.start();
	}

	void VoiceChangerApp::quit()
	{
		_hotkey_manager.quit();
	}

	void VoiceChangerApp::_show()
	{
		std::cout << "SHOW" << std::endl;
	}
}