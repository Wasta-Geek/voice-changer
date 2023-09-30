#include "effects/AEffect.hpp"

namespace Chelmi
{
	AEffect::AEffect() : _enabled(false)
	{

	}

	void AEffect::set(bool enabled)
	{
		_enabled = enabled;
	}

	bool AEffect::isEnabled() const
	{
		return _enabled;
	}
}