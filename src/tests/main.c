#ifndef __UNITY_TESTS_H__
#include "unity-tests.h"
#endif

int main(void)
{
    printf("Starting tests!\n\r");
    
    UnityBegin("main.c");

    RUN_TEST(test_canary);

    /* Service tests */
    RUN_TEST(test_service_creation);
    RUN_TEST(test_service_init);

    /* Characteristic tests */
    RUN_TEST(test_characteristic_creation);
    RUN_TEST(test_characteristic_init);

    /* Peripheral tests */
    RUN_TEST(test_peripheral_creation);
    RUN_TEST(test_peripheral_init);
    RUN_TEST(test_peripheral_add_service);
    
    return UnityEnd();
}
