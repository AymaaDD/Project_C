#include "unity.h"
#include "edid.h"
void setUp(void)
{
}
void tearDown(void)
{
}
void test_add( void )
{
    int result = 0;
    result = FixIDID(0,255);
    TEST_ASSERT_EQUAL_INT( 1, result );
}
void test_add2( void )
{
    int result = 0;
    result = FixIDID(3,255);
    TEST_ASSERT_EQUAL_INT( 0, result );
}
