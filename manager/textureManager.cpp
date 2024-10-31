#include "manager/textureManager.h"
#include "DxLib.h"
#include <iostream>
std::unordered_map<TEXTURE, std::string> TextureManager::m_ReservTexturePool = {};	    // �ǂݍ��ݗ\��ς݂̃e�N�X�`��
std::unordered_map<TEXTURE, int> TextureManager::m_LoadTexturePool = {};			    // �e�N�X�`���̕ۑ��ꏊ

void TextureManager::Init()
{
    // �e�N�X�`���̓ǂݍ���
    for (const std::pair<const TEXTURE, std::string>& ReservTexture : m_ReservTexturePool)
    {
        LoadTexture(ReservTexture.first,ReservTexture.second);
    }

}

void TextureManager::ReservTexture(const TEXTURE& texture, const std::string& fileName)
{
    m_ReservTexturePool.emplace(texture, fileName);
}

const int& TextureManager::GetTexture(const TEXTURE& texture)
{
    return m_LoadTexturePool[texture];
}

// -------------------------- private --------------------------

void TextureManager::LoadTexture(const TEXTURE& texture, const std::string& fileName)
{
    // �ۑ��ς݂̉摜������ꍇ
    if (m_LoadTexturePool.count(texture) > 0)
    {
        return; // �ǂݍ��܂Ȃ�
    }
    // �摜��ۑ�
    int Lg = LoadGraph(fileName.c_str());

    m_LoadTexturePool.emplace(texture, Lg);
}

 