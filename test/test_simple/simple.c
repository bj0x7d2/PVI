#include "simple.h"

#include <unity.h>

void
setUp (void)
{
  // set stuff up here
}

void
tearDown (void)
{
  // clean stuff up here
}

void
test_add ()
{
  TEST_ASSERT_EQUAL (3, add (1, 2));
}

void
app_main ()
{
  UNITY_BEGIN ();
  RUN_TEST (test_add);
  UNITY_END ();
}