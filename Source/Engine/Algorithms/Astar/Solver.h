#pragma once

#include "Grid.h"
#include "Node.h"
#include <list>
struct vec2;

class Solver
{
public:
	explicit Solver(int gridWidth, int gridHeight, bool useDiagonals = false);
	~Solver() = default;

	Grid GetGridCopy() const;
	Grid& GetGridRef();
	void GetPath(const glm::vec2& start, const glm::vec2& end, std::list<Node>& result);

private:
	Grid m_Grid;
	std::vector<glm::vec2> m_Directions;

	glm::vec2 GetNodePosition(const glm::vec2& absolutePos) const;
};