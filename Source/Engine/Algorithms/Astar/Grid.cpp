#include "MiniginPCH.h"
#include "Grid.h"
#include "Engine/Helpers/Window.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Helpers/Structs.h"

Grid::Grid(int gridSize)
	: m_GridSize{ gridSize }
{
	int area = gridSize * gridSize;

	m_ObstacleTiles.resize(area);
    for (int i = 0; i < area; ++i) {
		m_ObstacleTiles[i] = false;
	}

	m_TileWidth = Window::GetWidth() / gridSize;
	m_TileHeight = Window::GetHeight() / gridSize;
}

void Grid::Draw() const
{
	if (Debug::IsDebugRenderingEnabled()) {
		glm::vec2 pos;
		float width, height;

		for (int row = 0; row < m_GridSize; ++row) {
			for (int col = 0; col < m_GridSize; ++col) {
				pos = { col * m_TileWidth, row * m_TileHeight };
				width = static_cast<float>(m_TileWidth);
				height = static_cast<float>(m_TileHeight);

				Renderer::GetInstance().RenderRect(pos, width, height, Color{ 192.0f, 192.0f, 192.0f, 255.0f }, false);
			}
		}
	}
}

bool Grid::IsObstacle(const glm::vec2& pos) const
{
	int x, y;
	ToIndexPos(pos, x, y);

	if (y < 0) y = 0;
    if (x < 0) x = 0;
    if (y >= m_GridSize) y = m_GridSize - 1;
    if (x >= m_GridSize) x = m_GridSize - 1;

    return m_ObstacleTiles[x + (y * m_GridSize)];
}

int Grid::GetSize() const
{
	return m_GridSize;
}

void Grid::ToIndexPos(const glm::vec2& pos, int& x, int& y) const
{
	x = static_cast<int>((pos.x - m_TileWidth) / m_TileWidth);
	y = static_cast<int>((pos.y - m_TileHeight) / m_TileHeight);
}