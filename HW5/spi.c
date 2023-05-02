#include "nu32dip.h"
#include "spi.h"
#include "math.h"

int main () {
    NU32DIP_Startup(); //initialize
    initSPI();
    float sinewave = 0;
    float triwave = 0;
    float t = 0;
    unsigned int f = 0;
    unsigned int f2 = 0;
    int direction = 1;
    int counter = 0;
    while(1){
        _CP0_SET_COUNT(0);
        
        //calculate sin wave
        //need plus 512, and multiply by amplitude
        //to keep within 0-1023
        sinewave = 511*sin(2*3.14159*(t/1000)*2) + 512;
        f = sinewave;
        t++;
        
        unsigned short v = 0;
        v = 0b111<<12;
        v = v|(0b0<<15); //DAC A
        
        //add sinewave voltage
        
        v = v|(f<<2);
                
 
        //send voltage with spi
        LATBbits.LATB9 = 0;
        spi_io(v>>8);
        spi_io(v);
        LATBbits.LATB9 = 1;
        
        //triangle wave
        //slope of triangle wave is rise/run = 1023/(1000*.5*1) = 2.046
        triwave = 2.046*counter*direction;
        counter++;
        if (counter <= 500)
        {
            direction = 1;
        }
        if (counter > 500)
        {
            direction = -1;
        }
        if (counter >= 1000)
        {
            counter = 0;
        }
        
        f2 = triwave;
        
        unsigned short v2 = 0;
        v2 = 0b111<<12;
        v2 = v2|(0b1<<15); //DAC B
        
        //add triwave voltage
        
        v2 = v2|(f2<<2);
                
 
        //send voltage with spi
        LATBbits.LATB9 = 0;
        spi_io(v2>>8);
        spi_io(v2);
        LATBbits.LATB9 = 1;
        
             
        while(_CP0_GET_COUNT() < 24000) {;} //wait 1ms
    }
}

// initialize SPI1
void initSPI() {
    // Pin B14 has to be SCK1
    // Turn of analog pins
    ANSELA = 0;
    // Make an output pin for CS, B9
    TRISBbits.TRISB9 = 0;
    LATBbits.LATB9 = 1;
    // Set SDO1, B11
    RPB11Rbits.RPB11R = 0b0011; 
    // Set SDI1, not relevant here

    // setup SPI1
    SPI1CON = 0; // turn off the spi module and reset it
    SPI1BUF; // clear the rx buffer by reading from it
    //2000 for 12kHz:
    SPI1BRG = 239; // 1000 for 24kHz, 1 for 12MHz; // baud rate to 10 MHz [SPI1BRG = (48000000/(2*desired))-1]
    SPI1STATbits.SPIROV = 0; // clear the overflow bit
    SPI1CONbits.CKE = 1; // data changes when clock goes from hi to lo (since CKP is 0)
    SPI1CONbits.MSTEN = 1; // master operation
    SPI1CONbits.ON = 1; // turn on spi 
}


// send a byte via spi and return the response
unsigned char spi_io(unsigned char o) {
  SPI1BUF = o;
  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI1BUF;
}