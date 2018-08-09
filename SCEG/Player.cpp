#include "Player.h"

namespace SCEG {
	Player::Player(Engine *engine) : Entity(engine){
		velocity = 40.0f;
	}

	Player::~Player() { 
		*logger << Logger::LogType::LOG_DEBUG << "Eliminando player: " << EntityName.c_str() << "\n";
	}

	void Player::SetName(const std::string& name) {
		EntityName = name;
	}

	void Player::SetPosition(sf::Vector2f position) {
		sprite.setPosition(position);
	}

	void Player::Move(Entity::MovementTo direction) {
		switch (direction) {
		case SCEG::Entity::MovementTo::MOV_NORTE:
			if (sprite.getPosition().y - 1.0f > 0.0f) {
				sprite.move(0, -(velocity * engine->GetDelta()));
			}
			break;
		case SCEG::Entity::MovementTo::MOV_SUR:
			if ((sprite.getPosition().y + texture.getSize().y) + 1.0f < 600.0f) { 
				sprite.move(0, velocity * engine->GetDelta());
			}
			break;
		case SCEG::Entity::MovementTo::MOV_ESTE:
			sprite.move(velocity * engine->GetDelta(), 0);
			break;
		case SCEG::Entity::MovementTo::MOV_OESTE:
			sprite.move(-(velocity * engine->GetDelta()), 0);
			break;
		case SCEG::Entity::MovementTo::MOV_NORESTE:
			sprite.move(velocity * engine->GetDelta(), -(velocity * engine->GetDelta()));
			break;
		case SCEG::Entity::MovementTo::MOV_NOROESTE:
			sprite.move(-(velocity * engine->GetDelta()), -(velocity * engine->GetDelta()));
			break;
		case SCEG::Entity::MovementTo::MOV_SURESTE:
			sprite.move(velocity * engine->GetDelta(), velocity * engine->GetDelta());
			break;
		case SCEG::Entity::MovementTo::MOV_SUROESTE:
			sprite.move(-(velocity * engine->GetDelta()), velocity * engine->GetDelta());
			break;
		default:
			break;
		}
	}

	void Player::SetImage(sf::Image img) {
		texture.loadFromImage(img);
		texture.setSmooth(true);
		sprite.setTexture(texture);
	}

	void Player::RegisterSprite() {
		engine->RegisterEntity(EntityName, this);
	}

	void Player::draw(sf::RenderWindow *window) {
		window->draw(sprite);
	}

	bool Player::intersects(Entity *ent) {
		if (sprite.getGlobalBounds().intersects(ent->GetSprite().getGlobalBounds())) {
			return true;
		}
		return false;
	}

	std::string Player::GetName() const {
		return EntityName;
	}

	sf::Vector2f Player::GetPosition() const {
		return sprite.getPosition();
	}
}