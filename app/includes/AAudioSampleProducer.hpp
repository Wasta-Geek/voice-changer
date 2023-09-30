#pragma once

#include <mutex>
#include <list>
#include "AudioSample.hpp"

namespace Chelmi
{
	class AAudioSampleProducer
	{
	public:
		std::list<AudioSample>& getCurrentAudioSamples();
		void addFileSample(AudioSample&& audio_samples);
		void clearAlreadyReadAudioSamples();
		void clearAllAudioSamples();
	protected:
		std::list<AudioSample> _current_audio_samples;
		std::mutex _mutex;
	};
}