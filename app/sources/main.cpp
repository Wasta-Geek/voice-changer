#include <iostream>
#include <thread>
#include "portaudio.h"

constexpr unsigned SAMPLE_RATE = 44100;
constexpr PaSampleFormat PA_SAMPLE_TYPE = paFloat32;
constexpr unsigned FRAMES_PER_BUFFER = 64;
constexpr const char* VIRTUAL_MICROPHONE_DEVICE_NAME = "CABLE Input (VB-Audio Virtual C";

typedef struct
{
	float left_phase = 0.0;
	float right_phase = 0.0;
	bool ascending = false;
}
paTestData;

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
	
	paTestData * data = (paTestData*)userData;
	for (i = 0; i < framesPerBuffer; i++)
	{
		*out++ = *in++;  /* left */
	}
	return paContinue;
}
static paTestData data;

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

int main(void)
{
	PaError err = Pa_Initialize();
	if (err != paNoError)
	{
		std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
	}


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
		return 1;
	}

	PaStreamParameters output_parameters;
	output_parameters.device = output_device_index;
	output_parameters.channelCount = 1;
	output_parameters.sampleFormat = paFloat32;
	output_parameters.hostApiSpecificStreamInfo = NULL;
	output_parameters.suggestedLatency = Pa_GetDeviceInfo(output_device_index)->defaultLowOutputLatency;

	err = Pa_OpenStream(&main_stream,
		&input_parameters, &output_parameters,
		SAMPLE_RATE, paFramesPerBufferUnspecified,
		paNoFlag,
		patestCallback, &data);

	if (err != paNoError)
		std::cout << "ERROR DURING OPENING MAIN STREAM: " << Pa_GetErrorText(err) << std::endl;


	err = Pa_StartStream(main_stream);

	if (err != paNoError)
		std::cout << "ERROR DURING STARTING MAIN STREAM: " << Pa_GetErrorText(err) << std::endl;


	for (auto i = 0; i < 10; i++)
	{
		std::cout << "Sleeping... " << i << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}


	err = Pa_Terminate();
	if (err != paNoError)
		std::cout << "PortAudio error while closing: " << Pa_GetErrorText(err) << std::endl;

	return 0;
}