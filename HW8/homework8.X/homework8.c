#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c_master_noint.h"
#include "ssd1306.h"
#include "mpu60502.h"
#include <stdio.h>
#include "font.h"

void draw_character(unsigned char, unsigned char, unsigned char);
void draw_string(unsigned char x, unsigned char y, char * string);

char message[100];
int fps;

int main(void){
    NU32DIP_Startup();
    init_mpu6050();
    ssd1306_setup();
    
    //copy and pasting from HW7
    char array[8];
    float ax;
    float ay;
    float az;
    float gx;
    float gy;
    float gz;
    float temp;
    while(1){
        _CP0_SET_COUNT(0);
        //from HW7
        burst_read_mpu6050(array);
        ax = conv_xXL(array);
        ay = conv_yXL(array);
        az = conv_zXL(array);
        gx = conv_xG(array);
        gy = conv_yG(array);
        gz = conv_zG(array);
        temp = conv_temp(array);
        
        sprintf(message, "Z accel: %f", az); //draw z accel
        draw_string(5, 5, message);
        ssd1306_update();
        float fps = _CP0_GET_COUNT();
        sprintf(message, "FPS: %f", 1/(fps/24000000)); //draw FPS
        draw_string(50, 20, message);
        ssd1306_update();
    }
}

void draw_character(unsigned char x, unsigned char y, unsigned char character)
{
    int i;
    int j;
    //each letter 8 pixels tall, 5 pixels wide
    for(j = 0; j < 8; j++)
    {
        for(i = 0; i < 5; i++)
        {
            ssd1306_drawPixel(x+i, y+j, (ASCII[character - 0x20][i] >> j) & 1);
        }
    }
        
}

void draw_string(unsigned char x, unsigned char y, char * string){
    int i = 0;
    while (string[i] != '\0'){
        draw_character(x+i*5, y, string[i]);
        i++;
    }
}
