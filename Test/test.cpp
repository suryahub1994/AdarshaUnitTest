#include "../src/adarsha_test.hpp"
int main() {
    TEST("add", []() { Adarsha::assertEqual(1,2, "This should be equal"); });
    RUN_ALL();
}