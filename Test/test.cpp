#include "../src/adarsha_test.hpp"
int main()
{
    TEST("suryasis0", [](){ return Adarsha::assert(1==2, "Not equal"); });
    TEST("suryasis1", [](){ return Adarsha::assertEqual(1, 2, "Not equal"); });
    TEST("suryasis2", [](){ return Adarsha::assertNotEqual(1, 2, "Not equal"); });
    TEST("suryasis3", [](){ return Adarsha::assertLess(1, 2, "Not equal"); });
    TEST("suryasis4", [](){ return Adarsha::assertGreater(1, 2, "Not equal"); });
}