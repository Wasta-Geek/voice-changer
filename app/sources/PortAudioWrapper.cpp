#include <iostream>
#include "PortAudioWrapper.hpp"

namespace Chelmi
{
	PortAudioWrapper::PortAudioWrapper(FilePlayerManager& file_player_manager) : _user_data({ file_player_manager })
	{ }

	PortAudioWrapper::~PortAudioWrapper()
	{
		PaError err = Pa_Terminate();
		if (err != paNoError)
			std::cout << "PortAudio error while closing: " << Pa_GetErrorText(err) << std::endl;
	}

	bool PortAudioWrapper::initialize()
	{
		PaError err = Pa_Initialize();
		if (err != paNoError)
		{
			std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
			return false;
		}
		return true;
	}

	bool PortAudioWrapper::createStream()
	{
		PaStream* main_stream;

		PaDeviceIndex input_device_index = Pa_GetHostApiInfo(paInDevelopment)->defaultInputDevice;

		PaStreamParameters input_parameters;
		input_parameters.device = input_device_index;
		input_parameters.channelCount = NUMBER_OF_CHANNELS;
		input_parameters.sampleFormat = paFloat32;
		input_parameters.hostApiSpecificStreamInfo = NULL;
		input_parameters.suggestedLatency = Pa_GetDeviceInfo(input_device_index)->defaultLowInputLatency;



		PaDeviceIndex output_device_index = _getDeviceIndexFromName(VIRTUAL_MICROPHONE_DEVICE_NAME.c_str(), paInDevelopment);
		if (input_device_index == paNoDevice)
		{
			std::cout << "Please make sure you have installed VB virtual audio cable correctly." << std::endl;
			return false;
		}

		PaStreamParameters output_parameters;
		output_parameters.device = output_device_index;
		output_parameters.channelCount = NUMBER_OF_CHANNELS;
		output_parameters.sampleFormat = paFloat32;
		output_parameters.hostApiSpecificStreamInfo = NULL;
		output_parameters.suggestedLatency = Pa_GetDeviceInfo(output_device_index)->defaultLowOutputLatency;

		PaError err = Pa_OpenStream(&main_stream,
			&input_parameters, &output_parameters,
			SAMPLE_RATE, paFramesPerBufferUnspecified,
			paNoFlag,
			&PortAudioWrapper::_portAudioCallback, &this->_user_data);

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

	PaDeviceIndex PortAudioWrapper::_getDeviceIndexFromName(const char* device_name, PaHostApiIndex device_api) const
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

	int PortAudioWrapper::_portAudioCallback(const void* input_buffer, void* output_buffer, unsigned long frames_per_buffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* raw_user_data)
	{
		float* out = (float*)output_buffer;
		const float* in = (const float*)input_buffer;
		unsigned int i;
		(void)timeInfo; /* Prevent unused variable warnings. */
		(void)statusFlags;


		if (raw_user_data == nullptr)
		{
			for (i = 0; i < frames_per_buffer * NUMBER_OF_CHANNELS; i++)
			{
				* out++ = *in++;  /* left */
			}
		}
		else
		{
			UserData* user_data = static_cast<UserData*>(raw_user_data);
			for (i = 0; i < frames_per_buffer * NUMBER_OF_CHANNELS; i++)
			{
				float output_value = *in++;
				auto &file_samples_list =  user_data->file_player_manager.getCurrentFileSamples();
				for (auto& _file_samples : file_samples_list)
				{
					if (_file_samples.availableSample())
					{
						output_value += _file_samples.consumeNextSample() * 0.5;
					}
				}
				user_data->file_player_manager.clearAlreadyReadFileSamples();
				*out++ = output_value;
			}
		}
		return paContinue;
	}
}