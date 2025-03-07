/*
 * ADC.h
 *
 * Created: 11/02/2025 17:02:07
 *  Author: pablo
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

extern volatile uint8_t canal_adc;
extern volatile uint8_t pot1, pot2;

void initADC(void);
void iniciarADC(uint8_t canal);

#endif /* ADC_H_ */
