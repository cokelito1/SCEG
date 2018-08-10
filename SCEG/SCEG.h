#pragma once

#include <map>

#include "ImageManager.h"
#include "Logger.h"

namespace SCEG {

	class Entity;

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
	ImageManager* GetImageManager() const;
	sf::RenderWindow* GetRenderWindow() const;
private:
	Logger *logger;
	ImageManager *imgMngr;

	sf::RenderWindow *window;

	std::map<std::string, Entity *> entitys;

	sf::Clock delta;
	sf::Time deltaTime;
};
}