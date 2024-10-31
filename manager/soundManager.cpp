#include "soundManager.h"
#include "main.h"
std::unordered_map<SOUND, std::string> SoundManager::m_ReservSoundPool = {};	    // �ǂݍ��ݗ\��ς݂̃T�E���h
std::unordered_map<SOUND, int> SoundManager::m_LoadSoundPool = {};			        // �T�E���h�̕ۑ��ꏊ

constexpr int m_SOUND_VOLUME = 130;

void SoundManager::Init()
{
    // �e�N�X�`���̓ǂݍ���
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
    // �ۑ��ς݂̉摜������ꍇ
    if (m_LoadSoundPool.count(sound) > 0)
    {
        return m_LoadSoundPool[sound];
    }

    // �T�E���h��ۑ�
    int Sound = LoadSoundMem(fileName.c_str());

    // ���ʂ̒���
    ChangeVolumeSoundMem(m_SOUND_VOLUME, Sound);

    m_LoadSoundPool.emplace(sound, Sound);
    return Sound;
}