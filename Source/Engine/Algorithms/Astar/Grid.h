#pragma once

struct vec2;

class Grid
{
public:
	explicit Grid(int width, int height);
	~Grid() = default;

	void PostInitialize();
	void Draw() const;

	bool IsObstacle(const glm::vec2& pos) const;
	void ToIndexPos(const glm::vec2& pos, int& x, int& y) const;

	int GetWidth() const;
	int GetHeight() const;
	float GetTileSize() const;

private:
	std::vector<bool> m_ObstacleTiles;
	int m_Width, m_Height;
	float m_TileSize;
};