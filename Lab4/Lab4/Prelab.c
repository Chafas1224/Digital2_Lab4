/*
 * D2-LAB-04-ESCLAVO_CONTADOR.c
 *
 * Created: 2/23/2025 10:53:36 PM
 * Author : samue
 */ 


#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "I2C/I2C.h"

#define SlaveAddress 0x29
uint8_t buffer = 0;
uint8_t contador = 0;

void setup(){
	cli();
	DDRD |= 0x0F;
	DDRB &= ~((1 << PB0) | (1 << PB1));
	PORTB |= (1 << PB0) | (1 << PB1);
	 UCSR0B &= ~((1 << TXEN0) | (1 << RXEN0)); // Deshabilitar TX y RX
	 //DDRD &= ~((1 << PD0) | (1 << PD1)); // Configurar PD0 y PD1 como entrada
	 //PORTD &= ~((1 << PD0) | (1 << PD1)); // Desactivar pull-ups en PD0 y PD1
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT0) | (1 << PCINT1);
	I2C_Slave_Init(SlaveAddress);
	sei();
}


int main(void)
{
	
	setup();
    /* Replace with your application code */
    while (1) 
    {
		
    }
}


ISR(PCINT0_vect){
	 if (!(PINB & (1 << PB0))) { // Botón de incremento
		 _delay_ms(10); // Antirrebote
		 if (!(PINB & (1 << PB0))) {
			 if (contador < 15) 
			 contador++;
			 PORTD = contador;
		 }
	 }
	 if (!(PINB & (1 << PB1))) { // Botón de decremento
		 _delay_ms(10); // Antirrebote
		 if (!(PINB & (1 << PB1))) {
			 if (contador > 0) 
			 contador--;
			 PORTD = contador;
		 }
	 }
}

ISR(TWI_vect) {
	uint8_t estado = TWSR & 0xFC;
	switch (estado) {
		case 0xA8: // Dirección reconocida con solicitud de lectura
		case 0xB8: // Maestro sigue leyendo
		TWDR = contador; // Enviar el valor actual del contador
		TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWINT) | (1 << TWEA);
		break;
		default:
		TWCR |= (1 << TWINT) | (1 << TWSTO);
		break;
	}
}
