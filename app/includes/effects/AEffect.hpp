#pragma once

namespace Chelmi
{
	class AEffect
	{
	public:
		AEffect();
		virtual float getCurrentFrame(float input_frame) = 0;
		void set(bool enabled);
		bool isEnabled() const;
	protected:
	private:
		bool _enabled;
	};
}