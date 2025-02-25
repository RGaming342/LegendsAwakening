#include "logger.h"

Logger systemLogger("core/logger/logs");

Logger::Logger(std::string log_file) {
	logFile.open(log_file, std::ios::out | std::ios::app);
}
Logger::~Logger() {
	if (logFile.is_open()) {
		logFile<<std::endl;
		logFile.close();
	}
}

void Logger::debug(std::string message){
	printMsg(LogLevel::DEBUG,message);
}

void Logger::info(std::string message){
	printMsg(LogLevel::INFO,message);
}

void Logger::warning(std::string message){
	printMsg(LogLevel::WARN,message);
}

void Logger::error(std::string message){
	printMsg(LogLevel::ERROR,message);
}

void Logger::fatal(std::string message,uint8_t exit_code){
	printMsg(LogLevel::FATAL,message);
	logFile<<std::endl;
	logFile.close();
	exit(exit_code);
}

void Logger::printMsg(LogLevel level, std::string& message) {
	std::lock_guard<std::mutex> guard(logMutex);
	
	std::string timestamp = getCurrentTime();
	std::string msg = timestamp + " " + levelToString(level) + message;
	
	std::cerr << msg << std::endl;
	if (logFile.is_open()) {
		logFile << msg << std::endl;
	}
}

std::string Logger::getCurrentTime() {
	std::time_t now = std::time(nullptr);
	char buf[100];
	std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
	return "[" + std::string(buf) + "]";
}

std::string Logger::levelToString(LogLevel level){
	const std::string levels[5] = {"[DEBUG]: ","[INFO]: ","[WARN]: ","[ERROR]: ","[FATAL]: "};
	return levels[static_cast<int8_t>(level)];
}
