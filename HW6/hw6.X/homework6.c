#include "nu32dip.h"
#include "i2c_master_noint.h"
#include "math.h"

void write(unsigned char, unsigned char);
char read(unsigned char);

int main ()
{
    NU32DIP_Startup();
    i2c_master_setup();
    //initialize pins, GP0 as input, GP7 as output
    write(0x00, 0b00000001); //all pins output except GP0
    
    while(1)
    {
        //blink yellow LED, as heartbeat
        LATBbits.LATB5 = 0;  
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT() < 2400000) {;}
        LATBbits.LATB5 = 1;
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT() < 2400000) {;}
        
        //blink GP7, commented out, for testing purposes
        //write(0x0A, 0b11111111); //turn on
        //_CP0_SET_COUNT(0);
        //while(_CP0_GET_COUNT() < 2400000) {;}
        //write(0x0A, 0b00000000); //turn off
        //_CP0_SET_COUNT(0);
        //while(_CP0_GET_COUNT() < 2400000) {;}
        if ((read(0x09) & 0b1) > 0)
        {
            write(0x0A, 0b00000000); //turn on
        }
        else
        {
            write(0x0A, 0b11111110); //turn on
        }
    }
}

void write(unsigned char reg_add, unsigned char value)
{
    i2c_master_start();
    //send address with write bit (0)
    //address is 0 1 0 0 A2 A1 A0 R/W, all 'A' pins are connected to ground
    i2c_master_send((0b0100000 << 1) | 0);
    //send register we want to change
    i2c_master_send(reg_add);
    //send value
    i2c_master_send(value);
    //send stop
    i2c_master_stop();
}

char read(unsigned char reg_add)
{
    i2c_master_start();
    //send address with write bit (0)
    i2c_master_send((0b0100000 << 1) | 0);
    //send register we want to read from
    i2c_master_send(reg_add);
    //restart
    i2c_master_restart();
    //send address with read bit (1)
    i2c_master_send((0b0100000 << 1) | 1);
    //recv from the chip
    char data = i2c_master_recv();
    //ack with a 1
    i2c_master_ack(1);
    //stop
    i2c_master_stop();
    return data;
}