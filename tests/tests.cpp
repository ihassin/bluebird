#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef CU_TEST_H
#include "cutest.h"
#endif

void TestPasses(CuTest* tc)
{
  CuAssert(tc, "test should pass", 1 == 0 + 1);
}

CuSuite* CuGetSuite(void)
{
  CuSuite* suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, TestPasses);

  return suite;
}

