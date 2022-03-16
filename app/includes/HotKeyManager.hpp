#pragma once

#define _AMD64_

#include <functional>
#include <vector>
#include <windows.h>

namespace Chelmi
{
	struct HotKey
	{
		int key_code;
		std::string human_representation;
	};
	
	struct HotKeyEvent
	{
		HotKeyEvent(int key_code, bool ctrl_on, bool shift_on, bool alt_on, const std::function<void()>& callback) : key_code(key_code), ctrl_on(ctrl_on), shift_on(shift_on), alt_on(alt_on), callback(callback)
		{
			static unsigned int unique_ID = 0;
			register_unique_ID = unique_ID++;
		}
		HotKeyEvent(int key_code, bool ctrl_on, bool shift_on, bool alt_on, const std::function<void()>& callback, unsigned int register_unique_ID) : key_code(key_code), ctrl_on(ctrl_on), shift_on(shift_on), alt_on(alt_on), callback(callback), register_unique_ID(register_unique_ID) {}
		HotKeyEvent(const HotKeyEvent& to_copy) : HotKeyEvent(to_copy.key_code, to_copy.ctrl_on, to_copy.shift_on, to_copy.alt_on, to_copy.callback, to_copy.register_unique_ID) {}
		HotKeyEvent operator=(const HotKeyEvent &to_copy)
		{
			return HotKeyEvent(to_copy);
		}
		unsigned int getModifierValue() const
		{
			return (ctrl_on ? MOD_CONTROL : 0) | (shift_on ? MOD_SHIFT : 0) | (alt_on ? MOD_ALT : 0) | (norepeat_on ? MOD_NOREPEAT : 0);
		}

		int key_code;
		bool ctrl_on;
		bool shift_on;
		bool alt_on;
		// Unused for now
		bool norepeat_on = true;
		std::function<void()> callback;
		unsigned int register_unique_ID;
	};

	class HotKeyManager
	{
	public:
		HotKeyManager();
		~HotKeyManager();
		void start();
		void quit();
		bool addHotkeyEvent(const HotKeyEvent &event);
		void removeHotkeyMonitored(const HotKeyEvent& event);
		const std::vector<HotKey>& getAvailableHotkeys() const;
	private:
		std::vector<HotKey> _hotkeys_available;
		std::vector<HotKeyEvent> _hotkeys_registered;
	};
}