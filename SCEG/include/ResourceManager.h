#pragma once

#include <map>
#include <vector>
#include <string>
#include <sstream>

#include "SCEG.h"
#include "Logger.h"

namespace SCEG {
	template<class T>
	class ResourceManager {
	public:
		explicit ResourceManager(Engine *engine) {
			this->engine = engine;
			logger = engine->GetLogger();
		}
		~ResourceManager() { }

		void AddResourceDirectory(const std::string& DirName) {
			for(std::vector<std::string>::const_iterator it = ResourcesDirectories.begin(); it != ResourcesDirectories.end(); it++) {
				if((*it) == DirName) {
					return;
				}
			}

			ResourcesDirectories.push_back(DirName);
		}

		const T& GetResource(const std::string& FileName) {
			for (typename std::map<std::string, T>::const_iterator it = Resources.begin(); it != Resources.end(); it++) {
				if (it->first == FileName) {
					(*logger) << Logger::LogType::LOG_DEBUG << "Cargando recurso de memoria: " << FileName << "\n";
					return it->second;
				}
			}

			T resource;
			std::streambuf *previous = sf::err().rdbuf(NULL);
			if (resource.loadFromFile(FileName)) {
				Resources[FileName] = resource;
				(*logger) << Logger::LogType::LOG_DEBUG << "Cargando desde disco: " << FileName << "\n";
				sf::err().rdbuf(previous);
				return Resources[FileName];
			}

			for(std::vector<std::string>::const_iterator it = ResourcesDirectories.begin(); it != ResourcesDirectories.end(); it++) {
				if(resource.loadFromFile((*it) + FileName)) {
					Resources[FileName] = resource;
					(*logger) << Logger::LogType::LOG_DEBUG << "Cargando desde disco: " << FileName << "\n";
					sf::err().rdbuf(previous);
					return Resources[FileName];
				}
			}

			(*logger) << Logger::LogType::LOG_ERROR << "Error al cargar archivo: " << FileName << "\n";
			Resources[FileName] = resource;
			sf::err().rdbuf(previous);
			return Resources[FileName];
		}

	private:
		Engine *engine;
		Logger *logger;

		std::map<std::string, T> Resources;
		std::vector<std::string> ResourcesDirectories;
	};
}
