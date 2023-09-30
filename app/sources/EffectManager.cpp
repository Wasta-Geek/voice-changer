#include "EffectManager.hpp"
#include "effects/EchoEffect.hpp"

namespace Chelmi
{
	EffectManager::EffectManager()
	{
		_registered_effects.try_emplace(e_effect::ECHO, std::make_unique<EchoEffect>(1.0f, 75));
	}

	void EffectManager::applyEffect(e_effect effect)
	{
		if (_registered_effects.find(effect) != _registered_effects.end())
		{
			AEffect &effect_object = *_registered_effects.at(effect).get();
			// Change later when release event is catched
			effect_object.set(!effect_object.isEnabled());
		}
	}
}