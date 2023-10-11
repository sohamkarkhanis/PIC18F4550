// Program for interfacing Switch, LED, Relay & Buzzer
// When button 1 is pressed relay and buzzer is turned ON and LED chases left to right.
// When button 2 is pressed relay and buzzer is turned OFF and LED chases right to left.

#include <pic18F4550.h>

void delay() {
    unsigned int i;
    for (i = 0; i < 30000; i++);
}

void main() {
    char i, key = 0;
    TRISB = 0x00;        // LED pins as output
    LATB = 0x00;
    TRISDbits.TRISD0 = 1;        // set RD0 as input
    TRISDbits.TRISD1 = 1;        // set RD1 as input
    TRISDbits.TRISD2 = 0;        // set buzzer pin RD2 as output
    TRISAbits.TRISA4 = 0;        // set relay pin RA4 as output

    while (1) {
        if (PORTDbits.RD0 == 0) key = 0;        // If button1 pressed
        if (PORTDbits.RD1 == 0) key = 1;        // If button2 pressed
        if (key == 0) {
            LATAbits.LATA4 = 1;              // Relay On
            LATDbits.LATD2 = 0;              // Buzzer On
            
            for (i = 0; i < 8; i++) {        // Chase LED left to right
                LATB = 1 << i;
                delay();
                LATB = 0x00;
                delay();
            }
        }

        if (key == 1) {
            LATAbits.LATA4 = 0;               // Relay Off
            LATDbits.LATD2 = 1;               // Buzzer Off

            for (i = 7; i >= 0; i--) {        // Chase LED right to left
                LATB = 1 << i;
                delay();
                LATB = 0x00;
                delay();
            }
        }
    }
}