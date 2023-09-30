#pragma once

namespace Chelmi
{
	struct AudioSample
	{
		float consumeNextSample()
		{
			float next_sample = samples[current_index++];
			return next_sample;
		}

		bool availableSample() const
		{
			return samples && current_index < samples_number * 2; // TODO REAL NUMBER OF CHANNELS
		}

		std::unique_ptr<float[]> samples;
		unsigned long samples_number;
		unsigned long current_index = 0;
	};
}