#ifndef __UNITY_TESTS_H__
#include "unity-tests.h"
#endif

void test_peripheral_creation(void)
{
    Peripheral *peripheral = peripheral_create();
    TEST_ASSERT_NOT_EQUAL(0, peripheral);
    peripheral_destroy(peripheral);
}

void test_peripheral_init(void)
{
    Peripheral *peripheral = peripheral_create();
    TEST_ASSERT_EQUAL(-1, peripheral->id);
    peripheral_destroy(peripheral);
}

void test_peripheral_add_service(void)
{
    Peripheral *peripheral = peripheral_create();
    Service *service = service_create();
    
    int rc = peripheral_add_service(service);
    TEST_ASSERT_EQUAL(0, rc);
    
    service_destroy(service);
    peripheral_destroy(peripheral);
}
