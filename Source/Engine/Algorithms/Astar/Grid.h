#pragma once

struct vec2;

class Grid
{
public:
	explicit Grid(int gridSize);
	~Grid() = default;

	void Draw() const;

	bool IsObstacle(const glm::vec2& pos) const;
	int GetSize() const;

private:
	std::vector<bool> m_ObstacleTiles;
	int m_GridSize;
	int m_TileWidth, m_TileHeight;

	void ToIndexPos(const glm::vec2& pos, int& x, int& y) const;

    /*void setElement(char&& asda, Vector2 position) {
        data[position.getX() + (position.getY() * size)] = asda;
    }*/
};