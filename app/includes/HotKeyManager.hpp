#pragma once

#include <functional>
#include <vector>

namespace Chelmi
{
	struct HotKey
	{
		int key_code;
		std::string human_representation;
	};
	
	struct HotKeyEvent
	{
		HotKeyEvent(int key_code, const std::function<void()>& callback) : key_code(key_code), callback(callback) {}
		HotKeyEvent(const HotKeyEvent& to_copy) : HotKeyEvent(to_copy.key_code, to_copy.callback)  {}
		HotKeyEvent operator=(const HotKeyEvent &to_copy)
		{
			return HotKeyEvent(to_copy);
		}
		int key_code;
		std::function<void()> callback;
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