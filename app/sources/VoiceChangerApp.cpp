// voice-changer.cpp : définit le point d'entrée de l'application.
//

#include "VoiceChangerApp.hpp"

namespace Chelmi
{
	VoiceChangerApp::VoiceChangerApp(): _port_audio_wrapper(_file_player_manager)
	{

	}

	VoiceChangerApp::~VoiceChangerApp()
	{
	}

	///TODO Shouldn't be included here
	#include <windows.h>
	bool VoiceChangerApp::initialize()
	{
		bool port_audio_initialized = _port_audio_wrapper.initialize() && _port_audio_wrapper.createStream();
		bool hotkey_manager_initialized =
			_hotkey_manager.addHotkeyEvent({ VK_F19, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "LE QUOI.wav") })
			/*_hotkey_manager.addHotkeyEvent({ VK_F19, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "ah.wav") })*/
			
			&& _hotkey_manager.addHotkeyEvent({ VK_F20, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "sardoche.wav") })
			
			//&& _hotkey_manager.addHotkeyEvent({ VK_F21, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "steam.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F21, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "murloc.wav") })
			
			//&& _hotkey_manager.addHotkeyEvent({ VK_F22, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "maite.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F22, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "lalalala-SOAD.wav") })
			/*&& _hotkey_manager.addHotkeyEvent({ VK_F22, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "jesuispasvenupoursouffrir.wav") })*/

			//&& _hotkey_manager.addHotkeyEvent({ VK_F23, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "ok boomer.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F23, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "steam.wav") })
			
			//&& _hotkey_manager.addHotkeyEvent({ VK_F24, std::bind(&VoiceChangerApp::quit, this) });
			//&& _hotkey_manager.addHotkeyEvent({ VK_F24, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "jeanne_au_secours.wav") });
			&& _hotkey_manager.addHotkeyEvent({ VK_F24, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "c'est honteux.wav") });

		return port_audio_initialized && hotkey_manager_initialized;	}

	void VoiceChangerApp::start()
	{
		_hotkey_manager.start();
	}

	void VoiceChangerApp::quit()
	{
		_hotkey_manager.quit();
	}

	void VoiceChangerApp::_show()
	{
		std::cout << "DUMMY" << std::endl;
	}

	bool VoiceChangerApp::_playFile(e_FileFormat file_format, const std::string &file_path)
	{
		return _file_player_manager.playFile(file_format, file_path);
	}
}