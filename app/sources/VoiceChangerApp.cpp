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

	bool VoiceChangerApp::initialize()
	{
		bool port_audio_initialized = _port_audio_wrapper.initialize() && _port_audio_wrapper.createStream();
		bool hotkey_manager_initialized =
			// -- Numerics / symbols line
			_hotkey_manager.addHotkeyEvent({ VK_F13, false, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "LE QUOI.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F14, false, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "sardoche.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F15, false, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "oskur.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F16, false, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "maite.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F17, false, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "jeanne_au_secours.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F18, false, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "c'est honteux.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F19, false, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "non meme.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F20, false, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "my body is ready.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F21, false, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "jesuispasvenupoursouffrir.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F22, false, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "incroyable-du-cul-monsieur-pot-de-beurre.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F23, false, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "saucisses.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F24, false, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "nous-sommes-en-guerre.wav") })

			// 1st characters line
			&& _hotkey_manager.addHotkeyEvent({ VK_F13, true, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "fantabob - ta gueule.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F14, true, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "bonjour paris.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F15, true, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "jchui trop bg.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F16, true, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "russian boy - chocolate cry.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F17, true, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "leviosa.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F18, true, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "bigard - le murloc.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F19, true, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "bigard - c'est moi qui te chie dessus maintenant.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F20, true, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "murloc.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F21, true, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "mais oui c'est clair.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F22, true, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "bien evidemment.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F23, true, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "and-his-name-is-john-cena.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F24, true, false, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "Attendez mais c'est de la merde ce jeux.wav") })
			// 2nd characters line
			&& _hotkey_manager.addHotkeyEvent({ VK_F13, false, true, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "titanic-parody.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F14, false, true, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "darude-sandstorm-flute.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F15, false, true, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "take on me bad flute.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F16, false, true, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "naruto bad flute.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F17, false, true, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "naruto sadness bad flute.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F18, false, true, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "SON DE LA POLICE.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F19, false, true, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "darkness_my_old_friend.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F20, false, true, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "Taisez vous.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F21, false, true, false, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "On va niquer ce soir.wav") })
			// 3rd characters line
			&& _hotkey_manager.addHotkeyEvent({ VK_F13, false, false, true, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "avast.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F14, false, false, true, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "steam.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F15, false, false, true, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "knock-knock.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F16, false, false, true, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "ah.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F17, false, false, true, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "merci-la-gueuse.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F18, false, false, true, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "C'est pas toi qui décide.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F19, false, false, true, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "C'est horrible ça me prend à la gorge.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F20, false, false, true, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "Mais ça va pas Baptiste.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F21, false, false, true, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "Mais t'es pas net nan.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F22, false, false, true, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "Mais moi je veux faire l'amour.wav") })
			&& _hotkey_manager.addHotkeyEvent({ VK_F23, false, false, true, std::bind(&VoiceChangerApp::_playFile, this, e_FileFormat::WAV, "T'es un malade Bernard.wav") })
			;


		return port_audio_initialized && hotkey_manager_initialized;
	}

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