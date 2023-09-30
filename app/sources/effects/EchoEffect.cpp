#include "effects/EchoEffect.hpp"
// T¨MP
#include <iostream>

namespace Chelmi
{
	EchoEffect::EchoEffect(float time_delay, int volume_percent): _time_delay(time_delay), _volume_percent(volume_percent)
	{
	}

	float EchoEffect::getCurrentFrame(float input_frame)
	{
		std::cout << "COUCOu" << std::endl;
		return 0.0f;
	}
}