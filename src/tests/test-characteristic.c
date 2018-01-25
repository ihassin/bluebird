#ifndef __UNITY_TESTS_H__
#include "unity-tests.h"
#endif

void test_characteristic_creation(void)
{
    Characteristic *characteristic = characteristic_create();
    TEST_ASSERT_NOT_EQUAL(0, characteristic);
    characteristic_destroy(characteristic);
}

void test_characteristic_init(void)
{
    Characteristic *characteristic = characteristic_create();
    TEST_ASSERT_EQUAL(-1, characteristic->id);
    characteristic_destroy(characteristic);
}
