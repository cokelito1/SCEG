#include <random>

#include "SCEG.h"
#include "Player.h"
#include "ResourceManager.h"

#include <SFML/Audio.hpp>

#include <string.h>

namespace SCEG {
	Engine::Engine() {
		logger = new Logger("0.0.1");

		imgMngr = new ResourceManager<sf::Image>(this);
		soundMngr = new ResourceManager<sf::SoundBuffer>(this);
		fontMngr = new ResourceManager<sf::Font>(this);

		imgMngr->AddResourceDirectory("media/images/");
		soundMngr->AddResourceDirectory("media/sounds/");
		fontMngr->AddResourceDirectory("media/fonts/");

		window = new sf::RenderWindow(sf::VideoMode(800, 600), "hello");
		window->setVerticalSyncEnabled(true);
		window->setIcon(imgMngr->GetResource("ball.png").getSize().x, imgMngr->GetResource("ball.png").getSize().y, imgMngr->GetResource("ball.png").getPixelsPtr());
		
		state = GameState::GAME_SELECT;

		(*logger) << Logger::LogType::LOG_INFO << "Engine Iniciado\n";
	}

	Engine::~Engine() {
		delete imgMngr;
		delete soundMngr;
		delete fontMngr;

		for (auto i : entitys) {
			(*logger) << Logger::LogType::LOG_DEBUG <<"Entidad de registrada: " << i.second->GetName().c_str() << "\n";
			delete i.second;
		}

		delete window;

		(*logger) << Logger::LogType::LOG_INFO << "Engine terminado\n";
		delete logger;
	}

	void Engine::RegisterEntity(const std::string& EntityName, Entity *ent) {
		entitys.insert(std::pair<std::string, Entity *>(EntityName, ent));
		(*logger) << Logger::LogType::LOG_DEBUG << "Entidad registrada, nombre: " << ent->GetName().c_str() << "\n";
	}

	void Engine::UnregisterEntity(const std::string& EntityName) {
		for (std::map<std::string, Entity *>::const_iterator it = entitys.begin(); it != entitys.end(); it++) {
			if (it->first == EntityName) {
				delete it->second;
				entitys.erase(it);
				(*logger) << Logger::LogType::LOG_DEBUG << "Entidad eliminada, nombre: " << EntityName.c_str() << "\n";
				break;
			}
		}
	}

	void Engine::UnregisterEntity(Entity *ent) {
		for (std::map<std::string, Entity *>::const_iterator it = entitys.begin(); it != entitys.end(); it++) {
			if (it->second == ent) {
				entitys.erase(it);
				(*logger) << Logger::LogType::LOG_DEBUG << "Entidad eliminada, nombre: " << ent->GetName().c_str() << "\n";
				delete ent;
				break;
			}
		}
	}
	
	float Engine::GetDelta() {
		return deltaTime.asSeconds();
	}

	Logger* Engine::GetLogger() const {
		return logger;
	}

	ResourceManager<sf::Image>* Engine::GetImageManager() const {
		return imgMngr;
	}

	sf::RenderWindow* Engine::GetRenderWindow() const {
		return window;
	}
}
