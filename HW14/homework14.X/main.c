#include "nu32dip.h"

int main(void) {
    RPA0Rbits.RPA0R = 0b0101; //Makes A0 OC1
    T2CONbits.TCKPS = 4;     // Timer2 prescaler N=16 (1:16)
    PR2 = 60000;              // period = (PR2+1) * N * (1/48000000) = 50Hz, has to be less than 65000
    TMR2 = 0;                // initial TMR2 count is 0
    OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC1CONbits.OCTSEL = 0;   // Use timer2
    OC1RS = 4860;             // duty cycle = OC1RS/(PR2+1) = 25%
    OC1R = 4860;              // initialize before turning OC1 on; afterward it is read-only
    T2CONbits.ON = 1;        // turn on Timer2
    OC1CONbits.ON = 1;       // turn on OC1
    while (1){
        //100 ~= 0 degrees
        //6500 ~= 180 degrees
        //36 ~= 1 degree
        //45 degrees = 36 * 45 = 1620
        //135 degrees = 36 * 135 = 4860
        OC1RS = 1620; //45 degrees
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT() < 24000000*4){} //wait 4 seconds
        OC1RS = 4860; //135 degrees
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT() < 24000000*4){} //wait 4 seconds
        
    }
//  OC1rs between 0 to PR2, 10% - 20%, how you define position
    //PWM 50hz --> 20ms
    //1.5 - 2.5 ms is 180

}
