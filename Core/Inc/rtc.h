/*
 * rtc.h
 *
 *  Created on: May 1, 2023
 *      Author: arsla
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "main.h"

void __gettimeanddatefromrtc();
void __synchroniseRTCBuff(unsigned char *, int);
void get_time(void);
void __showtimeanddatefromrtc(void);
void DecimalToHexadecimal(int decimal, int hexaDecimal);

#endif /* INC_RTC_H_ */
