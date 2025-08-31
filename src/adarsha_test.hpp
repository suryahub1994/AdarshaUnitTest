#pragma once
#include <format>
#include <iostream>
#include <map>
#include <source_location>

#include "adarsha_assertions.hpp"
#include "adarsha_logging.hpp"

#define TEST(name, value) Adarsha::TestRepository::registerTest(name, value)
#define RUN_ALL() Adarsha::TestRepository::runAll();

namespace Adarsha {
class TestRepository {
private:
  inline static std::map<std::string, std::function<void()>> repository{};

public:
  static void registerTest(const std::string &testName,
                           std::function<void()> func) {
    repository[testName] = func;
  }

  static int runAll(const std::set<std::string>& filter = {}) {
    int countOfSuccess = 0, countOfFailure = 0;

    for (auto& [name, fn] : repository) {
        // If a name filter is provided, skip tests not in it
        if (!filter.empty() && filter.count(name) == 0) continue;

        try {
            fn();
            ++countOfSuccess;
            printMessage("PASS: " + name, Adarsha::Status::SUCCESS);
        } catch (const Adarsha::AssertFail& e) {
            ++countOfFailure;
            printMessage("FAIL " + name + " : " + e.what(), Adarsha::Status::ERROR);
        } catch (...) {
            ++countOfFailure;
            printMessage("FAIL " + name + " : Unknown exception", Adarsha::Status::ERROR);
        }
    }

    printMessage("-------------------------------------------", Adarsha::Status::SUCCESS);
    printMessage(std::format("Test cases passed: {}", countOfSuccess), Adarsha::Status::SUCCESS);
    printMessage(std::format("Test cases failed: {}", countOfFailure), Adarsha::Status::ERROR);

    if (countOfFailure == 0) {
        printMessage("Test harness succeeded", Adarsha::Status::SUCCESS);
    } else {
        printMessage("Test harness failed", Adarsha::Status::ERROR);
    }
    return countOfFailure ? 1 : 0;
}
};
} // namespace Adarsha