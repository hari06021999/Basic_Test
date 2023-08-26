#include "src/can.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




uint8_t channel;

uint8_t Current_State;



_Bool 

     state;

void setUp(void)

{

  channel = 1;

  Current_State = 0;

  state = 

         0

              ;

}

void tearDown(void)

{



}



void test_led(void)

{



    led_state(state);

   do {if ((state == 

  0

  )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(23)));}} while(0);



}



void test_led1(void)

{

    state = 

           1

               ;

    led_state(state);

   do {if ((state == 

  1

  )) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(31)));}} while(0);



}

void test_canstart(void)

{



    can_start(channel);

    uint8_t ch = channel;

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((1)), (UNITY_INT)(UNITY_INT8 )((ch)), (

   ((void *)0)

   ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_INT8);

}



void test_canstart1(void)

{

    channel = 2;

    can_start(channel);

    uint8_t ch = channel;

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((1)), (UNITY_INT)(UNITY_INT8 )((ch)), (

   ((void *)0)

   ), (UNITY_UINT)(47), UNITY_DISPLAY_STYLE_INT8);

}





void test_can_receive(void)

{

    uint16_t data = can_receive(1,0x102,20);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((20)), (UNITY_INT)(UNITY_INT8 )((data)), (

   ((void *)0)

   ), (UNITY_UINT)(54), UNITY_DISPLAY_STYLE_INT8);

}



void test_can_rec1(void)

{

     uint16_t data = can_receive(1,0x103,20);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((20)), (UNITY_INT)(UNITY_INT8 )((data)), (

   ((void *)0)

   ), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_INT8);

}

void test_can_rec2(void)

{

     uint16_t data = can_receive(1,0x104,20);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((20)), (UNITY_INT)(UNITY_INT8 )((data)), (

   ((void *)0)

   ), (UNITY_UINT)(65), UNITY_DISPLAY_STYLE_INT8);

}



void test_can_rec3(void)

{

     uint16_t data = can_receive(1,0x105,20);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((20)), (UNITY_INT)(UNITY_INT8 )((data)), (

   ((void *)0)

   ), (UNITY_UINT)(71), UNITY_DISPLAY_STYLE_INT8);

}



void test_can_rec4(void)

{

     uint16_t data = can_receive(2,0x105,20);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((20)), (UNITY_INT)(UNITY_INT8 )((data)), (

   ((void *)0)

   ), (UNITY_UINT)(77), UNITY_DISPLAY_STYLE_INT8);

}
