#include "Engine/Scenegraph/GameObject.h"
struct vec2;
class GameTime;

class GhostActor final : public GameObject
{
public:
	explicit GhostActor(float size = 50.0f, float speed = 50.0f, const Color& color = { 255.0f, 255.0f, 255.0f, 255.0f });
	virtual ~GhostActor() = default;

	void Update(const GameTime& time);
	void Draw() const;

private:
	float m_Speed;
	
	void Move(const glm::vec2& displacement);
};