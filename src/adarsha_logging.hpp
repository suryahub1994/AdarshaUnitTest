#pragma once
#include <iostream>
#include <string>

namespace Adarsha {

    enum class Status {
        SUCCESS,
        ERROR
    };

    inline const char* green() { return "\x1b[32m"; }
    inline const char* red()   { return "\x1b[31m"; }
    inline const char* reset() { return "\x1b[0m"; }

    inline void printMessage(const std::string &message, Status status) {
        switch (status) {
        case Status::SUCCESS:
            std::cout << green() << message << reset() << std::endl;
            break;
        case Status::ERROR:
            std::cout << red() << message << reset() << std::endl;
            break;
        }
    }
} 
