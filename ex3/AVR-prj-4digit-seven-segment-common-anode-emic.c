
#include <mega16.h>     
#include <delay.h>      

void main(void)
{
unsigned char seg[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};    
DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

while (1)
      {
      PORTD=0b00000001;  
      PORTC=seg[1];      
      delay_ms(1000);     

      PORTD=0b00000010;    
      PORTC=seg[2];       
      delay_ms(1000);      

      PORTD=0b00000100;    
      PORTC=seg[3];       
      delay_ms(1000);      

      PORTD=0b00001000;   
      PORTC=seg[4];      
      delay_ms(1000);      
      }
}