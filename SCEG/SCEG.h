#pragma once

#include <map>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Logger.h"

namespace SCEG {

class Entity;
template<class T>
class ResourceManager;

class Engine {
public:
	Engine();
	~Engine();

	void RegisterEntity(const std::string& name, Entity *ent);
	void run();

	void UnregisterEntity(const std::string& name);
	void UnregisterEntity(Entity *ent);

	float GetDelta();

	Logger* GetLogger() const;
	ResourceManager<sf::Image>* GetImageManager() const;
	sf::RenderWindow* GetRenderWindow() const;
private:
	Logger *logger;
	ResourceManager<sf::Image> *imgMngr;
	ResourceManager<sf::SoundBuffer> *soundMngr;

	sf::RenderWindow *window;

	std::map<std::string, Entity *> entitys;

	sf::Clock delta;
	sf::Time deltaTime;
};
}