/*
 * Lab4.c
 *
 * Created: 18/02/2025 00:57:35
 * Author : pablo
 */ 
// #define F_CPU 16000000
// #include <avr/io.h>
// #include <util/delay.h>
// #include <avr/interrupt.h>
// #include "I2C/I2C.h"
// #include "ADC/ADC.h"
// 
// #define slave1 0x30
// #define slave2 0x40
// 
// uint8_t direccion;
// uint8_t temp;
// uint8_t bufferI2C;
// uint8_t valorI2C;
// 
// void initPorts(void);
// void refreshPORT(uint8_t valor);
// 
// 
// int main(void)
// {
//     I2C_Master_Init(100000,1);
// 	initPorts();
//     while (1) 
//     {
// 		PORTB |=(1<<PORTB5);
// 		
// 		I2C_Master_Start();
// 		bufferI2C = slave1 << 1 & 0b11111110;
// 		
// 		temp = I2C_Master_Write(bufferI2C);
// 		if(temp != 1){
// 			I2C_Master_Stop();
// 		}else{
// 			I2C_Master_Write('R');
// 			I2C_Master_Stop();
// 		}
// 		_delay_ms(500);
// 		
// 		PORTB &=~(1<<PORTB5);
// 		I2C_Master_Start();
// 		//Lectura
// 		bufferI2C = slave1 << 1 | 0b00000001;
// 		
// 		temp = I2C_Master_Write(bufferI2C);
// 		if(temp != 1){
// 			I2C_Master_Stop();
// 		}else{
// 			TWCR = (1<<TWINT)|(1<<TWEN);
// 			while(!(TWCR & (1<<TWINT)));
// 			
// 			valorI2C = TWDR;
// 			I2C_Master_Stop();
// 		}
// 		
// 		
// 		refreshPORT(valorI2C);
// 		_delay_ms(500);
// 		
// 			
//     }
// }
// 
// void initPorts(void){
// 	//Salidas
// 	DDRC |= (1<< DDC0)|(1<< DDC1)|(1<< DDC2)|(1<< DDC3);
// 	DDRD |= (1<< DDD2)|(1<< DDD3)|(1<< DDD4)|(1<< DDD5);
// 	refreshPORT(0);
// 	DDRB |= (1<<DDB5);
// }
// 
// void refreshPORT(uint8_t valor){
// 	if(valor & 0b10000000){
// 		PORTD |= (1<<PORTD5);
// 	}else{
// 		PORTD &= ~(1<<PORTD5);
// 	}
// 	if(valor & 0b01000000){
// 		
// 	}
// }


// ------------------ESCLAVO-------------------------------------------------------
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "I2C/I2C.h"
#include "ADC/ADC.h"

#define SlaveAddress 0x30

uint8_t buffer = 0;
volatile uint8_t valorADC = 0;


int main(void)
{
// 	DDRB |= (1<<DDB5);
// 	PORTB &= ~(1<<PORTB5);
	initADC();
	iniciarADC(0);
	I2C_Slave_Init(SlaveAddress);
	sei(); //
	while (1)
	{
		//iniciarADC(0);
		valorADC = pot1;
		//_delay_ms(10);
	}
}


ISR(TWI_vect){
	uint8_t estado;
	estado = TWSR & 0xFC;
	switch(estado){
		case 0x60:
		case 0x70:
			TWCR |= (1<< TWINT);
			break;
		case 0x80:
		case 0x90:
			buffer = TWDR;
			TWCR |= (1<< TWINT);
			break;
		case 0xA8:
		case 0xB8:
			TWDR = valorADC;
			TWCR = (1 << TWEN)|(1<<TWIE)|(1<<TWINT)|(1<<TWEA);
			break;
		default:
 			TWCR |= (1<<TWINT)|(1<<TWSTO);
 		break;
 		}
 }