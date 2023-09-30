#include <iostream>
#include <utility>
#include "AAudioSampleProducer.hpp"

namespace Chelmi
{
	std::list<AudioSample>& AAudioSampleProducer::getCurrentAudioSamples()
	{
		return _current_audio_samples;
	}

	void AAudioSampleProducer::clearAlreadyReadAudioSamples()
	{
		//std::async(std::launch::async, [=]() {
		std::scoped_lock lock(_mutex);
		_current_audio_samples.erase(
			std::remove_if(_current_audio_samples.begin(),
				_current_audio_samples.end(),
				[](const AudioSample& file_samples) {
					if (!file_samples.availableSample())
						std::cout << "remove ! " << std::endl;
					return !file_samples.availableSample(); }), _current_audio_samples.end());
		//});
	}

	void AAudioSampleProducer::clearAllAudioSamples()
	{
		std::scoped_lock lock(_mutex);
		_current_audio_samples.clear();
	}

	void AAudioSampleProducer::addFileSample(AudioSample&& audio_samples)
	{
		std::scoped_lock lock(_mutex);
		_current_audio_samples.emplace_back(std::forward<AudioSample>(audio_samples));
	}

}