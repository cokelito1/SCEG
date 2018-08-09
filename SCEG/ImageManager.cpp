#include "ImageManager.h"
#include "SCEG.h"

namespace SCEG {
	ImageManager::ImageManager(Engine *engine) {
		this->engine = engine;
		logger = this->engine->GetLogger();
		(*logger) << Logger::LogType::LOG_DEBUG << "Image Manager inciado\n";
	}

	ImageManager::~ImageManager() { 
		(*logger) << Logger::LogType::LOG_DEBUG << "Image Manager destruido\n";
	}

	const sf::Image& ImageManager::GetImage(const std::string& FileName) {
		for (std::map<std::string, sf::Image>::const_iterator it = Images.begin(); it != Images.end(); it++) {
			if (FileName == it->first) {
				(*logger) << Logger::LogType::LOG_DEBUG << "Usando imagen ya cargada\n";
				return it->second;
			}
		}

		sf::Image image;
		if (image.loadFromFile(FileName)) {
			Images[FileName] = image;
			(*logger) << Logger::LogType::LOG_DEBUG << "Imagen cargada de disco\n";
			return Images[FileName];
		}

		(*logger) << Logger::LogType::LOG_ERROR << "Error al cargar la imagen :(\n";
		Images[FileName] = image;
		return Images[FileName];
	}
}