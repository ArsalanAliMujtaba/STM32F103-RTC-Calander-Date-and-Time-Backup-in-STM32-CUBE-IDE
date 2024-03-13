/*
 * rtc_modified.h
 *
 *  Created on: Mar 13, 2024
 *      Author: Arsalan Ali Mujtaba
 */

#ifndef INC_RTC_MODIFIED_H_
#define INC_RTC_MODIFIED_H_

#include "main.h"




uint32_t epochtime_;



typedef struct  {
  uint16_t numberOfDays;
  uint16_t year;
  int16_t  month;
  int16_t  day;
  uint8_t  weekday;
  int     isLeapYear;
}DateVar;
DateVar date_var;

typedef struct  {
  int16_t  hours;
  int16_t  minutes;
  int16_t  seconds;
}TimeVar;
TimeVar time_var;


enum Weekday {
  SUNDAY,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY
};

enum MonthIndex {
  JANUARY,
  FEBRUARY,
  MARCH,
  APRIL,
  MAY,
  JUNE,
  JULY,
  AUGUST,
  SEPTEMBER,
  OCTOBER,
  NOVEMBER,
  DECEMBER
};


//struct DateTime {
//  DateVar date;
//  TimeVar time;
//};


//struct  rtc_reg_map{
//  uint32_t CRH;
//  uint32_t CRL;
//  uint32_t PRLH;
//  uint32_t PRLL;
//  uint32_t DIVH;
//  uint32_t DIVL;
//  uint32_t CNTH;
//  uint32_t CNTL;
//  uint32_t ALRH;
//  uint32_t ALRL;
//};

//#define RTC_BASE ((volatile rtc_reg_map*)0x40002800)


#define RTC_CRH_OWIE_BIT  2
#define RTC_CRH_ALRIE_BIT 1
#define RTC_CRH_SECIE_BIT 0

#define RTC_CRH_OWIE  BIT(RTC_CRH_OWIE_BIT)
#define RTC_CRH_ALRIE BIT(RTC_CRH_ALRIE_BIT)
#define RTC_CRH_SECIE BIT(RTC_CRH_SECIE_BIT)


#define RTC_CRH  RTC_BASE->CRH
#define RTC_CRL  RTC_BASE->CRL
#define RTC_PRLH RTC_BASE->PRLH
#define RTC_PRLL RTC_BASE->PRLL
#define RTC_DIVH RTC_BASE->DIVH
#define RTC_DIVL RTC_BASE->DIVL
#define RTC_CNTH RTC_BASE->CNTH
#define RTC_CNTL RTC_BASE->CNTL
#define RTC_ALRH RTC_BASE->ALRH
#define RTC_ALRL RTC_BASE->ALRL

#define RCC_APB1ENR RCC->APB1ENR
#define RCC_BDCR    RCC->BDCR
#define PWR_CR      PWR->CR
#define NVIC_ISER   NVIC_BASE->ISER
#define NVIC_ICER   NVIC_BASE->ICER
#define EXTI_IMR    EXTI_BASE->IMR
#define EXTI_RTSR   EXTI_BASE->RTSR


#ifndef HAL_RTC_MODULE_ENABLED
#error "RTC configuration is missing. Check flag HAL_RTC_MODULE_ENABLED in stm32f1xx_hal_conf_default.h"
#endif

#define RTC_CRH  RTC->CRH
#define RTC_CRL  RTC->CRL
#define RTC_PRLH RTC->PRLH
#define RTC_PRLL RTC->PRLL
#define RTC_DIVH RTC->DIVH
#define RTC_DIVL RTC->DIVL
#define RTC_CNTH RTC->CNTH
#define RTC_CNTL RTC->CNTL
#define RTC_ALRH RTC->ALRH
#define RTC_ALRL RTC->ALRL


#endif

#define BKP_DR        (((volatile uint32_t*)0x40006C00))
#define RTC_INIT_REG  1
#define RTC_INIT_BIT  0
#define RTC_INIT_FLAG (1 << RTC_INIT_BIT)
#define MOON_CYCLE    29.5305882
#define HIJRI_DIFF    21.252353


  uint16_t getNumberOfDaysUntilMonth(int16_t monthIndex, int isLeapYear);
  uint16_t getSumOfDayFromYearValue(uint16_t year);





  int rtc_begin();
  void rtc_init();
  void rtc_setTime(uint32_t time);
  uint32_t rtc_getTime();
  uint16_t rtc_getMilliseconds();
  uint16_t rtc_getBackupRegister(uint8_t idx);
  int rtc_setBackupRegister(uint8_t idx, uint16_t val);

  void rtc_epochToDate(uint32_t time);
  void rtc_epochToTime(uint32_t time);
  uint32_t rtc_dateTimeToEpoch(void);
  uint16_t rtc_getNumberOfDaysUntilMonth(int16_t monthIndex, int isLeapYear);
  uint16_t rtc_getSumOfDayFromYearValue(uint16_t year);





  void rtc_set_date_time(char*);

  int rtc_get_date_and_time(void);

  void rtc_print3Digits(uint16_t n);
  void rtc_print2Digits(uint8_t n);
  void rtc_printtime_(int ms);
  void rtc_printDate();
