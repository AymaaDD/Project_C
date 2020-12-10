#include "build/temp/_test_1.c"
#include "src/edid.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"
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

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((result)), (

   ((void *)0)

   ), (UNITY_UINT)(13), UNITY_DISPLAY_STYLE_INT);

}

void test_add2( void )

{

    int result = 0;

    result = FixIDID(3,255);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((result)), (

   ((void *)0)

   ), (UNITY_UINT)(19), UNITY_DISPLAY_STYLE_INT);

}
