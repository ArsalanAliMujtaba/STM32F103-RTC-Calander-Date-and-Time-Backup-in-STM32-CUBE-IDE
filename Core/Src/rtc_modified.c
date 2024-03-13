/*
 * rtc_modified.c
 *
 *  Created on: Mar 13, 2024
 *      Author: Arsalan Ali Mujtaba
 */


#include "rtc_modified.h"




uint16_t numberOfDaysUntilMonth[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };


  void rtc_set_date_time(char *rtc_buffer)
  {

	  char temp_1[4];
	  char temp[4];

	  memcpy(temp,"20",2);
	  memcpy(temp_1,rtc_buffer,2);
	  strcat(temp,temp_1);
	  date_var.year = atoi(temp);

	  memset(temp,0,4);
	  memcpy(temp,rtc_buffer+3,2);
	  date_var.month = atoi(temp);

	  memset(temp,0,4);
	  memcpy(temp,rtc_buffer+6,2);
	  date_var.day = atoi(temp);

	  memset(temp,0,4);
	  memcpy(temp,rtc_buffer+9,2);
	  time_var.hours = atoi(temp);

	  memset(temp,0,4);
	  memcpy(temp,rtc_buffer+12,2);
	  time_var.minutes = atoi(temp);

	  memset(temp,0,4);
	  memcpy(temp,rtc_buffer+15,2);
	  time_var.seconds = atoi(temp);
	  rtc_setTime(rtc_dateTimeToEpoch());
  }

  int rtc_get_date_and_time(void)
  {

	  memset(RTCBuff,0,sizeof(RTCBuff));
	  epochtime_ = rtc_getTime();
	  rtc_epochToTime(epochtime_);
	  rtc_epochToDate(epochtime_);
	  char temp[10];
	  sprintf(temp, "%d", date_var.year);
	  memcpy(RTCBuff,temp+2,2);
	  strcat(RTCBuff,"-");

	  memset(temp,0,sizeof(temp));
	  sprintf(temp, "%d", date_var.month);
	  if(date_var.month < 10)
	  {
		  strcat(RTCBuff,"0");
	  }
	  strcat(RTCBuff,temp);


	  strcat(RTCBuff,"-");

	  memset(temp,0,sizeof(temp));
	  sprintf(temp, "%d", date_var.day);
	  if(date_var.day < 10)
	  {
		  strcat(RTCBuff,"0");
	  }
	  strcat(RTCBuff,temp);

	  strcat(RTCBuff," ");

	  memset(temp,0,sizeof(temp));
	  sprintf(temp, "%d", time_var.hours);
	  if(time_var.hours < 10)
	  {
		  strcat(RTCBuff,"0");
	  }
	  strcat(RTCBuff,temp);

	  strcat(RTCBuff,":");

	  memset(temp,0,sizeof(temp));
	  sprintf(temp, "%d", time_var.minutes);
	  if(time_var.minutes < 10)
	  {
		  strcat(RTCBuff,"0");
	  }
	  strcat(RTCBuff,temp);

	  strcat(RTCBuff,":");

	  memset(temp,0,sizeof(temp));
	  sprintf(temp, "%d", time_var.seconds);
	  if(time_var.seconds < 10)
	  {
		  strcat(RTCBuff,"0");
	  }
	  strcat(RTCBuff,temp);

	  Serial_str_ln(RTCBuff);
//	  rtc_printDate();
//	  rtc_printtime_(1);
  }

  void rtc_printDate() {
  	Serial_int(date_var.year);
    Serial_str("-");
    rtc_print2Digits(date_var.month);
    Serial_str("-");
    rtc_print2Digits(date_var.day);
    Serial_str(" ");
  }

  void rtc_printtime_(int ms) {
    uint8_t h = time_var.hours;

    rtc_print2Digits(h);
    Serial_str(":");
    rtc_print2Digits(time_var.minutes);
    Serial_str(":");
    rtc_print2Digits(time_var.seconds);

    Serial_str_ln("");
  }

  void rtc_print2Digits(uint8_t n) {
    if (n < 10)
  	  Serial_int(0);
    Serial_int(n);
  }

  void rtc_print3Digits(uint16_t n) {
    if (n < 100) {
      Serial_int(0);
      print2Digits(n);
    }
    else
      Serial_int(n);
  }




int rtc_begin()
{
  int isInit = (BKP_DR[RTC_INIT_REG] & RTC_INIT_FLAG) == RTC_INIT_FLAG;
  RCC_APB1ENR |= RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN;
  if (isInit)
  {
	    RTC_CRL &= ~RTC_CRL_RSF;
	    while ((RTC_CRL & RTC_CRL_RSF) == 0);
  }
  else
  {
	  rtc_init();
  }
  return isInit;
}

void rtc_init()
{
  PWR_CR |= PWR_CR_DBP;
  RCC_BDCR |= RCC_BDCR_BDRST; // Resets the entire Backup domain
  RCC_BDCR &= ~RCC_BDCR_BDRST; // Deactivates reset of entire Backup domain
  RCC_BDCR |= RCC_BDCR_LSEON; // Enables external low-speed oscillator (LSE)
  while ((RCC_BDCR & RCC_BDCR_LSERDY) == 0); // Waits for LSE ready
  RCC_BDCR |= RCC_BDCR_RTCSEL_LSE; // Selects LSE as RTC clock
  RCC_BDCR |= RCC_BDCR_RTCEN; // Enables the RTC

  RTC_CRL &= ~RTC_CRL_RSF;
  while ((RTC_CRL & RTC_CRL_RSF) == 0);

  while ((RTC_CRL & RTC_CRL_RTOFF) == 0);
  RTC_CRL |= RTC_CRL_CNF;
  RTC_PRLL = 0x7FFF;
  RTC_CRL &= ~RTC_CRL_CNF;
  while ((RTC_CRL & RTC_CRL_RTOFF) == 0);
  BKP_DR[RTC_INIT_REG] |= RTC_INIT_FLAG; // Signals that RTC initilized
  PWR_CR &= ~PWR_CR_DBP;
}


