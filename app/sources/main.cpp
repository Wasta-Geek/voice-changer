#include <iostream>
#include <thread>
#include "portaudio.h"
#define _AMD64_
#include <windows.h>

constexpr unsigned SAMPLE_RATE = 44100;
constexpr PaSampleFormat PA_SAMPLE_TYPE = paFloat32;
constexpr unsigned FRAMES_PER_BUFFER = 64;
constexpr const char* VIRTUAL_MICROPHONE_DEVICE_NAME = "CABLE Input (VB-Audio Virtual C";


int patestCallback(const void* inputBuffer, void* outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void* userData)
{
	float* out = (float*)outputBuffer;
	const float* in = (const float*)inputBuffer;
	unsigned int i;
	(void)timeInfo; /* Prevent unused variable warnings. */
	(void)statusFlags;

	for (i = 0; i < framesPerBuffer; i++)
	{
		*out++ = *in++;  /* left */
	}
	return paContinue;
}

PaDeviceIndex getDeviceIndexFromName(const char* device_name, PaHostApiIndex device_api)
{
	int numDevices;
	numDevices = Pa_GetDeviceCount();
	if (numDevices < 0)
	{
		std::cout << "ERROR: Pa_CountDevices returned " << numDevices << std::endl;
		return paNoDevice;
	}

	const   PaDeviceInfo* deviceInfo;
	for (auto api_index = 0; api_index < Pa_GetHostApiCount(); api_index++)
	{
		for (auto i = 0; i < Pa_GetDeviceCount(); ++i)
		{
			deviceInfo = Pa_GetDeviceInfo(i);
			if (Pa_GetDeviceInfo(i)->hostApi == api_index)
			{
				printf("API: %d -> Device: %s\n", api_index, deviceInfo->name);
			}
		}
	}
	for (auto i = 0; i < numDevices; i++)
	{
		deviceInfo = Pa_GetDeviceInfo(i);
		std::cout << deviceInfo->name << std::endl;
		if (deviceInfo->hostApi == device_api && strcmp(deviceInfo->name, device_name) == 0)
		{
			return i;
		}
	}
	return paNoDevice;
}

bool initializePortaudio()
{
	PaError err = Pa_Initialize();
	if (err != paNoError)
	{
		std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
		return false;
	}
	return true;
}

void clearPortaudio()
{
	PaError err = Pa_Terminate();
	if (err != paNoError)
		std::cout << "PortAudio error while closing: " << Pa_GetErrorText(err) << std::endl;
}

bool createStream()
{
	PaStream* main_stream;


	PaDeviceIndex input_device_index = Pa_GetHostApiInfo(paInDevelopment)->defaultInputDevice;

	PaStreamParameters input_parameters;
	input_parameters.device = input_device_index;
	input_parameters.channelCount = 1;
	input_parameters.sampleFormat = paFloat32;
	input_parameters.hostApiSpecificStreamInfo = NULL;
	input_parameters.suggestedLatency = Pa_GetDeviceInfo(input_device_index)->defaultLowInputLatency;



	PaDeviceIndex output_device_index = getDeviceIndexFromName(VIRTUAL_MICROPHONE_DEVICE_NAME, paInDevelopment);
	if (input_device_index == paNoDevice)
	{
		std::cout << "Please make sure you have installed VB virtual audio cable correctly." << std::endl;
		return false;
	}

	PaStreamParameters output_parameters;
	output_parameters.device = output_device_index;
	output_parameters.channelCount = 1;
	output_parameters.sampleFormat = paFloat32;
	output_parameters.hostApiSpecificStreamInfo = NULL;
	output_parameters.suggestedLatency = Pa_GetDeviceInfo(output_device_index)->defaultLowOutputLatency;

	PaError err = Pa_OpenStream(&main_stream,
		&input_parameters, &output_parameters,
		SAMPLE_RATE, paFramesPerBufferUnspecified,
		paNoFlag,
		patestCallback, NULL);

	if (err != paNoError)
	{
		std::cout << "ERROR DURING OPENING MAIN STREAM: " << Pa_GetErrorText(err) << std::endl;
		return false;
	}


	err = Pa_StartStream(main_stream);

	if (err != paNoError)
	{
		std::cout << "ERROR DURING STARTING MAIN STREAM: " << Pa_GetErrorText(err) << std::endl;
		return false;
	}
	return true;
}

void loop()
{
	if (RegisterHotKey(
		NULL,
		1,
		MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT,
		VK_F20) && RegisterHotKey(NULL, 2, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, VK_F24))
	{
		std::cout << "Hotkeys registered: loop starts now." << std::endl;

		MSG msg = { 0 };
		while (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			if (msg.message == WM_HOTKEY)
			{
				switch (msg.wParam)
				{
				case 1: /// G1
					break;
				case 2:  /// G6
					return;
				default:
					break;
				}
			}
		}
	}
}

int main(void)
{
	if (!initializePortaudio())
		return 1;

	if (!createStream())
		return 2;

	//f/*or (auto i = 0; i < 10; i++)
	//{
	//	std::cout << "Sleeping... " << i << std::endl;

	//	std::this_thread::sleep_for(std::chrono::seconds(1));
	//}*/

	loop();
	clearPortaudio();
	return 0;
}