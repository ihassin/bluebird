#ifndef __UNITY_TESTS_H__
#include "unity-tests.h"
#endif

void test_service_creation(void)
{
    Service *service = service_create();
    TEST_ASSERT_NOT_EQUAL(0, service);
    service_destroy(service);
}

void test_service_init(void)
{
    Service *service = service_create();
    TEST_ASSERT_EQUAL(-1, service->id);
    service_destroy(service);
}

void test_service_add_characteristic(void)
{
    Service *service = service_create();
    Characteristic *characteristic = characteristic_create();
    
    int rc = service_add_characteristic(service, characteristic);
    TEST_ASSERT_EQUAL(0, rc);
    
    characteristic_destroy(characteristic);
    service_destroy(service);
}
