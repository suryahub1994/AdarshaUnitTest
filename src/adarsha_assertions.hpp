#pragma once
#include <stdexcept>
#include <string>
#include <set>

#include "adarsha_assertions.hpp"

namespace Adarsha
{
    static const double DEFAULT_EPS = 1e-9;
    struct AssertFail : std::runtime_error 
    {
        using std::runtime_error::runtime_error;  
    };
    void assert(bool condition, const std::string &message,
            std::source_location loc = std::source_location::current()) {
    if (!condition) {
        throw AssertFail(message + " at:  File " + loc.file_name() + ":" + std::to_string(loc.line()));
    }
    }

template <typename T>
void assertEqual(const T &a, const T &b, const std::string &message,
                 std::source_location loc = std::source_location::current()) {
    if (!(a == b)) {
        throw AssertFail(message + " at: File " + loc.file_name() + ":" + std::to_string(loc.line()));
    }
}

template <typename T>
void assertNotEqual(const T &a, const T &b, const std::string &message,
                    std::source_location loc = std::source_location::current()) {
    if (!(a != b)) {
        throw AssertFail(message + " at: File " + loc.file_name() + ":" + std::to_string(loc.line()));
    }
}

template <typename T>
void assertLess(const T &a, const T &b, const std::string &message,
                std::source_location loc = std::source_location::current()) {
    if (!(a < b)) {
        throw AssertFail(message + " at: File " + loc.file_name() + ":" + std::to_string(loc.line()));
    }
}

template <typename T>
void assertGreater(const T &a, const T &b, const std::string &message,
                   std::source_location loc = std::source_location::current()) {
    if (!(a > b)) {
        throw AssertFail(message + " at: File " + loc.file_name() + ":" + std::to_string(loc.line()));
    }
}

template <typename T>
void assertNear(const T &a, const T &b, double eps = DEFAULT_EPS,
                const std::string &message = "",
                std::source_location loc = std::source_location::current()) {
    if (!(std::abs(a - b) < eps)) {
        throw AssertFail(message + " at: File " + loc.file_name() + ":" + std::to_string(loc.line()));
    }
}

template <typename P>
void assertNull(P p, const std::string &message = "",
                std::source_location loc = std::source_location::current()) {
    if (p != nullptr) {
        throw AssertFail(message + " at: File " + loc.file_name() + ":" + std::to_string(loc.line()));
    }
}
}