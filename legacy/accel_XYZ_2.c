#ifndef F_CPU                                                                                          
#define F_CPU 16000000UL                                                                
#endif
#include<avr/io.h>  
#include<stdlib.h> 
#include<string.h>                                                                             
#include<util/delay.h>                                                                           
#include<avr/interrupt.h>

void CMD ()
{
 PORTB&=~(1<<0);                                                                           
 PORTB&=~(1<<1);                                                                         
 PORTB|=(1<<2);                                                                              
 _delay_ms(10);
 PORTB&=~(1<<2);
 _delay_ms(10);                                                                           
}

void DATA ()
{
 PORTB|=(1<<0);                               
 PORTB&=~(1<<1);                                                                        
 PORTB|=(1<<2);                                                                         
 _delay_ms(10);
 PORTB&=~(1<<2);
 _delay_ms(10);                                                                        
}

void LCD_INIT()
{

PORTC=0x38;
CMD ();
_delay_ms(10);
PORTC=0x0E;
CMD ();
_delay_ms(10);
PORTC=0x01;
CMD ();
_delay_ms(10);
PORTC=0x06;
CMD ();
_delay_ms(10);

PORTC='v';
DATA ();
_delay_ms(10);

PORTC='=';
DATA ();
_delay_ms(10);

PORTC=0x82;
CMD ();
_delay_ms(10);

PORTC=0x00;
}

int main()
{
 
 float a,x;
 unsigned int d,i;
 char f[2];

 DDRD=0xFF;
 PORTD=0x00;
 DDRB=0x07;                                                    

 DDRC=0xFF;

 DDRA=0x00;


 LCD_INIT();

 sei();
 ADMUX=0x02;
// ADMUX|=(1<<ADLAR);
 ADCSRA=0xCF;
	
 PORTB=0x00;
 PORTC=0x00;
 PORTD=0x00;


 while(1)
 {	

	d=ADCL;
	
	_delay_ms(200);
	PORTC=0x0E;
	CMD();
	
	_delay_ms(1);
	
	PORTC=0x82;
	CMD ();
	_delay_ms(10);
	itoa(d,f,10);
	_delay_ms(15);

	for(i=0;i<3;i++)
	{
	
	PORTC=f[i];
	_delay_ms(10);	
	DATA();		
	_delay_ms(10);
	}


	
 }
	return 0;
}




ISR(ADC_vect)
{
//	PORTC=ADCH;
	ADCSRA|=0x40;

}

