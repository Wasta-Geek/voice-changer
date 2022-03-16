#pragma once

#include <iostream>
#include "PortAudioWrapper.hpp"
#include "HotKeyManager.hpp"
#include "FilePlayerManager.hpp"
#include "AvailableEffects.hpp"

namespace Chelmi
{
	class VoiceChangerApp
	{
	public:
		VoiceChangerApp();
		~VoiceChangerApp();
		bool initialize();
		void start();
		void quit();
	private:
		void _show();
		bool _playFile(e_FileFormat file_format, const std::string& file_path);
		void _clearAllFuturesEffects();


		PortAudioWrapper _port_audio_wrapper;
		FilePlayerManager _file_player_manager;
		HotKeyManager _hotkey_manager;
		//std::array<AEffect, 4> _favorite_effects;
	};
}