#include "Engine/Scenegraph/GameObject.h"
struct vec2;
class GameTime;
class PacmanActor;
class ShapeComponent;
class AIComponent;
class CharacterController;

class GhostActor final : public GameObject
{
public:
	explicit GhostActor(PacmanActor* pPacman, int id = 0, float size = 50.0f, float speed = 50.0f, const Color& color = { 255.0f, 255.0f, 255.0f, 255.0f }, 
						const glm::vec2& spawnPos = { 387.5f, 362.5f }, bool isPlayerControlled = false);
	virtual ~GhostActor() = default;

	void Update(const GameTime& time);
	void Draw() const;

	int GetID() const;
	void Respawn();
	bool IsScared() const;
	void SetColor(const Color& color);

private:
	int m_ID;
	Color m_Color;
	bool m_IsPlayerControlled;
	ShapeComponent* m_pShape;
	AIComponent* m_pAI;
	CharacterController* m_pController;
	glm::vec2 m_Direction;
	float m_Speed;
	PacmanActor* m_pPlayer;

	glm::vec2 m_SpawnPosition;
	bool m_IsScared;

	void SetupBehaviour(PacmanActor* pActor, float speed);
	void GetScared(bool value);
};