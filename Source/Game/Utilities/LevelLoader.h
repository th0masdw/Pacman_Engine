#pragma once

#include <fstream>

class LevelLoader
{
public:
	explicit LevelLoader(const std::string& fileName);
	~LevelLoader() = default;

	glm::vec2 GetPlayerPosition() const;
	//More
	const std::vector<glm::vec2>& GetWallPositions() const;
	const std::vector<glm::vec2>& GetPelletPositions() const;
	//More

	//More
	UINT GetWallAmount() const;
	UINT GetPelletAmount() const;

private:
	enum class BlockType
	{
		PLAYER	= 0,
		WALL	= 1,
		PELLET	= 2
	};

	std::ifstream m_Reader;
	BlockType m_CurrentBlock;

	glm::vec2 m_PacmanPosition;
	std::vector<glm::vec2> m_GhostPositions;
	std::vector<glm::vec2> m_WallPositions;
	std::vector<glm::vec2> m_PelletPositions;
	std::vector<glm::vec2> m_PowerPelletPositions;
	glm::vec2 m_FruitPosition;

	void ProcessFile();
};