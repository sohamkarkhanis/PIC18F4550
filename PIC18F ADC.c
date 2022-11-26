//Program to interface internal ADC of PIC18F and display the corresponding value on HD44780 without using any libraries

#include <pic18f4550.h>
#include<stdio.h>

#define en PORTCbits.RC1
#define rs PORTCbits.RC0
#define LCDPORT PORTB                  //Port B connected to data bus of LCD 

void lcd_delay(unsigned int time){
 unsigned int i , j ;
 for(i = 0; i < time; i++){
    for(j=0;j<50;j++);
    }
}

void lcd_cmd(unsigned char command){
     rs = 0;		
     LCDPORT = command;
     en = 1;		
     lcd_delay(10);
     en = 0;	
     lcd_delay(10);
}

void lcd_write(unsigned char lcddata){
     rs = 1;		
     LCDPORT = lcddata;
     en = 1;		
     lcd_delay(10);
     en = 0;	
     lcd_delay(10);
}



void main()
{
    unsigned short result;
    unsigned char i,text[16];
    TRISB = 0x00;                  //Set data port as output
    TRISCbits.TRISC0 = 0;          //Port CO pin connected to EN pin of LCD as output 
    TRISCbits.TRISC1 = 0;          //Port C1 pin connected to  RS pin of LCD as output
    TRISEbits.TRISE1 = 1;          //Port E1 pin used as ADC channel 6 defined as input
    
//lcd initialization
    lcd_cmd(0x38);      //8 bit mode, 2 line,5x7 dots
    lcd_cmd(0x06);	    //Entry mode
    lcd_cmd(0x0C);	    //Display ON cursor OFF
    lcd_cmd(0x01);      //Clear display
    lcd_cmd(0x80);      //set address to line 1 ,column 0
    
//ADC Initialization
    ADCON0 = 0b00011001;      	 //ADC on; Select channel 6
    ADCON1 = 0b00000111;         //Ref voltages Vdd & Vss; AN0 - AN7 channels Analog
    ADCON2 = 0b10101110;         //Right justified; Acquisition time 12T; Conversion clock Fosc/64


    while(1){ 
        ADCON0bits.GO_DONE = 1;           //Start Conversion

    while((ADCON0bits.GO_DONE) != 0 );    //Wait till A/D conversion is complete
        result = ADRES; 			      //Read value after ADC conversion
        lcd_cmd(0x80);                    //Set to 1st line
        sprintf(text,"%03X",result);   //Renders result as a string and stores it in array text
                                          //sprintf function formats and stores a series of characters
                                          //and values in the array pointed to by buffer
        
    for(i=0;i<3;i++){                     //Using an array to directly display a string on LCD, instead of 1 character at a time
        lcd_write(text[i]);
    }            
        lcd_delay(5000);   
}
}