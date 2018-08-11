#pragma once

#include "Entity.h"
#include "SCEG.h"

namespace SCEG {
class Player : public Entity{
public:
	explicit Player(Engine *engine);
	~Player();

	void Move(Entity::MovementTo direction);

	void SetPosition(sf::Vector2f pos);
	void SetImage(sf::Image img);
	void SetName(const std::string& name);

	std::string GetName() const;
	sf::Vector2f GetPosition() const;

	void RegisterSprite();

	void draw(sf::RenderWindow *window);
	bool intersects(Entity *ent);
};
}