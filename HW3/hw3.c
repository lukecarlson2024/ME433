#include "nu32dip.h" // constants, functions for startup and UART
#include "math.h"

void blink(int, int); // blink the LEDs function

int main(void) {
  char message[100];
  int time;
  int number;
  
  //sin wave
  float wave[100];
  for(int i = 0; i < 100; i++)
  {
      wave[i] = sin(((2*3.14159)/100)*i);
  }
  
  NU32DIP_Startup();
  while (1) {
      if (!NU32DIP_USER)
      {
          for(int i = 0; i < 100; i++)
            {
              sprintf(message, "%f\r\n", wave[i]);
              NU32DIP_WriteUART1(message);
              _CP0_SET_COUNT(0);
              while(_CP0_GET_COUNT() < 24000000*.01){}
            }
      }
  }
}