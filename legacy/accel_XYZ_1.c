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

PORTC=0x80;
CMD ();
_delay_ms(10);
PORTC='X';
DATA ();
_delay_ms(10);

PORTC='=';
DATA ();
_delay_ms(10);

PORTC=0x86;
CMD ();
_delay_ms(10);


PORTC='Y';
DATA ();
_delay_ms(10);

PORTC='=';
DATA ();
_delay_ms(10);

PORTC=0xC0;
CMD ();
_delay_ms(10);


PORTC='Z';
DATA ();
_delay_ms(10);

PORTC='=';
DATA ();
_delay_ms(10);


PORTC=0x00;
}
unsigned int a,b,i,x,y,z;
char f[3];
int main()
{
 
 

 ADMUX|=(1<<ADLAR);
 DDRD=0xFF;
 DDRB=0x07;                                                    

 DDRC=0xFF;
 sei();
 DDRA=0x00;


 LCD_INIT();

 _delay_ms(10);

 b=0;
 ADCSRA=0xCF;



 while(1)
 {	
	if(b==0)
	{
	ADMUX&=~(1<<0);
	ADMUX&=~(1<<1);
	_delay_ms(10);
	ADCSRA|=0x40;
	_delay_ms(100);

	x=ADCH;
	
	PORTC=0x82;
	CMD ();
	_delay_ms(10);

	itoa(x,f,10);
	_delay_ms(15);

	PORTA|=(1<<7);
	for(i=0;i<3;i++)
	{

	PORTC=' ';
	_delay_ms(1);	
	DATA();		
	_delay_ms(1);
	
	}
	PORTC=0x82;
	CMD();

	
	for(i=0;f[i]!='\0';i++)
	{
	
	PORTC=f[i];
	_delay_ms(10);	
	DATA();		
	_delay_ms(10);
	}

	_delay_ms(10);

	b=1;
	_delay_ms(10);
	
 	}
	
	if(b==1)
	{
	ADMUX|=(1<<0);
	_delay_ms(10);
	ADCSRA|=0x40;
	_delay_ms(100);
	
	y=ADCH;

	PORTC=0x88;
	CMD();
	_delay_ms(10);
	itoa(y,f,10);
	_delay_ms(15);

	for(i=0;i<3;i++)
	{

	PORTC=' ';
	_delay_ms(1);	
	DATA();		
	_delay_ms(1);
	
	}
	PORTC=0x88;
	CMD();

	for(i=0;f[i]!='\0';i++)
	{

	PORTC=f[i];
	_delay_ms(1);	
	DATA();		
	_delay_ms(1);
	
	}
	b=2;	
 	}
	

	if(b==2)
	{
	ADMUX|=(1<<1);
	ADMUX&=~(1<<0);

	_delay_ms(10);

	ADCSRA|=0x40;
	_delay_ms(100);
	
	z=ADCH;

	PORTC=0xC2;
	CMD();

	_delay_ms(10);
	itoa(z,f,10);
	_delay_ms(15);

	for(i=0;f[i]!='\0';i++)
	{
	
	PORTC=f[i];
	_delay_ms(10);	
	DATA();		
	_delay_ms(10);
	}
	b=0;
	}
	
 }
return 0;
}


ISR(ADC_vect)
{
	ADCSRA|=0x40;
}

