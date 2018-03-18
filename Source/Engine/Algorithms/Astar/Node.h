#pragma once

struct vec2;

class Node
{
public:
	explicit Node(const glm::vec2& pos);
	~Node() = default;

	void CalculateCost(const glm::vec2& endPos);

	int GetGCost() const;
	int GetHCost() const;
	int GetFCost() const;

	Node* GetParent() const;
	void SetParent(Node* pNode);
	glm::vec2 GetPosition() const;

	bool operator==(const Node& other) const;
    bool operator!=(const Node& other) const;
    bool operator<(const Node& other) const;

private:
	glm::vec2 m_Position;
	int m_GCost, m_HCost, m_FCost;
	Node* m_pParent;
};