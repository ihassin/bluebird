#ifndef __UNITY_TESTS_H__
#include "unity-tests.h"
#endif

void test_service_creation(void)
{
    Service *service = service_create();
    TEST_ASSERT_NOT_EQUAL(0, service);
    service_remove(service);
}

void test_service_init(void)
{
    Service *service = service_create();
    TEST_ASSERT_EQUAL(-1, service->id);
    service_remove(service);
}
