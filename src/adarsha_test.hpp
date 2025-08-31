#pragma once
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
    for (auto& [name, fn] : repository) {
      try {
        fn();
        std::string message = "PASS: " + name;
        printMessage(message, Adarsha::Status::SUCCESS);
      } catch (const Adarsha::AssertFail& e) {
        std::string failMessage =  "FAIL " +  name + " : " +  e.what();
        printMessage(failMessage, Adarsha::Status::ERROR);

      } catch (...) {
        std::string failMessage =  "FAIL " +  name + " : " + "Unknown exception";
        printMessage(failMessage, Adarsha::Status::ERROR); 
      }
    }
  }
};
} // namespace Adarsha