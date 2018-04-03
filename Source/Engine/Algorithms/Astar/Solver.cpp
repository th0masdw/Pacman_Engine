#include "MiniginPCH.h"
#include "Solver.h"
#include <algorithm>

Solver::Solver(int gridWidth, int gridHeight, bool useDiagonals)
	: m_Grid(gridWidth, gridHeight)
{
	m_Directions.emplace_back(0, 1);
	m_Directions.emplace_back(0, -1);
	m_Directions.emplace_back(1, 0);
	m_Directions.emplace_back(-1, 0);

	if (useDiagonals) {
		m_Directions.emplace_back(1, 1);
		m_Directions.emplace_back(1, -1);
		m_Directions.emplace_back(-1, 1);
		m_Directions.emplace_back(-1, -1);
	}
}

Grid Solver::GetGridCopy() const
{
	return m_Grid;
}

Grid& Solver::GetGridRef()
{
	return m_Grid;
}

void Solver::GetPath(const glm::vec2& start, const glm::vec2& end, std::list<Node>& result)
{
	Node startNode(GetNodePosition(start));
    Node goalNode(GetNodePosition(end));

    if (m_Grid.IsObstacle(startNode.GetPosition()) || m_Grid.IsObstacle(goalNode.GetPosition())) {
        //Debug::LogError("Astar Solver: Could not get path - start or endnode is obstructed");
        return;
    }

    std::list<Node> openList;
    std::list<Node> closedList;

    startNode.CalculateCost(goalNode.GetPosition());
    openList.push_back(startNode);

    while (!openList.empty()) {
        Node current = *std::min_element(openList.begin(), openList.end());

        current.CalculateCost(goalNode.GetPosition());

        closedList.push_back(current);     
        if (current == goalNode) break;
		openList.remove(current);

        for (const glm::vec2& direction : m_Directions) {
            Node next(direction + current.GetPosition());
			
            if (m_Grid.IsObstacle(next.GetPosition()) || next.GetPosition().x > m_Grid.GetWidth() - 1 || 
                next.GetPosition().y > m_Grid.GetHeight() - 1 || next.GetPosition().x < 0 || 
                next.GetPosition().y < 0 ||
                std::find(closedList.begin(), closedList.end(), next) != closedList.end()) 
			{
                continue;
            }

            next.CalculateCost(goalNode.GetPosition());

            auto openIt = std::find(openList.begin(), openList.end(), next);
            if (openIt == openList.end()) {
				next.SetParent(&closedList.back());
                next.CalculateCost(goalNode.GetPosition());

                openList.push_back(next);
            }
            else {
				if (next.GetGCost() < openIt->GetGCost())
					next.SetParent(&closedList.back());
			}
        }
    }

    if (openList.empty()) {
        Debug::LogError("Astar Solver: No path found");
        return;
    }

    auto closedIt = std::find(closedList.begin(), closedList.end(), goalNode);
    if (closedIt != closedList.end()) {
        while (*closedIt != startNode) {
			result.push_front(*closedIt);
            *closedIt = *closedIt->GetParent();
        }
    }
}

glm::vec2 Solver::GetNodePosition(const glm::vec2& absolutePos) const
{
	int x, y = 0;

	m_Grid.ToIndexPos(absolutePos, x, y);
	return glm::vec2(x, y);
}