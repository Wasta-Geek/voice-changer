#pragma once

#include<functional>
#include "AAudioSampleProducer.hpp"

namespace Chelmi
{
	struct UserData
	{
		std::vector<std::reference_wrapper<AAudioSampleProducer>> audio_sample_producers;
	};
}