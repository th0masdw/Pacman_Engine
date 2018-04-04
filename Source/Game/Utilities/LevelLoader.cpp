#include "MiniginPCH.h"
#include "LevelLoader.h"
#include <sstream>

LevelLoader::LevelLoader(const std::string& fileName)
	: m_Reader{}
{
	m_Reader.open(fileName, std::ios::in);

	if (!m_Reader) {
		std::stringstream ss;
		ss << "Could not open file " << fileName << " for reading";
		Debug::LogError(ss.str());
		return;
	} else {
		ProcessFile();
	}
}

void LevelLoader::ProcessFile()
{
	std::string line;
	while (std::getline(m_Reader, line)) {

		if (line.empty())
			continue;
		
		//Process block type
		if (line.find('[') != std::string::npos) {
			size_t rightBracket = line.find(']');
			int blockId = std::stoi(line.substr(1, rightBracket - 1));
			m_CurrentBlock = static_cast<BlockType>(blockId);
		}
		else {
			//get position
			size_t seperator = line.find(';');
			float x = std::stof(line.substr(0, seperator));
			float y = std::stof(line.substr(seperator + 1));

			switch (m_CurrentBlock) {
				case BlockType::PLAYER:
					m_PacmanPosition = { x, y };
					break;

				case BlockType::GHOST:
					m_GhostPositions.emplace_back(x, y);
					break;

				case BlockType::WALL:
					m_WallPositions.emplace_back(x, y);
					break;

				case BlockType::PELLET:
					m_PelletPositions.emplace_back(x, y);
					break;

				case BlockType::POWER:
					m_PowerPelletPositions.emplace_back(x, y);
					break;

				case BlockType::FRUIT:
					m_FruitPosition = { x, y };
					break;

				case BlockType::GHOSTHOUSE:
					m_GhostHousePosition = { x, y };
					break;
			}
		}
	}
}

glm::vec2 LevelLoader::GetPlayerPosition() const
{
	return m_PacmanPosition;
}

const std::vector<glm::vec2>& LevelLoader::GetGhostPositions() const
{
	return m_GhostPositions;
}

const std::vector<glm::vec2>& LevelLoader::GetWallPositions() const
{
	return m_WallPositions;
}

const std::vector<glm::vec2>& LevelLoader::GetPelletPositions() const
{
	return m_PelletPositions;
}

const std::vector<glm::vec2>& LevelLoader::GetPowerPelletPositions() const
{
	return m_PowerPelletPositions;
}

glm::vec2 LevelLoader::GetFruitPosition() const
{
	return m_FruitPosition;
}

glm::vec2 LevelLoader::GetGhostHousePosition() const
{
	return m_GhostHousePosition;
}

UINT LevelLoader::GetGhostAmount() const
{
	return static_cast<UINT>(m_GhostPositions.size());
}

UINT LevelLoader::GetWallAmount() const
{
	return static_cast<UINT>(m_WallPositions.size());
}

UINT LevelLoader::GetPelletAmount() const
{
	return static_cast<UINT>(m_PelletPositions.size());
}

UINT LevelLoader::GetPowerPelletAmount() const
{
	return static_cast<UINT>(m_PowerPelletPositions.size());
}