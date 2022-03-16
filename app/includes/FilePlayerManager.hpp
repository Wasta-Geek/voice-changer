#pragma once

#include <string>
#include <future>
#include <map>
#include <list>
#include <mutex>
#include "FileFormats.hpp"

namespace Chelmi
{
	struct FileSamples
	{
		float consumeNextSample()
		{
			float next_sample = samples[current_index++];
			return next_sample;
		}

		bool availableSample() const
		{
			return samples && current_index < samples_number * 2; // TODO REAL NUMBER OF CHANNELS
		}

		std::unique_ptr<float[]> samples;
		unsigned long samples_number;
		unsigned long current_index = 0;
	};

	class FilePlayerManager
	{
	public:
		FilePlayerManager();
		bool playFile(e_FileFormat file_format, const std::string& relative_file_path);
		std::list<FileSamples> &getCurrentFileSamples();
		void clearAlreadyReadFileSamples();
		void clearAllFileSamples();
	private:
		void _playWavFile(const std::string& relative_file_path, std::promise<bool> play_file_future);
		void _addFileSample(FileSamples &&file_samples);

		const std::string _default_file_folder_path;
		std::map<e_FileFormat, void(FilePlayerManager::*)(const std::string& relative_file_path, std::promise<bool> play_file_future)> _player_function_map;
		std::list<FileSamples> _current_file_samples;
		std::mutex _mutex;
	};
}