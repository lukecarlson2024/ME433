#include "nu32dip.h"
#include "uart2.h"

int main(void) {
    NU32DIP_Startup();
    char message2[100];
    // after NU32DIP_startup()
    ANSELA = 0;
    ANSELB = 0;
    UART2_Startup();
    /*
    //motor 1
    RPA0Rbits.RPA0R = 0b0101; //Makes A0 OC1
    // Make an output pin for B0
    TRISBbits.TRISB0 = 0;
    LATBbits.LATB0 = 0;
    T2CONbits.TCKPS = 0;     // Timer2 prescaler N=16 (1:16)
    PR2 = 2400;              // period = (PR2+1) * N * (1/48000000) = 50Hz, has to be less than 65000
    TMR2 = 0;                // initial TMR2 count is 0
    OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC1CONbits.OCTSEL = 0;   // Use timer2
    OC1RS = 2400-1;             // duty cycle = OC1RS/(PR2+1) = 25%
    OC1R = 2400-1;              // initialize before turning OC1 on; afterward it is read-only
    
    //motor 2
    RPA1Rbits.RPA1R = 0b0101; //Makes A1 OC1
    // Make an output pin for B0
    TRISBbits.TRISB1 = 0;
    LATBbits.LATB1 = 0;
    OC2CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC2CONbits.OCTSEL = 0;   // Use timer2
    OC2RS = 2400-1;             
    OC2R = 2400-1;   
    T2CONbits.ON = 1;        // turn on Timer2
    OC1CONbits.ON = 1;       // turn on OC1
    OC2CONbits.ON = 1;   
     */    
    while(1){
        // in while(1)
        int com = 0;
        // uart2_flag() is 1 when uart2 has rx a message and sprintf'd it into a value
        if(get_uart2_flag()){
            set_uart2_flag(0); // set the flag to 0 to be ready for the next message
            com = get_uart2_value();
            sprintf(message2,"%d\r\n",com);
            NU32DIP_WriteUART1(message2);
        }
    }
}