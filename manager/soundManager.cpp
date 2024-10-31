#include "soundManager.h"
#include "main.h"
std::unordered_map<SOUND, std::string> SoundManager::m_ReservSoundPool = {};	    // 読み込み予約済みのサウンド
std::unordered_map<SOUND, int> SoundManager::m_LoadSoundPool = {};			        // サウンドの保存場所

constexpr int m_SOUND_VOLUME = 130;

void SoundManager::Init()
{
    // テクスチャの読み込み
    for (const std::pair<const SOUND, std::string>& ReservSound : m_ReservSoundPool)
    {
        LoadSound(ReservSound.first, ReservSound.second);
    }
}

void SoundManager::ReservSound(const SOUND& texture, const std::string& fileName)
{
    m_ReservSoundPool.emplace(texture, fileName);
}

const int& SoundManager::GetSound(const SOUND& texture)
{
    return m_LoadSoundPool[texture];
}

// -------------------------- private --------------------------
int SoundManager::LoadSound(const SOUND& sound, const std::string& fileName)
{
    // 保存済みの画像がある場合
    if (m_LoadSoundPool.count(sound) > 0)
    {
        return m_LoadSoundPool[sound];
    }

    // サウンドを保存
    int Sound = LoadSoundMem(fileName.c_str());

    // 音量の調整
    ChangeVolumeSoundMem(m_SOUND_VOLUME, Sound);

    m_LoadSoundPool.emplace(sound, Sound);
    return Sound;
}