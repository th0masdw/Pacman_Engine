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

				case BlockType::WALL:
					m_WallPositions.emplace_back(x, y);
					break;
			}
		}
	}
}

glm::vec2 LevelLoader::GetPlayerPosition() const
{
	return m_PacmanPosition;
}

//More

const std::vector<glm::vec2>& LevelLoader::GetWallPositions() const
{
	return m_WallPositions;
}

//More

//More

size_t LevelLoader::GetWallAmount() const
{
	return m_WallPositions.size();
}