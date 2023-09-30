#pragma once

#include "AEffect.hpp"

namespace Chelmi
{
	class EchoEffect : public AEffect
	{
	public:
		EchoEffect(float time_delay, int volume_percent);
		float getCurrentFrame(float input_frame) override;
	private:
		float _time_delay;
		int _volume_percent;
	};
}