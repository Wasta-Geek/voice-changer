#pragma once

#include "portaudio.h"
#include "FilePlayerManager.hpp"
#include "UserData.hpp"

namespace Chelmi
{
	class PortAudioWrapper
	{
	public:
		PortAudioWrapper(FilePlayerManager &file_player_manager);
		~PortAudioWrapper();
		bool initialize();
		bool createStream();

		static inline unsigned SAMPLE_RATE = 44100;
		static inline PaSampleFormat PA_SAMPLE_TYPE = paFloat32;
		static inline unsigned FRAMES_PER_BUFFER = 64;
		static inline unsigned NUMBER_OF_CHANNELS = 2;
		static inline std::string VIRTUAL_MICROPHONE_DEVICE_NAME = "CABLE Input (VB-Audio Virtual C";
	private:
		PaDeviceIndex _getDeviceIndexFromName(const char* device_name, PaHostApiIndex device_api) const;
		static int _portAudioCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData);

		UserData _user_data;
		//FilePlayerManager &_file_player_manager;
	};
}