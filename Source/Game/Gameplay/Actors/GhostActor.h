#include "Engine/Scenegraph/GameObject.h"
struct vec2;
class GameTime;
class PacmanActor;
class CharacterController;

class GhostActor final : public GameObject
{
public:
	explicit GhostActor(PacmanActor* pPacman, float size = 50.0f, float speed = 50.0f, 
						const Color& color = { 255.0f, 255.0f, 255.0f, 255.0f }, bool isPlayerControlled = false);
	virtual ~GhostActor() = default;

	void Update(const GameTime& time);
	void Draw() const;

private:
	CharacterController* m_pController;
	bool m_IsPlayerControlled;
};