/*
 * TIMER.c
 *
 * Author : A. Giuffra
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void TIM_init(uint8_t TIMER)
{
	if (TIMER == 0)
	{
		PRR		&=~ (1 << PRTIM0);	// Aseguramos que el TIM se encuentre encendido
		
		TCCR0A	&=~	(1 << COM0A1) || (1 << COM0A0);	// El canal A lo dejamos en output mode normal 
		TCCR0A	&=~ (1 << COM0B1) || (1 << COM0B0);	// El canal B lo dejamos en output mode normal 
		TCCR0A	|=	(1 << WGM01) || (0 << WGM00);	// El timer lo usaremos en modo CTC
		
		TCCR0B	&=~	(1 << FOC0A) || (1 << FOC0B);	// No se forzará ningún canal
		TCCR0B	&=~	(1 << WGM02);	// Dejamos en 0 para que el modo siga siendo CTC
		TCCR0B	|=	(1 << CS02) || (0 << CS01) || (1 << CS00); // Preescalador de 1024
		
		TIMSK0	|=	(0 << OCIE0B) || (1 << OCIE0A) || (0 << TOIE0);	// Activamos interrupción por comparación del canal A
		
		OCR0A = 156;	// Recordar que es de 8 bits (0-255), con preescalador de 1024 a 16 MHz, el timer interrumpe cada 10 ms
		
	} else if (TIMER == 1)
	{
		PRR		&=~ (1 << PRTIM1);	// Aseguramos que el TIM se encuentre encendido
	
		TCCR1A	&=~	(1 << COM1A1) || (1 << COM1A0);	// El canal A lo dejamos en output mode normal
		TCCR1A	&=~ (1 << COM1B1) || (1 << COM1B0);	// El canal B lo dejamos en output mode normal
		TCCR1A	&=~	(1 << WGM11) || (1 << WGM10);	// El timer lo usaremos en modo CTC
	
		TCCR1B	&=~	(1 << FOC1A) || (1 << FOC1B);	// No se forzará ningún canal
		TCCR1B	|=	(0 << WGM13) || (1 << WGM12);	// Dejamos en 0 para que el modo siga siendo CTC
		TCCR1B	|=	(1 << CS12) || (0 << CS11) || (1 << CS10); // Preescalador de 1024
	
		TIMSK1	|=	(0 << ICIE1) || (0 << OCIE1B) || (1 << OCIE1A) || (0 << TOIE1);	// Activamos interrupción por comparación del canal A
	
		OCR1A = 1563;	// Recordar que es de 16 bits (0-65535), con preescalador de 1024 a 16 MHz, el timer interrumpe cada 100 ms
	} else if (TIMER == 2)
	{
		PRR		&=~ (1 << PRTIM2);	// Aseguramos que el TIM se encuentre encendido
	
		TCCR2A	&=~	(1 << COM2A1) || (1 << COM2A0);	// El canal A lo dejamos en output mode normal
		TCCR2A	&=~ (1 << COM2B1) || (1 << COM2B0);	// El canal B lo dejamos en output mode normal
		TCCR2A	|=	(1 << WGM21) || (0 << WGM20);	// El timer lo usaremos en modo CTC
	
		TCCR2B	&=~	(1 << FOC2A) || (1 << FOC2B);	// No se forzará ningún canal
		TCCR2B	&=~	(0 << WGM22);	// Dejamos en 0 para que el modo siga siendo CTC
		TCCR2B	|=	(1 << CS22) || (1 << CS21) || (1 << CS20); // Preescalador de 1024
	
		TIMSK2	|=	(0 << OCIE2B) || (1 << OCIE2A) || (0 << TOIE2);	// Activamos interrupción por comparación del canal A
	
		OCR2A = 156;	// Recordar que es de 8 bits (0-255), con preescalador de 1024 a 16 MHz, el timer interrumpe cada 10 ms
	}
}

int main(void)
{
	cli();
	
	DDRD = 0xFF;
	
	TIM_init(1);
	
	sei();
	
    while (1) 
    {
    }
}

/************************************************************************/
/* FUNCIONES DE INTERRUPCION                                            */
/************************************************************************/
void TIMER0_COMPA_vect()
{
}

void TIMER0_COMPB_vect()
{
}

void TIMER1_COMPA_vect()
{
	if (PORTD & (1<<PORTD0)) PORTD &=~ (1 << PORTD0);
	else PORTD |= (1 << PORTD0);
}

void TIMER1_COMPB_vect()
{
}

void TIMER2_COMPA_vect()
{
}

void TIMER2_COMPB_vect()
{
}
