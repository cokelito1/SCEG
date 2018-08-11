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
	enum class GameState {GAME_PLAYING, GAME_LOSE_SCREEN, GAME_SELECT};

	Engine();
	virtual ~Engine();

	void RegisterEntity(const std::string& name, Entity *ent);
	virtual void run();

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
	ResourceManager<sf::Font> *fontMngr;

	GameState state;
	bool bot = false;

	sf::RenderWindow *window;

	std::map<std::string, Entity *> entitys;

	sf::Clock delta;
	sf::Time deltaTime;
};
}