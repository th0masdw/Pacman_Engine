#include "MiniginPCH.h"
#include "Grid.h"
#include "Engine/Helpers/Window.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Helpers/Structs.h"
#include "Engine/Managers/PhysicsManager.h"

Grid::Grid(int width, int height)
	: m_Width{ width },
	m_Height{ height }
{
	int area = width * height;

	m_ObstacleTiles.resize(area);
    for (int i = 0; i < area; ++i) {
		m_ObstacleTiles[i] = false;
	}

	m_TileSize = static_cast<float>(Window::GetWidth() / width);
}

void Grid::PostInitialize()
{
	std::vector<glm::vec2> positions;
	PhysicsManager::GetInstance().GetObstacles(positions);
	
	int x, y = 0;
	for (const glm::vec2& pos : positions) {
		ToIndexPos(pos, x, y);
		m_ObstacleTiles[(y * m_Width) + x] = true;
	}
}

void Grid::Draw() const
{
	if (Debug::IsDebugRenderingEnabled()) {
		glm::vec2 pos;

		for (int row = 0; row < m_Height; ++row) {
			for (int col = 0; col < m_Width; ++col) {
				pos = { col * m_TileSize, row * m_TileSize };

				Renderer::GetInstance().RenderRect(pos, m_TileSize, m_TileSize, Color{ 192.0f, 192.0f, 192.0f, 255.0f }, false);
			}
		}
	}
}

bool Grid::IsObstacle(const glm::vec2& pos) const
{
	int x = static_cast<int>(pos.x);
	int y = static_cast<int>(pos.y);

	if (y < 0) y = 0;
    if (x < 0) x = 0;
    if (y >= m_Height) y = m_Height - 1;
    if (x >= m_Width) x = m_Width - 1;

    return m_ObstacleTiles[(y * m_Width) + x];
}

int Grid::GetWidth() const
{
	return m_Width;
}

int Grid::GetHeight() const
{
	return m_Height;
}

float Grid::GetTileSize() const
{
	return m_TileSize;
}

void Grid::ToIndexPos(const glm::vec2& pos, int& x, int& y) const
{
	x = static_cast<int>(std::ceilf((pos.x - m_TileSize) / m_TileSize));
	y = static_cast<int>(std::ceilf((pos.y - m_TileSize) / m_TileSize));
}