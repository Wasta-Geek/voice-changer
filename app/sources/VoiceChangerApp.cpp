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

	bool VoiceChangerApp::initialize()
	{
		return _port_audio_wrapper.initialize() && _port_audio_wrapper.createStream();
	}

	void VoiceChangerApp::start()
	{
	}

	void VoiceChangerApp::quit()
	{

	}
}