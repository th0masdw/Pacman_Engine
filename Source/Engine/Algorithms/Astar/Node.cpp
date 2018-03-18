#include "MiniginPCH.h"
#include "Node.h"

Node::Node(const glm::vec2& pos)
	: m_Position{ pos },
	m_GCost{ 0 },
	m_HCost{ 0 },
	m_FCost{ 0 },
	m_pParent{ nullptr }
{
}

void Node::CalculateCost(const glm::vec2& endPos)
{
	m_HCost = static_cast<int>((std::abs(m_Position.x - endPos.x) + std::abs(m_Position.y - endPos.y)));
    m_GCost = m_pParent ? m_pParent->m_GCost + 1 : 1;
    m_FCost = m_HCost + m_GCost;
}

int Node::GetGCost() const
{
	return m_GCost;
}

int Node::GetHCost() const
{
	return m_HCost;
}

int Node::GetFCost() const
{
	return m_FCost;
}

Node* Node::GetParent() const
{
	return m_pParent;
}

void Node::SetParent(Node* pNode)
{
	m_pParent = pNode;
}

glm::vec2 Node::GetPosition() const
{
	return m_Position;
}

//Operators
bool Node::operator==(const Node& other) const
{
	return (m_Position.x == other.m_Position.x && m_Position.y == other.m_Position.y); 
}

bool Node::operator!=(const Node& other) const
{
	return !(*this == other);
}

bool Node::operator<(const Node& other) const
{
	return(m_FCost < other.m_FCost);
}