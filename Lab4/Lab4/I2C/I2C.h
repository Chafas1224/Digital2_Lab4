/*
 * I2C.h
 *
 * Created: 18/02/2025 00:58:05
 *  Author: pablo
 */ 

#define F_CPU 16000000
#ifndef I2C_H_
#define I2C_H_
#include <avr/io.h>
#include <stdint.h>

//Funcion para inicializar I2C Maestro
void I2C_Master_Init (unsigned long SCL_Clock, uint8_t Prescaler);

//Funci�n de inicio de la comunicaci�n I2C
void I2C_Master_Start(void);

//Funci�n de parada de la comunicaci�n I2C
void I2C_Master_Stop(void);

//Funci�n de transmisi�n de datos del maestro al esclavo
uint8_t I2C_Master_Write(uint8_t dato);

//Funci�n de recepci�n de datos enviados por el esclavo al maestro
//Esta funci�n es para leer los datos que estan en el esclavo
uint8_t I2C_Master_Read(uint8_t *buffer, uint8_t ack);

//Funci�n para inicializar I2C Esclavo
void I2C_Slave_Init(uint8_t address);
#endif /* I2C_H_ */