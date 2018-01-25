#ifndef __UNITY_TESTS_H__
#define __UNITY_TESTS_H__

#ifndef UNITY_FRAMEWORK_H
#include "../unity/src/unity.h"
#endif

#ifndef __SERVICE_H__
#include "../service.h"
#endif

void test_canary(void);
void test_service_creation(void);

#endif
