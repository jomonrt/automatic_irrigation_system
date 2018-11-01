/*
 * adc.h
 *
 * Created: 24-12-2016 10:27:57 PM
 *  Author: JOMON THOMAS
 */ 


#ifndef ADC_H_
#define ADC_H_

void adc_init(void);

void start_adc_conversion_automatic(void);

int get_adc_value(void);

int start_conversion_mannual(void);

#endif /* ADC_H_ */