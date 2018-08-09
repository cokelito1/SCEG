#pragma once

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

#include "Logger.h"

namespace SCEG {

class Engine;

class ImageManager {
public:
	explicit ImageManager(Engine *engine);
	~ImageManager();

	const sf::Image& GetImage(const std::string& FileName);
private:
	ImageManager(const ImageManager&) = delete;
	ImageManager& operator=(const ImageManager&) = delete;
	
	Engine *engine;
	Logger *logger;

	std::map<std::string, sf::Image> Images;
};
}