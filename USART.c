//Program to establish serial communication between a PC and the PIC18F	

//		2)Parity    None
//		3)Databits  8
//		4)Stop bits 1

#include<pic18f4550.h>

//Function to transmit data to PC
void transmit(char data){
    while(TXSTAbits.TRMT==0);   //Wait till transmit buffer is not empty(when TRMT=1,register empty)
    TXREG = data;			    //Load data in TXREG for Transmission
}						 



void main(){
 unsigned char i=0;
 unsigned char String[]={"Press a key bro!\n\r"};  //User will be prompted to press any key on the PC's keyboard
 unsigned char String1[]={"\n\rUART Works!\n\r"};  // If serial communication is successfully established, this string will be returned on TerraTerm App

 SSPCON1 = 0;            //Make sure SPI is disabled	
 TRISB = 0;              //Configure PORTB as output
 TRISCbits.TRISC7=1;     //Configure C7 as input for RX
 TRISCbits.TRISC6=0;     //Configure C6 as output for TX
 SPBRG = 0x4D;           //Load register to set Baud rate 9600 for 48MHz
 
/*
BRG16 = 0 : 8-bit baud rate generator.
BRGH = 0:   Low baud rate.
Thus, n = Fosc / [64 * (SPBRG + 1)]       //Formula in Datasheet
i.e. SPBRG = [Fosc / (64 * n)]   1
for Fosc = 48MHz, n = 9600 
SPBRG = [48MHz/(64*9600)]-1
=77=4d
*/
 
//Set Transmit and receive Control /status register
 TXSTA = 0x20;       // TX Enabled 
 RCSTA = 0x90;       // Continuous RX

 //Transmit data to PC
 for(i=0;String[i]!='\0';i++){
  transmit(String[i]);          //call function to transmit data 
 }
 
//receive data from PC
 while(PIR1bits.RCIF==0);       //Wait until data from PC is received(key pressed) (when RCIF=1 ,data available))                               
	PORTB = RCREG;              //transfer the data available in receive register to PORTB

//transmit data to PC
 for(i=0;String1[i]!='\0';i++){
  transmit(String1[i]);         //when input recieved from pc, send string1 saying "uart works!" 
 }
    
 while(1);		//loop forever
}



