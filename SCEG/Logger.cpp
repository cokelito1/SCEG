#include <iostream>

#include "Logger.h"

namespace SCEG {
	Logger::Logger(const char *version, const char *fname) {
		LogFile.open(fname);
		if (LogFile.is_open()) {
			LogFile << "SCEG version " << version << std::endl;
			LogFile << "[Info] SCEG logger inciado" << std::endl << std::endl;
#ifdef LOGGER_TO_STDOUT
			std::cout << "SCEG Version " << version << std::endl;
			std::cout << "[Info] SCEG logger iniciado" << std::endl << std::endl;
#endif
		} else {
			std::cout << "Logger fallo al inciar :(" << std::endl;
		}
	}

	Logger::~Logger() {
		if (LogFile.is_open()) {
			LogFile << std::endl << std::endl;
			LogFile << "Numero de errores: " << ErrorNum << std::endl;
			LogFile << "Numero de warnings: " << WarningNum << std::endl;
#ifdef LOGGER_TO_STDOUT
			std::cout << std::endl << std::endl;
			std::cout << "Numero de errores: " << ErrorNum << std::endl;
			std::cout << "Numero de warnings: " << WarningNum << std::endl;
#endif
			LogFile.close();
		}
	}

	Logger& operator<<(Logger& logger, Logger::LogType type) {
		switch (type) {
		case SCEG::Logger::LogType::LOG_DEBUG:
			logger.LogFile << "[DEBUG]: ";
#ifdef LOGGER_TO_STDOUT
			std::cout << "[DEBUG]: ";
#endif
			break;
		case SCEG::Logger::LogType::LOG_INFO:
			logger.LogFile << "[INFO]: ";
#ifdef LOGGER_TO_STDOUT
			std::cout << "[INFO]: ";
#endif
			break;
		case SCEG::Logger::LogType::LOG_ERROR:
			logger.LogFile << "[ERROR]: ";
#ifdef LOGGER_TO_STDOUT
			std::cout << "[ERROR]: ";
#endif
			logger.ErrorNum++;
			break;
		case SCEG::Logger::LogType::LOG_WARNING:
			logger.LogFile << "[WARNING]: ";
#ifdef LOGGER_TO_STDOUT
			std::cout << "[WARNING]: ";
#endif
			logger.WarningNum++;
			break;
		default:
			break;
		}

		return logger;
	}

	Logger& operator<<(Logger& logger, const char *text) {
		logger.LogFile << text;
#ifdef LOGGER_TO_STDOUT
		std::cout << text;
#endif
		return logger;
	}

	Logger& operator<<(Logger& logger, float num) {
		logger.LogFile << num;
#ifdef LOGGER_TO_STDOUT
		std::cout << num;
#endif
		return logger;
	}

	Logger& operator<<(Logger& logger, int num) {
		logger.LogFile << num;
#ifdef LOGGER_TO_STDOUT
		std::cout << num;
#endif
		return logger;
	}
}