#define _AMD64_
#include <windows.h>
#include <iostream>
#include "HotKeyManager.hpp"

namespace Chelmi
{

	HotKeyManager::HotKeyManager() : _hotkeys_available({
		{VK_ADD, "Numpad +"},
		{VK_ATTN, "Attn"},
		{VK_F20, "F20"},
		{VK_F21, "F21"},
		{VK_F22, "F22"},
		{VK_F23, "F23"},
		{VK_F24, "F24"},
		})
	{
	}

	HotKeyManager::~HotKeyManager()
	{
	}

	void HotKeyManager::start()
	{
		MSG msg = { 0 };
		while (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			if (msg.message == WM_HOTKEY)
			{
				auto iterator = std::find_if(_hotkeys_registered.begin(), _hotkeys_registered.end(), [msg](const HotKeyEvent& event) { return msg.wParam == event.key_code;});
				if (iterator != _hotkeys_registered.end())
				{
					iterator->callback();
				}
			}
		}
	}

	void HotKeyManager::quit()
	{
		PostQuitMessage(0);
	}

	bool HotKeyManager::addHotkeyEvent(const HotKeyEvent& event)
	{
		// Should change to keyboard hook to be notified of release
		if (RegisterHotKey(
			NULL,
			event.key_code,
			MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT,
			event.key_code))
		{
			HotKeyEvent to_add = { event.key_code, event.callback };
			_hotkeys_registered.push_back(to_add);
			return true;
		}
		return false;
	}

	void HotKeyManager::removeHotkeyMonitored(const HotKeyEvent& event_to_remove)
	{
		auto iterator = std::find_if(_hotkeys_registered.begin(), _hotkeys_registered.end(), [event_to_remove](const HotKeyEvent& event) { return event_to_remove.key_code == event.key_code;});
		if (iterator != _hotkeys_registered.end())
		{
			_hotkeys_registered.erase(iterator);
		}
	}

	const std::vector<HotKey>& HotKeyManager::getAvailableHotkeys() const
	{
		return _hotkeys_available;
	}
}