/********************************************************************
 * COPYRIGHT --
 ********************************************************************
 * Program: -
 * Author:
 * Created: 
 ********************************************************************
 * Tests for ... 
 ********************************************************************/

#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"

_CYCLIC_SET()
{

	/* TODO:  add code running cyclically while test set is active here */
	return;
}


_SETUP_SET(void)
{
	/* TODO:  add code running before test set here */
	TEST_DONE;
}

_TEARDOWN_SET(void)
{
	/* TODO:  add code running after test set here */
	TEST_DONE;
}


_SETUP_TEST(void)
{
	/* TODO:  add code running before test case here */
	TEST_DONE;
}

_TEARDOWN_TEST(void)
{
	/* TODO:  add code running after test case here */
	TEST_DONE;
}


_TEST testcase1(void)
{

	/* TODO:  add assertions here */

	/* test is done */
	TEST_ASSERT_EQUAL_INT(3, 1);
	TEST_DONE;
}

_TEST testcase2(void)
{

	/* TODO:  add assertions here */

	/* test is done */
	TEST_ASSERT_EQUAL_INT(3, 3);
	TEST_DONE;
}



/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2025-12-15 13:53:02Z
By B+R UnitTest Helper Version: 2.0.0.0
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("testcase1", testcase1), 
	new_TestFixture("testcase2", testcase2), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_brse_arl, "Set_brse_arl", setupTest, teardownTest, fixtures, setupSet, teardownSet, cyclicSetCaller);

