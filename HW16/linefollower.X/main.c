#include "nu32dip.h"
#include "uart2.h"

//READ THIS
//I could not get it to work properly, although I got pretty close.
//I had UART communication between the PIC and PICO, line detection through
//the camera, and motor control all working. The problems I ran into on the last
//day was that I accidentally printed the wheel holes too large, and most importantly
//I dropped the camera which completely ruined the image and made it impossible
//to detect a line. I think with an extra few hours I could fix it, but I don't
//have that time so I'm turning this in.

//This uses the same PICO code as HW15.

int main(void) {
    NU32DIP_Startup();
    char message2[100];
    // after NU32DIP_startup()
    ANSELA = 0;
    ANSELB = 0;
    UART2_Startup();
    
    //motor 1
    RPA0Rbits.RPA0R = 0b0101; //Makes A0 OC1
    // Make an output pin for B2
    TRISBbits.TRISB2 = 0;
    LATBbits.LATB2 = 0;
    T2CONbits.TCKPS = 0;     // Timer2 prescaler N=16 (1:16)
    PR2 = 2400;              // period = (PR2+1) * N * (1/48000000) = 50Hz, has to be less than 65000
    TMR2 = 0;                // initial TMR2 count is 0
    OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC1CONbits.OCTSEL = 0;   // Use timer2
    OC1RS = 600-1;             // duty cycle = OC1RS/(PR2+1) = 25%
    OC1R = 600-1;              // initialize before turning OC1 on; afterward it is read-only
    
    //motor 2
    RPB7Rbits.RPB7R = 0b0101; //Makes B7 OC1
    // Make an output pin for B0
    TRISBbits.TRISB1 = 0;
    LATBbits.LATB1 = 0;
    OC2CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC2CONbits.OCTSEL = 0;   // Use timer2
    OC2RS = 600-1;             
    OC2R = 600-1;   
    T2CONbits.ON = 1;        // turn on Timer2
    OC1CONbits.ON = 1;       // turn on OC1
    OC2CONbits.ON = 1;   
       
    
    while(1){
        // in while(1)
        int com = 0;
        // uart2_flag() is 1 when uart2 has rx a message and sprintf'd it into a value
        if(get_uart2_flag()){
            set_uart2_flag(0); // set the flag to 0 to be ready for the next message
            com = get_uart2_value();
            sprintf(message2,"%d\r\n",com);
            NU32DIP_WriteUART1(message2);
            if(com >= 30){
            OC2RS = 600-1;
            OC1RS = (600-1)*(1-((com-30)/30));
            }
            if(com < 30){
                OC1RS = 600-1;
                OC2RS = (600-1)*(1-((30-com)/30));
            }
        }
        
    }
}