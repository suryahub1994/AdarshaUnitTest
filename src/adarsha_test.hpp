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

  static void runAll() {
    int countOfSucess = 0, countOfFailure = 0;
    for (auto& [name, fn] : repository) {
      try {
        fn();
        countOfSucess++;
        std::string message = "PASS: " + name;
        printMessage(message, Adarsha::Status::SUCCESS);
      } catch (const Adarsha::AssertFail& e) {
        countOfFailure++;
        std::string failMessage =  "FAIL " +  name + " : " +  e.what();
        printMessage(failMessage, Adarsha::Status::ERROR);

      } catch (...) {
        countOfFailure++;
        std::string failMessage =  "FAIL " +  name + " : " + "Unknown exception";
        printMessage(failMessage, Adarsha::Status::ERROR); 
      }
    }
    printMessage("-------------------------------------------", Adarsha::Status::SUCCESS);
    printMessage(std::format("Test cases passed: {}", countOfSucess), Adarsha::Status::SUCCESS);
    printMessage(std::format("Test cases failed: {}", countOfFailure), Adarsha::Status::ERROR);
    if (countOfFailure == 0)
    {
      printMessage("Test harness succeeded", Adarsha::Status::SUCCESS);
    }
    else
    {
      printMessage("Test harness failed", Adarsha::Status::ERROR); 
    }
  }
};
} // namespace Adarsha