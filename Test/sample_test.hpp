# include "../src/adarsha_test.hpp"

TEST("trueTest", []() {  Adarsha::assert(false, "It should be true"); });
TEST("falseTest", []() {  Adarsha::assert(!false, "It should be true"); });