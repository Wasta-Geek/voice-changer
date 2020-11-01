#include <filesystem>
#include <iostream>
#include <thread>
#include <utility>
#include "sndfile.h"
#include "FilePlayerManager.hpp"

#ifndef RESOURCES_FOLDER_PATH
	// TODO Crap
	#define RESOURCES_FOLDER_PATH = std::filesystem::current_path().parent_path().parent_path().parent_path().string()
#endif

namespace Chelmi
{
	FilePlayerManager::FilePlayerManager(): _default_file_folder_path((std::filesystem::path(RESOURCES_FOLDER_PATH) / "sounds").string())
	{
		_player_function_map.insert(std::make_pair(e_FileFormat::WAV, &FilePlayerManager::_playWavFile));
	}

	bool FilePlayerManager::playFile(e_FileFormat file_format, const std::string& relative_file_path)
	{
		auto find_iterator = _player_function_map.find(file_format);
		if (find_iterator != _player_function_map.end())
		{
			std::promise<bool> play_file_promise;
			// TODO Future should be used by client to await if needed
			std::future<bool> play_file_future = play_file_promise.get_future();
			std::thread worker_thread(find_iterator->second, this, relative_file_path, std::move(play_file_promise));
			worker_thread.detach();
			return true;
		}
		return false;
	}

	void FilePlayerManager::_playWavFile(const std::string& relative_file_path, std::promise<bool> play_file_future)
	{
		SF_INFO info;
		const std::string& absolute_file_path = (std::filesystem::path(_default_file_folder_path) / "wav" / relative_file_path).make_preferred().string();
		SNDFILE *file = sf_open(absolute_file_path.c_str(), SFM_READ, &info);
		
		if (sf_error(file) != SF_ERR_NO_ERROR)
		{
			std::cerr << sf_strerror(file) << absolute_file_path << std::endl;
			return;
		}
		
		std::unique_ptr<float[]> samples = std::make_unique<float[]>(info.frames * info.channels);

		sf_count_t frames_read = sf_readf_float(file, samples.get(), info.frames);
		if (sf_close(file) != SF_ERR_NO_ERROR)
		{
			std::cerr << sf_strerror(file) << absolute_file_path << std::endl;
		}
	}
}