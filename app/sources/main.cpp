#include <iostream>
#include "portaudio.h"

int main(void)
{
	PaError err = Pa_Initialize();
	if (err != paNoError)
	{
		std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
	}

	err = Pa_Terminate();
	if (err != paNoError)
		std::cout << "PortAudio error while closing: " << Pa_GetErrorText(err) << std::endl;

	return 0;
}