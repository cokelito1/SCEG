#pragma once

#include <string>
#include <fstream>

namespace SCEG {
class Logger {
public:
	enum class LogType {LOG_DEBUG, LOG_INFO, LOG_ERROR, LOG_WARNING};

	explicit Logger(const char *Version, const char *fname = "sceg.log");
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	~Logger();

	friend Logger& operator<<(Logger& logger, std::string text);
	friend Logger& operator<<(Logger& logger, LogType type);
	friend Logger& operator<<(Logger& logger, const char *text);
	friend Logger& operator<<(Logger& logger, float num);
	friend Logger& operator<<(Logger& logger, int num);
private:
	std::ofstream LogFile;

	unsigned int WarningNum = 0;
	unsigned int ErrorNum = 0;
};
}