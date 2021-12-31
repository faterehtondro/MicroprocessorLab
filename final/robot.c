#include <mega16a.h>
#include <delay.h>

#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))
unsigned int read_adc(unsigned char adc_input) // read analog to digital conversion
{
ADMUX=adc_input | ADC_VREF_TYPE;
delay_us(50); //stabilization of the ADC input
ADCSRA|=(1<<ADSC);
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCW;
}

void main(void)
{
// Declare your local variables here
int s=0;

// Port A initialization
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) |(0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) |(0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) |(0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) |(0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) |(0<<PORTB1) | (0<<PORTB0);

// Port C initialization
DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) |(1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) |(0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) |(0<<PORTC1) | (0<<PORTC0);

// Port D initialization
DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) |(1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) |(0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) |(0<<PORTD1) | (0<<PORTD0);

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 125.000 kHz
// Mode: Fast PWM top=0x00FF
// OC1A output: Non-Inverted PWM
// OC1B output: Non-Inverted PWM
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 2.048 ms
// Output Pulse(s):
// OC1A Period: 2.048 ms Width: 0 us
// OC1B Period: 2.048 ms Width: 0 us
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(1<<COM1A1) | (0<<COM1A0) | (1<<COM1B1) |(0<<COM1B0) | (0<<WGM11) | (1<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12)| (0<<CS12) | (1<<CS11) | (1<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;
// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0<<AS2;
TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) |(0<<CS22) | (0<<CS21) | (0<<CS20);
TCNT2=0x00;
OCR2=0x00;
// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) |(0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);
// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
// ADC initialization
// ADC Clock frequency: 125.000 kHz
// ADC Voltage Reference: AREF pin
// ADC Auto Trigger Source: ADC Stopped
ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (0<<ADPS0);
SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);


PORTD.0=1; // pin IN1 from l293 set 1
PORTD.1=0;
PORTD.2=0;
PORTD.3=1; // pin IN4 from l293 set 1

OCR1AL=0; //duty cycle set zero
OCR1BL=0; //duty cycle set zero


while (1)
{

s=1;
if((read_adc(6)>500) && s==1)
{
PORTD.0=0;
PORTD.1=1; //pin IN2 from l293 set 1
PORTD.2=0;
PORTD.3=1; //pin IN4 from l293 set 1
OCR1AL=125;
OCR1BL=125;
PORTC.6=1;
delay_ms(100);
PORTC.6=0;
s=0;
}

if((read_adc(5)>500) && s==1)
{
PORTD.0=1;//pin IN1 from l293 set 1
PORTD.1=0;
PORTD.2=0;
PORTD.3=1;//pin IN4 from l293 set 1
OCR1AL=125;
OCR1BL=45; //correction way of robot
PORTC.5=1;
delay_ms(100);
PORTC.5=0;
s=0;
}

if((read_adc(4)>500) && s==1)
{
PORTD.0=1; //pin IN1 from l293 set 1
PORTD.1=0;
PORTD.2=0;
PORTD.3=1; //pin IN4 from l293 set 1
OCR1AL=125;
OCR1BL=80;//correction way of robot
PORTC.4=1;
delay_ms(100);
PORTC.4=0;
s=0;
}

if((read_adc(3)>500) && s==1)
{
PORTD.0=1; //pin IN1 from l293 set 1
PORTD.1=0;
PORTD.2=0;
PORTD.3=1;//pin IN4 from l293 set 1
OCR1AL=125;
OCR1BL=125;
PORTC.3=1;
delay_ms(100);
PORTC.3=0;
s=0;
}

if((read_adc(2)>500) && s==1)
{
PORTD.0=1;//pin IN1 from l293 set 1
PORTD.1=0;
PORTD.2=0;
PORTD.3=1;//pin IN4 from l293 set 1
OCR1AL=80;//correction way of robot
OCR1BL=125;
PORTC.2=1;
delay_ms(100);
PORTC.2=0;
s=0;
}

if((read_adc(1)>500) && s==1)
{
PORTD.0=1;//pin IN1 from l293 set 1
PORTD.1=0;
PORTD.2=0;
PORTD.3=1;//pin IN4 from l293 set 1
OCR1AL=45;//correction way of robot
OCR1BL=125;
PORTC.1=1;
delay_ms(100);
PORTC.1=0;
s=0;
}

if((read_adc(0)>500) && s==1)
{
PORTD.0=1;//pin IN1 from l293 set 1
PORTD.1=0;
PORTD.2=1;//pin IN3 from l293 set 1
PORTD.3=0;
OCR1AL=125;
OCR1BL=125;
PORTC.0=1;
delay_ms(100);
PORTC.0=0;
s=0;
}

} // end of while
} // end of main