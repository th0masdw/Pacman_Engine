#pragma once

#include <fstream>

class LevelLoader
{
public:
	explicit LevelLoader(const std::string& fileName);
	~LevelLoader() = default;

	glm::vec2 GetPlayerPosition() const;
	const std::vector<glm::vec2>& GetGhostPositions() const;
	const std::vector<glm::vec2>& GetWallPositions() const;
	const std::vector<glm::vec2>& GetPelletPositions() const;
	const std::vector<glm::vec2>& GetPowerPelletPositions() const;
	//More

	UINT GetGhostAmount() const;
	UINT GetWallAmount() const;
	UINT GetPelletAmount() const;
	UINT GetPowerPelletAmount() const;

private:
	enum class BlockType
	{
		PLAYER	= 0,
		GHOST	= 1,
		WALL	= 2,
		PELLET	= 3,
		POWER	= 4,
		FRUIT	= 5
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