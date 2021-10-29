/*******************************************************
Chip type               : ATmega32
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega32.h>

unsigned char step[4] = {0x09 , 0x05 , 0x06 ,0x0A} ;
int i, time  ; 
bit SWITCH = 0 , inverse ;

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
TCNT0=0x83;  // TIME  = 1mS
time++ ;
PORTC.0 =! PORTC.0 ;

   if(time >4)
    {    

    PORTC.1 =! PORTC.1 ;
    time = 0 ;
      
        if(SWITCH == 1)
        {  PORTB = step[i];
            
            if(inverse == 0)
            {
            i++ ;
            if(i == 4) i = 0 ;
            }
            else
            {
            if(i == 0) i = 4 ;
            i-- ;
            }
        }
    }
    
    if(PINC.2 == 0 ) SWITCH =! SWITCH ;
    if(PINC.3 == 0 ) inverse =! inverse ;
     
}


void main(void)
{

TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (1<<CS01) | (1<<CS00);
TCNT0=0x83;
OCR0=0x00;
TIMSK = 0X01 ;


DDRB = 0X0F;
DDRC.0 = 1 ;
DDRC.1 = 1 ;

#asm("sei")



}
