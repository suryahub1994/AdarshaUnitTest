#include <iostream>
#include <map>
#include <source_location>

#include "adarsha_assertions.hpp"

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
        std::cout << "PASS " << name << "\n";
      } catch (const Adarsha::AssertFail& e) {
        std::cout << "FAIL " << name << " : " << e.what() << "\n";
      } catch (...) {
        std::cout << "FAIL " << name << " : unknown exception\n";
      }
    }
  }
};
} // namespace Adarsha