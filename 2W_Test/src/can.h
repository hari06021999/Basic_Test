#ifndef CAN_H
#define CAN_H

#include <stdio.h> 
#include <stdint.h> 
#include <stdbool.h>

void can_start(uint8_t channel);
uint16_t can_receive(uint8_t channel, uint16_t can_id,uint16_t  data);
void led_state(bool state);


void can_start(uint8_t channel)
{
   if(channel == 1)
   {
      printf("CAN Has been started");
   }
   else
   {
      printf("CAN Hasn't been started");
   }
}

uint16_t can_receive(uint8_t channel, uint16_t can_id,uint16_t  data)
{
   if(channel == 1)
   {
      switch (can_id)
      {
      case 0x102:
        return data;
        break;
      
      case 0x103:
        return data;
        break;

      case 0x104:
        return data;
        break;
      default:
        return 0;
        break;
      }
   }
   else
   {
      printf("Invalid CAN channel");
      return 1;
   }
}

void led_state(bool state)
{
    if( state == true)
    {
       printf("LED Glowing");
       state = true;
    }
    if(state == false)
    {
       printf("LED not Glowing");
       state = false;
    }
    
}

#endif 