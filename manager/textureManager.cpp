#include "manager/textureManager.h"
#include "DxLib.h"
#include <iostream>
std::unordered_map<TEXTURE, std::string> TextureManager::m_ReservTexturePool = {};	    // 読み込み予約済みのテクスチャ
std::unordered_map<TEXTURE, int> TextureManager::m_LoadTexturePool = {};			    // テクスチャの保存場所

void TextureManager::Init()
{
    // テクスチャの読み込み
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
    // 保存済みの画像がある場合
    if (m_LoadTexturePool.count(texture) > 0)
    {
        return; // 読み込まない
    }
    // 画像を保存
    int Lg = LoadGraph(fileName.c_str());

    m_LoadTexturePool.emplace(texture, Lg);
}

 