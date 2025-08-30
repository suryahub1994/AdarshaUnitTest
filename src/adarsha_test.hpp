#include <iostream>
#include <map>

#define TEST(name, value) Adarsha::TestRepository::registerTest(name, value)
#define RUN_ALL() Adarsha::TestRepository::runAll();
namespace Adarsha {
class TestRepository {
private:
  inline static std::map<std::string, std::function<bool()>> repository{};

public:
    static void registerTest(const std::string &testName,
                            std::function<bool()> func) {
        repository[testName] = func;
    }
    static void runAll() {
        for (auto [name, func] : repository) {
        if (func()) {
            std::cout << "Passed " << name << std::endl;
        } else {
            std::cout << "Failed " << name << std::endl;
        }
        }
    }
    };

    inline constexpr double DEFAULT_EPS = 1e-9;

    bool assert(bool condition, const std::string message) {
    if (condition) {
        return true;
    }
    std::cout << message << std::endl;
    return false;
    }
    template <typename T>
    bool assertEqual(const T &a, const T &b, const std::string &message) {
    if (a == b) {
        return true;
    }
    std::cout << message << std::endl;
    return false;
    }
    template <typename T>
    bool assertNotEqual(const T &a, const T &b, const std::string &message) {
    if (a != b) {
        return true;
    }
    std::cout << message << std::endl;
    return false;
    }
    template <typename T>
    bool assertLess(const T &a, const T &b, const std::string &message) {
    if (a < b) {
        return true;
    }
    std::cout << message << std::endl;
    return false;
    }
    template <typename T>
    bool assertGreater(const T &a, const T &b, const std::string &message) {
    if (a > b) {
        return true;
    }
    std::cout << message << std::endl;
    return false;
    }

    template <typename T>
    bool assertNear(const T &a, const T &b, const double eps = DEFAULT_EPS,
                    const std::string &message = "") {
    if (abs(a - b) < eps) {
        return true;
    }
    std::cout << message << std::endl;
    return false;
    }
    template <typename P> bool assertNull(P p, const std::string &msg = "") {
    if (p != nullptr) {
        return false;
    }
    std::cout << message << std::endl;
    return true;
    }
} // namespace Adarsha