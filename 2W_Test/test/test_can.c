#include <unity.h>
#include "can.h"


uint8_t channel;
uint8_t Current_State;
bool  state;
void setUp(void)
{
  channel = 1;
  Current_State = 0;
  state = false;
}
void tearDown(void)
{
    // Clear the memory Before Testing the Cases
}

void test_led(void)
{
    
    led_state(state);
   TEST_ASSERT_TRUE (state == false);
    
}

void test_led1(void)
{
    state = true;
    led_state(state);
   TEST_ASSERT_TRUE (state == true);
    
}
void test_canstart(void)
{
    
    can_start(channel);
    uint8_t ch = channel;
    TEST_ASSERT_EQUAL_INT8(1,ch);  
}

void test_canstart1(void)
{
    channel = 2;
    can_start(channel);
    uint8_t ch = channel;
    TEST_ASSERT_EQUAL_INT8(1,ch);  
}


void test_can_receive(void)
{
    uint16_t data = can_receive(1,0x102,20);
    TEST_ASSERT_EQUAL_INT8(20,data);
}

void test_can_rec1(void)
{
     uint16_t data = can_receive(1,0x103,20);
    TEST_ASSERT_EQUAL_INT8(20,data);
}
void test_can_rec2(void)
{
     uint16_t data = can_receive(1,0x104,20);
    TEST_ASSERT_EQUAL_INT8(20,data);
}

void test_can_rec3(void)
{
     uint16_t data = can_receive(1,0x105,20);
    TEST_ASSERT_EQUAL_INT8(20,data);
}

void test_can_rec4(void)
{
     uint16_t data = can_receive(2,0x105,20);
    TEST_ASSERT_EQUAL_INT8(20,data);
}
