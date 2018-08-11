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
	void RegisterSprite();
	void draw(sf::RenderWindow *window);

	void SetName(const std::string& name);

	bool intersects(Entity *ent);

	std::string GetName() const;
	sf::Vector2f GetPosition() const;
};
}