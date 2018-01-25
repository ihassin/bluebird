#ifndef __UNITY_TESTS_H__
#include "unity-tests.h"
#endif

int main(void)
{
    UnityBegin("main.c");

    // Listening on requested port
    RUN_TEST(test_canary);
    return UnityEnd();
}
