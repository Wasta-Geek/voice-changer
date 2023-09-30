#pragma once

#include <memory>
#include <map>
#include "AAudioSampleProducer.hpp"
#include "effects/AEffect.hpp"
#include "effects/types.hpp"

namespace Chelmi
{
	class EffectManager: public AAudioSampleProducer
	{
	public:
		EffectManager();
		void applyEffect(e_effect effect);
	private:
		std::map<e_effect, std::unique_ptr<AEffect>> _registered_effects;
	};
}