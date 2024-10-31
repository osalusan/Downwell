#pragma once
#include <unordered_map>
#include <string>
enum class TEXTURE
{
	NONE = 0,		// èâä˙âªóp
	PLAYER,
	BULLET,
	WHITE,
	UI_HEART,
	UI_BULLETGAGE,
	PLAYER_IDLE,
	PLAYER_WALK,
	PLAYER_JUMP,
	PLAYER_DEAD,
	ENEMY_JELLYFISH,
	ENEMY_SNAIL,
	BLOCK_BREAK,
	BLOCK_UNBREAK,
	TITLE_DOWNWELL,
	PUSHKEY_SPACE,
	GAMEOVER,
	GAMEOVER_ARROW

};

class TextureManager final
{
private:
	static std::unordered_map<TEXTURE, std::string> m_ReservTexturePool;
	static std::unordered_map<TEXTURE, int> m_LoadTexturePool;

	static void LoadTexture(const TEXTURE& texture, const std::string& fileName);
public:
	static void Init();
	static void ReservTexture(const TEXTURE& texture,const std::string& fileName);
	static const int& GetTexture(const TEXTURE& texture);
};