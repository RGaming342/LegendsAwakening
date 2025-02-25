#pragma once

#include <iostream>
#include <mutex>
#include <fstream>
#include <cstdint>

enum class LogLevel {
	DEBUG=0,
	INFO=1,
	WARN=2,
	ERROR=3,
	FATAL=4
};

class Logger{
	public:
		Logger(std::string log_file);
		~Logger();
		
		void debug(std::string);
		void info(std::string);
		void warning(std::string);
		void error(std::string);
		void fatal(std::string,uint8_t);
		
	private:
		std::mutex logMutex;
		std::ofstream logFile;
		
		void printMsg(LogLevel,std::string&);
		
		std::string getCurrentTime();
		std::string levelToString(LogLevel level);
};


extern Logger systemLogger;


#define Debug(message) systemLogger.debug(message)
#define Info(message) systemLogger.info(message)
#define Warn(message) systemLogger.warning(message)
#define Error(message) systemLogger.error(message)
#define Fatal(message,exit_code) systemLogger.fatal(message,exit_code)
