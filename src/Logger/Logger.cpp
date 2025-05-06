#include "Logger.h"
#include <ctime>
#include <stdlib.h>
#include <iostream>

std::vector<LogEntry> Logger::messages;

std::string GetTime() {
	time_t timestamp = time(NULL);
	struct tm datetime = *localtime(&timestamp);
	char output[50];
	strftime(output, 50, "%d/%b/%y %H:%M:%S", &datetime);

	return output;
}

void Logger::Log(const std::string& message) {
	LogEntry logEntry;
	logEntry.type = LOG_INFO;
	logEntry.message = "LOG: [" + GetTime() + "]: " + message;
	std::cout << "\x1B[32m" << logEntry.message << "\033[0m" << std::endl;
	messages.push_back(logEntry);
}

void Logger::Err(const std::string& message) {
	LogEntry logEntry;
	logEntry.type = LOG_ERROR;
	logEntry.message = "ERR: [" + GetTime() + "]: " + message;
	std::cout << "\x1b[91m" << logEntry.message << "\033[0m" << std::endl;
	messages.push_back(logEntry);
}
