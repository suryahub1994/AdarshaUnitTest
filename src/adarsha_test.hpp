#pragma once
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <format>
#include <source_location>

#include "adarsha_assertions.hpp"
#include "adarsha_logging.hpp"

namespace Adarsha {

class TestRepository {
private:
  inline static std::map<std::string, std::function<void()>> repository{};

public:
  static void registerTest(std::string name, std::function<void()> fn) {
    repository.emplace(std::move(name), std::move(fn));
  }
  static int listTest() {
    for (auto& [name, fn] : repository) {
        std::cout<<name<<std::endl;
    }
    std::cout<<std::endl;
  }

  static int runAll(const std::set<std::string>& filter = {}) {
    int pass = 0, fail = 0;
    for (auto& [name, fn] : repository) {
      if (!filter.empty() && !filter.count(name)) continue;
      try {
        fn();
        ++pass;
        printMessage("PASS: " + name, Status::SUCCESS);
      } catch (const AssertFail& e) {
        ++fail;
        printMessage("FAIL " + name + " : " + e.what(), Status::ERROR);
      } catch (...) {
        ++fail;
        printMessage("FAIL " + name + " : Unknown exception", Status::ERROR);
      }
    }
    printMessage("-------------------------------------------", Status::SUCCESS);
    printMessage(std::format("Test cases passed: {}", pass), Status::SUCCESS);
    printMessage(std::format("Test cases failed: {}", fail), Status::ERROR);
    printMessage(fail ? "Test harness failed" : "Test harness succeeded",
                 fail ? Status::ERROR : Status::SUCCESS);
    return fail ? 1 : 0;
  }
};

// Registrar must be defined **after** TestRepository so it can call it.
struct TestRegistrar {
  TestRegistrar(const std::string& name, std::function<void()> fn) {
    TestRepository::registerTest(name, std::move(fn));
  }
};

} // namespace Adarsha

// ----- Macros -----
// Two-stage token pasting to make a unique identifier with __LINE__
#define AD_JOIN2(a,b) a##b
#define AD_JOIN(a,b)  AD_JOIN2(a,b)

// Define a test at global scope using a static registrar object.
// Usage: TEST("name", []{ /* body */ });
#define TEST(name, lambda_body) \
  static ::Adarsha::TestRegistrar AD_JOIN(_adarsha_reg_, __LINE__){ (name), (lambda_body) }

#define RUN_ALL() ::Adarsha::TestRepository::runAll()

#define RUN_ALL_WITH(names) ::Adarsha::TestRepository::runAll((names))

#define LIST() ::Adarsha::TestRepository::listTest();
