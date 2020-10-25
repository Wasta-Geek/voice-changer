#pragma once

#include <iostream>
#include "PortAudioWrapper.hpp"
#include "HotKeyManager.hpp"

namespace Chelmi
{
	class VoiceChangerApp
	{
	public:
		VoiceChangerApp();
		~VoiceChangerApp();
		bool initialize();
		void start();
		void quit();

	private:
		void _show();

		PortAudioWrapper _port_audio_wrapper;
		HotKeyManager _hotkey_manager;
	};
}