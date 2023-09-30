#include <iostream>
#include "HotKeyManager.hpp"

namespace Chelmi
{

	HotKeyManager::HotKeyManager() : _hotkeys_available({
		{VK_ADD, "Numpad +"},
		{VK_ATTN, "Attn"},
		{VK_F1, "F1"},
		{VK_F2, "F2"},
		{VK_F3, "F3"},
		{VK_F4, "F4"},
		{VK_F5, "F5"},
		{VK_F6, "F6"},
		{VK_F7, "F7"},
		{VK_F8, "F8"},
		{VK_F9, "F9"},
		{VK_F10, "F10"},
		{VK_F11, "F11"},
		{VK_F12, "F12"},
		{VK_F13, "F13"},
		{VK_F14, "F14"},
		{VK_F15, "F15"},
		{VK_F16, "F16"},
		{VK_F17, "F17"},
		{VK_F18, "F18"},
		{VK_F19, "F19"},
		{VK_F20, "F20"},
		{VK_F21, "F21"},
		{VK_F22, "F22"},
		{VK_F23, "F23"},
		{VK_F24, "F24"},
		{VK_SHIFT, "SHIFT"},
		{VK_CONTROL, "CONTROL"},
		{VK_MENU, "ALT"},
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
				auto iterator = std::find_if(_hotkeys_registered.begin(), _hotkeys_registered.end(), [msg](const HotKeyEvent& event) { return msg.wParam == event.register_unique_ID;});
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
			event.register_unique_ID,
			event.getModifierValue(),
			event.key_code))
		{
			HotKeyEvent to_add = event;
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