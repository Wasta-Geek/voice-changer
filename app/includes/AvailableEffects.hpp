#pragma once



namespace Chelmi
{
	class AEffect
	{
	public:
		virtual float getCurrentFrame(float input_frame) = 0;
	private:

	};

	class EchoEffect: public AEffect
	{
	public:
		EchoEffect(float time_delay);
	private:
		float _time_delay;
	};
}