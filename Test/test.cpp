#include "../src/adarsha_test.hpp"
int main() {
    TEST("equal", []() { Adarsha::assertEqual(1,2, "This should be equal"); });
    TEST("not equal", []() { Adarsha::assertNotEqual(1,2, "This should be unequal"); }); 
    RUN_ALL();
}