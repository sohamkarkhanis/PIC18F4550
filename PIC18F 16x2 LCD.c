// Interfacing the PIC18F4550 with Hitachi HD44780
// Add a code offset depending on Dev Board, 0x800 for me

#include <pic18f4550.h>
#include <stdio.h>
#include <xc.h>

#define EN      PORTCbits.RC1
#define RS      PORTCbits.RC0
#define LCDPORT PORTB        // Port B connected to data bus of LCD

void lcd_delay(unsigned int time) {
    unsigned int i, j;

    for (i = 0; i < time; i++) {
        for (j = 0; j < 50; j++);
    }
}

void lcd_cmd(unsigned char command) {
    RS = 0;
    LCDPORT = command;
    EN = 1;
    lcd_delay(10);
    EN = 0;
    lcd_delay(10);
}

void lcd_write(unsigned char lcddata) {
    RS = 1;
    LCDPORT = lcddata;
    EN = 1;
    lcd_delay(10);
    EN = 0;
    lcd_delay(10);
}

void main() {
    unsigned char i, text[16];
    TRISB = 0x00;                // set data port as output
    TRISCbits.TRISC0 = 0;        // Port CO pin connected to EN pin of LCD as output
    TRISCbits.TRISC1 = 0;        // Port C1 pin connected to RS pin of LCD as output

    // lcd initialization
    lcd_cmd(0x38);        // 8 bit mode, 2 line,5x7 dots
    lcd_cmd(0x06);        // Entry mode
    lcd_cmd(0x0C);        // Display ON cursor OFF
    lcd_cmd(0x01);        // Clear display
    lcd_cmd(0x80);        // set address to line 1 ,column 0

    while (1) {

        lcd_cmd(0x80);        // set to 1st line

        lcd_write('s');
        lcd_delay(5000);
        lcd_write('o');
        lcd_delay(5000);
        lcd_write('h');
        lcd_delay(5000);
        lcd_write('a');
        lcd_delay(5000);
        lcd_write('m');

        lcd_delay(5000);
    }
}