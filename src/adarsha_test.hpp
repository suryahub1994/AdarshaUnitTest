#include <iostream>
#include <map>

#define TEST(name, value) Adarsha::TestRepository::registerTest(name, value)

namespace Adarsha
{
    class TestRepository 
    {
        private:
             inline static std::map<std::string, std::function<bool()>> repository{};
        public:
            static void registerTest(const std::string &testName, std::function<bool()> func) 
            {
                repository[testName] = func;
            }
    }; 

    bool assert(bool condition, const std::string message) {
        if(condition)
        {
            return true;
        }
        std::cout<<message<<std::endl;
        return false;
    }
    template<typename T> bool assertEqual(const T& a, const T& b, const std::string& message) {
        if(a == b)
        {
            return true;
        }
        std::cout<<message<<std::endl;
        return false;
    } 
    template<typename T> bool assertNotEqual(const T& a, const T& b, const std::string& message) {
        if(a != b)
        {
            return true;
        }
        std::cout<<message<<std::endl;
        return false;
    } 
    template<typename T> bool assertLess(const T& a, const T& b, const std::string& message) {
        if(a < b)
        {
            return true;
        }
        std::cout<<message<<std::endl;
        return false;
    }
    template<typename T> bool assertGreater(const T& a, const T& b, const std::string& message) {
        if(a > b)
        {
            return true;
        }
        std::cout<<message<<std::endl;
        return false;
    } 
}