void rtc_setTime(uint32_t time)
{
  PWR_CR |= PWR_CR_DBP;
  while ((RTC_CRL & RTC_CRL_RTOFF) == 0);
  RTC_CRL |= RTC_CRL_CNF;
  RTC_CNTH = time >> 16;
  RTC_CNTL = time & 0xFFFF;
  RTC_CRL &= ~RTC_CRL_CNF;
  while ((RTC_CRL & RTC_CRL_RTOFF) == 0);
  PWR_CR &= ~PWR_CR_DBP;
}

// The 32-bit RTC counter is spread over 2 registers so it cannot be read
// atomically. We need to read the high word twice and check if it has rolled
// over. If it has, then read the low word a second time to get its new, rolled
// over value. See the RTC_ReadTimeCounter() function in
// system/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rtc.c of the
// STM32duino Core.
uint32_t rtc_getTime()
{
  uint16_t high1 = RTC_CNTH;
  uint16_t low = RTC_CNTL;
  uint16_t high2 = RTC_CNTH;

  if (high1 != high2) {
    low = RTC_CNTL;
    high1 = high2;
  }

  return (high1 << 16) | low;
}


uint16_t rtc_getMilliseconds()
{
  uint32_t ms = (RTC_DIVH << 16) | RTC_DIVL;
  return (uint16_t)((float)(32767 - ms) / 32768.0 * 1000.0);
}

uint16_t rtc_getBackupRegister(uint8_t idx) {
#if (BKP_NR_DATA_REGS == 42) || defined(BKP_DR42_D)
  if (idx > 10)
    idx += 5;
  if (1 <= idx && idx <= 47)
#else
  if (1 <= idx && idx <= 10)
#endif
    return BKP_DR[idx];
  else
    return 0;
}

int rtc_setBackupRegister(uint8_t idx, uint16_t val) {
#if (BKP_NR_DATA_REGS == 42) || defined(BKP_DR42_D)
  if (idx > 10)
    idx += 5;
  if (1 <= idx && idx <= 47)
#else
  if (1 <= idx && idx <= 10)
#endif
  {
    PWR_CR |= PWR_CR_DBP;
    BKP_DR[idx] = val;
    PWR_CR &= ~PWR_CR_DBP;
    return 1;
  }
  else
    return 0;
}

void rtc_epochToDate(uint32_t time)
{
  uint16_t sod, dom;
  date_var.numberOfDays = time / 86400;
  date_var.year = date_var.numberOfDays / 365 + 1970;
  sod = rtc_getSumOfDayFromYearValue(date_var.year);
  if (sod > date_var.numberOfDays)
    sod = rtc_getSumOfDayFromYearValue(--date_var.year);
  date_var.isLeapYear = ((date_var.year - 1968) % 4) == 0 && date_var.year != 2100;
  sod = date_var.numberOfDays - sod;
  for (int8_t i = DECEMBER; i >= JANUARY; i--) {
    dom = rtc_getNumberOfDaysUntilMonth(i, date_var.isLeapYear);
    if (dom <= sod) {
      date_var.day = sod - dom + 1;
      date_var.month = i + 1;
      break;
    }
  }
  date_var.weekday = (date_var.numberOfDays + 4) % 7;
}

void rtc_epochToTime(uint32_t time)
{
  uint32_t tm = time % 86400;
  time_var.hours = tm / 3600;
  tm %= 3600;
  time_var.minutes = tm / 60;
  time_var.seconds = tm % 60;
}

uint32_t rtc_dateTimeToEpoch(void)
{
  uint32_t time;
  if (date_var.month > 0) {
	  date_var.year += (date_var.month - 1) / 12;
	  date_var.month = (date_var.month - 1) % 12 + 1;
  }
  else {
	  date_var.year -= 1 - date_var.month / 12;
	  date_var.month = 12 + date_var.month % 12;
  }
  if (date_var.year < 1970)
	  date_var.year = 1970;
  else if (date_var.year > 2105)
	  date_var.year = 2105;
  date_var.isLeapYear = ((date_var.year - 1968) % 4) == 0 && date_var.year != 2100;
  date_var.numberOfDays = rtc_getSumOfDayFromYearValue(date_var.year) + rtc_getNumberOfDaysUntilMonth(date_var.month - 1, date_var.isLeapYear) + date_var.day - 1;
  time = date_var.numberOfDays * 86400 + time_var.hours * 3600 + time_var.minutes * 60 + time_var.seconds;
  rtc_epochToDate(time);
  rtc_epochToTime(time);
  return time;
}


uint16_t rtc_getNumberOfDaysUntilMonth(int16_t monthIndex, int isLeapYear)
{
  uint16_t n = numberOfDaysUntilMonth[monthIndex];
  if (isLeapYear && monthIndex > FEBRUARY)
    n++;
  return n;
}

uint16_t rtc_getSumOfDayFromYearValue(uint16_t year)
{
  float fsod = (float)(year - 1970) * 365.25 + 0.25;
  if (year > 2100)
    fsod -= 0.5;
  return (uint16_t)fsod;
}


#ifdef __cplusplus
}
#endif
