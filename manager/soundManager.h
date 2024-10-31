#pragma once
#include <unordered_map>
#include <string>

enum class SOUND
{
	SHOT = 0,
	NOAMMO
};

class SoundManager final
{
private:
	static std::unordered_map<SOUND, std::string> m_ReservSoundPool;
	static std::unordered_map<SOUND, int> m_LoadSoundPool;

	static int LoadSound(const SOUND& sound, const std::string& fileName);

public:
	static void Init();
	static void ReservSound(const SOUND& texture, const std::string& fileName);
	static const int& GetSound(const SOUND& texture);
};