#pragma once

#include <map>
#include <string>

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

		const T& GetResource(const std::string& FileName) {
			for (typename std::map<std::string, T>::const_iterator it = Resources.begin(); it != Resources.end(); it++) {
				if (it->first == FileName) {
					(*logger) << Logger::LogType::LOG_DEBUG << "Cargando recurso de memoria: " << FileName << "\n";
					return it->second;
				}
			}

			T resource;
			if (resource.loadFromFile(FileName)) {
				Resources[FileName] = resource;
				(*logger) << Logger::LogType::LOG_DEBUG << "Cargando desde disco: " << FileName << "\n";
				return Resources[FileName];
			}

			(*logger) << Logger::LogType::LOG_ERROR << "Error al cargar archivo: " << FileName << "\n";
			Resources[FileName] = resource;
			return Resources[FileName];
		}

	private:
		Engine *engine;
		Logger *logger;

		std::map<std::string, T> Resources;
	};
}
