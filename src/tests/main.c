#ifndef __UNITY_TESTS_H__
#include "unity-tests.h"
#endif

int main(void)
{
    printf("Starting tests!\n");
    
    UnityBegin("main.c");

    RUN_TEST(test_canary);
    
    return UnityEnd();
}
