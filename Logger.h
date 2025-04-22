//
// Created by 24124 on 2025-04-22.
//

#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <iostream>
#include <mutex>
#include <fstream>

class Logger {
public:
    static Logger& getInstance();
    Logger& operator=(const Logger&) = delete;
    Logger(const Logger&) = delete;
    void log(const std::string& msg);
    ~Logger();
private:
    Logger();
    std::mutex _m;
    std::fstream _logFile;
};



#endif //LOGGER_H
