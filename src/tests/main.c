#ifndef __UNITY_TESTS_H__
#include "unity-tests.h"
#endif

int main(void)
{
    printf("Hello tests!\n");
    UnityBegin("main.c");

    // Listening on requested port
    RUN_TEST(test_canary);
    return UnityEnd();
}
