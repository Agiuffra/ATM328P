/*
 * ADC.c
 *
 * Created: 21/12/2021 23:18:52
 * Author : Usuario
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/************************************************************************/
/* Inicializacion del ADC                                               */
/************************************************************************/
void ADC_init()
{
	//- En que orden almacena los bits resultantes (derecha)
	ADMUX	&=~	(1<<ADLAR);
	
	//- Referencia de voltaje (Alimentacion = 5 VDC)
	ADMUX	|=	(1<<REFS0);
	ADMUX	&=~ (1<<REFS1);
	
	//- Preescalador: frecuencia de muestreo (Fs = F_CPU/128 = 125 kHz)
	ADCSRA	|=	(1<<ADPS0);
	ADCSRA	|=	(1<<ADPS1);
	ADCSRA	|=	(1<<ADPS2);
	
	//- Todos los canales ADC estan como input
	DDRC	=   (0<<DDC0)|(0<<DDC1)|(0<<DDC2)|(0<<DDC3)|(0<<DDC4)|(0<<DDC5);
}

/************************************************************************/
/* Pedir datos del ADC                                                  */
/************************************************************************/
uint16_t ADC_GetData(uint8_t canal)
{
	//- Seleccion del canal a leer
	ADMUX	&=~ 0x0F;
	ADMUX	|=  canal;
	
	//- Se enciende el ADC
	ADCSRA	|=	(1<<ADEN);
	_delay_us(10);
	
	//- Inicia la lectura
	ADCSRA	|=  (1<<ADSC);
	
	//- Espera a que finalice la toma de datos
	while(!(ADCSRA & (1<<ADIF)));
	
	//- Borramos bandera de interrupcion
	ADCSRA	|=	(1<<ADIF);
	
	//- Se apaga el ADC
	ADCSRA	&=~	(1<<ADEN);
	
	//- Se retorna el valor medido
	return ADC;
}

int main(void)
{	
	cli();
	ADC_init();
	sei();
	
    while (1) 
    {
		uint16_t data = ADC_GetData(0);
		
		_delay_us(100);
    }
}

