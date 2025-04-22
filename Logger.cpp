//
// Created by 24124 on 2025-04-22.
//

#include "Logger.h"

Logger & Logger::getInstance() {
    static Logger logger;
    return logger;
}

void Logger::log(const std::string &msg) {
    std::lock_guard<std::mutex> lock(_m);
    if (_logFile.is_open()) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        char buffer[100];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now_time));
        _logFile << std::string(buffer) << ": " << msg << std::endl;
    }
}

Logger::~Logger() {
    if (_logFile.is_open()) {
        _logFile.close();
    }
}

Logger::Logger() {
    _logFile.open("log.txt", std::ios::app);
    if (!_logFile.is_open()) {
        throw std::runtime_error("Logger could not open log file");
    }
}
