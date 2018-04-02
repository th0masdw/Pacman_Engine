#include "Engine/Scenegraph/GameObject.h"
struct vec2;
class GameTime;
class PacmanActor;
class CharacterController;

class GhostActor final : public GameObject
{
public:
	explicit GhostActor(PacmanActor* pPacman, float size = 50.0f, float speed = 50.0f, const Color& color = { 255.0f, 255.0f, 255.0f, 255.0f }, 
						const glm::vec2& ghostHouse = { 387.5f, 362.5f }, bool isPlayerControlled = false);		//TODO CHANGE GHOSTHOUSE
	virtual ~GhostActor() = default;

	void Update(const GameTime& time);
	void Draw() const;

	void Respawn();
	bool IsScared() const;

private:
	bool m_IsPlayerControlled;
	CharacterController* m_pController;
	glm::vec2 m_Direction;

	glm::vec2 m_GhostHouse;
	bool m_IsScared;

	void SetupBehaviour(PacmanActor* pActor, float speed);
};