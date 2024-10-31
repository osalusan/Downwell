#include "gameObject.h"
#include "manager/textureManager.h"

void GameObject::Draw(const XMFLOAT2& cameraPos)
{
	const XMFLOAT2& HalfScale = { m_Scale.x / 2,m_Scale.y / 2 };
	DrawExtendGraph(static_cast<int>(m_Position.x - HalfScale.x), static_cast<int>(m_Position.y - HalfScale.y) + static_cast<int>(cameraPos.y),
					static_cast<int>(m_Position.x + HalfScale.x), static_cast<int>(m_Position.y + HalfScale.y) + static_cast<int>(cameraPos.y), TextureManager::GetTexture(m_Texture), true);
}

void GameObject::LoadTexture(const TEXTURE& texture, const std::string& fileName)
{
	m_Texture = texture;
	TextureManager::ReservTexture(texture, fileName);
}

