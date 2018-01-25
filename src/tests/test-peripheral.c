#ifndef __UNITY_TESTS_H__
#include "unity-tests.h"
#endif

void test_peripheral_creation(void)
{
    Peripheral *peripheral = peripheral_create();
    TEST_ASSERT_NOT_EQUAL(0, peripheral);
    peripheral_remove(peripheral);
}

void test_peripheral_init(void)
{
    Peripheral *peripheral = peripheral_create();
    TEST_ASSERT_EQUAL(-1, peripheral->id);
    peripheral_remove(peripheral);
}
