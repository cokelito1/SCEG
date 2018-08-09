#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "SCEG.h"
#include "ImageManager.h"
#include "Logger.h"

namespace SCEG {

class Engine;

class Entity {
public:
	enum class MovementTo {MOV_NORTE, MOV_SUR, MOV_ESTE, MOV_OESTE, MOV_NORESTE, MOV_NOROESTE, MOV_SURESTE, MOV_SUROESTE};

	Entity(Engine *engine) {
		this->engine = engine;
		imgMngr = this->engine->GetImageManager();
		logger = this->engine->GetLogger();
		(*logger) << Logger::LogType::LOG_DEBUG << "Entity created\n";
	}

	virtual ~Entity() {
		*logger << Logger::LogType::LOG_DEBUG << "Eliminando entity: " << EntityName.c_str() << "\n";
	}

	virtual void Move(MovementTo direction) = 0;
	virtual void SetPosition(sf::Vector2f Pos) = 0;
	virtual void RegisterSprite() = 0;
	virtual void draw(sf::RenderWindow *window) = 0;
	virtual bool intersects(Entity *ent) = 0;

	virtual void SetVelocity(float velocity) { this->velocity = velocity; }
	virtual float GetVelocity() { return velocity; }

	virtual std::string GetName() const = 0;

	virtual sf::Vector2f GetPosition() const = 0;
	virtual sf::Sprite& GetSprite() { return sprite; };
protected:
	sf::Sprite sprite;
	sf::Texture texture;

	std::string EntityName;

	float velocity;

	Engine *engine;
	Logger *logger;
	ImageManager *imgMngr;
};
}