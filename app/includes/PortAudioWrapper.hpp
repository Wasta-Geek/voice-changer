#pragma once

#include "portaudio.h"

namespace Chelmi
{
	class PortAudioWrapper
	{
	public:
		~PortAudioWrapper();
		bool initialize();
		bool createStream();
	private:
		PaDeviceIndex _getDeviceIndexFromName(const char* device_name, PaHostApiIndex device_api) const;
		static int _portAudioCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData);

		unsigned SAMPLE_RATE = 44100;
		PaSampleFormat PA_SAMPLE_TYPE = paFloat32;
		unsigned FRAMES_PER_BUFFER = 64;
		const char* VIRTUAL_MICROPHONE_DEVICE_NAME = "CABLE Input (VB-Audio Virtual C";
	};
}