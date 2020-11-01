#pragma once

#include <string>
#include <future>
#include <map>
#include "FileFormats.hpp"

namespace Chelmi
{
	class FilePlayerManager
	{
	public:
		FilePlayerManager();
		bool playFile(e_FileFormat file_format, const std::string& relative_file_path);
	private:
		void _playWavFile(const std::string& relative_file_path, std::promise<bool> play_file_future);

		const std::string _default_file_folder_path;
		std::map<e_FileFormat, void(FilePlayerManager::*)(const std::string& relative_file_path, std::promise<bool> play_file_future)> _player_function_map;
	};
}