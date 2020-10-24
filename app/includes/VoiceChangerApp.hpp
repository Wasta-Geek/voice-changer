#pragma once

#include <iostream>
#include "PortAudioWrapper.hpp"

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
		PortAudioWrapper _port_audio_wrapper;
	};
}