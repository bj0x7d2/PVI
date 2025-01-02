#include <unity.h>

#include "simple.h"

void test_add() {
    TEST_ASSERT_EQUAL(3, add(1, 2));
}

void test_sub() {
    TEST_ASSERT_EQUAL(1, sub(2, 1));
}

void app_main () {
    UNITY_BEGIN();
    RUN_TEST(test_add);
    RUN_TEST(test_sub);
    UNITY_END();
}