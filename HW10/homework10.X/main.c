#include "nu32dip.h"
#include "ws2812b.h"
#include "math.h"

int main () {
    NU32DIP_Startup(); //initialize
    ws2812b_setup();
    wsColor array[7]; //color array
    while(1){
        int i = 0;
        int c = 0;
        int j[6];
        j[0] = 0;
        j[1] = 30;
        j[2] = 60;
        j[3] = 90;
        j[4] = 120;
        j[5] = 150;
        j[6] = 180;
        for(i = 0; i < 360; i++){ //generate rainbow
                array[0] = HSBtoRGB(360, 1, .1); //this LED is uncontrollable
                //for some reason
                array[1] = HSBtoRGB(j[0], 1, 1);
                array[2] = HSBtoRGB(j[1], 1, 1);
                array[3] = HSBtoRGB(j[2], 1, 1);
                array[4] = HSBtoRGB(j[3], 1, 1);
                array[5] = HSBtoRGB(j[4], 1, 1);
                array[6] = HSBtoRGB(j[5], 1, 1);
                array[7] = HSBtoRGB(360, 1, 1); //making this green like the 
                //first LED for symmetry
                ws2812b_setColor(array, 8);
                _CP0_SET_COUNT(0);
                while(_CP0_GET_COUNT() < 240000) {;}
                for(c = 0; c < 6; c++){ 
                    j[c]++; //next color
                    if(j[c] == 360){//reset color cycles
                        j[c] = 0;
                    }
                }
        }
    }
    
}