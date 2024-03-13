/*
 * rtc.c
 *
 *  Created on: May 1, 2023
 *      Author: arsla
 */


#include "rtc.h"
void __gettimeanddatefromrtc(){

	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef DateToUpdate = {0};

	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);

	_timeanddate.hours = sTime.Hours;
	_timeanddate.min = sTime.Minutes;
	_timeanddate.sec = sTime.Seconds;


	_timeanddate.date = DateToUpdate.Date;
	_timeanddate.month = DateToUpdate.Month;
	_timeanddate.year = DateToUpdate.Year;

}

void get_time(void)
{
 RTC_DateTypeDef gDate;
 RTC_TimeTypeDef gTime;
 unsigned char time_=0,date=0;
/* Get the RTC current Time */
 HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
/* Get the RTC current Date */
 HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
/* Display time Format: hh:mm:ss */
// sprintf(time_,"%02d:%02d:%02d",gTime.Hours, gTime.Minutes, gTime.Seconds);
///* Display date Format: dd-mm-yy */
// sprintf(date,"%02d-%02d-%2d ",gDate.Date, gDate.Month, gDate.Year);
// memcpy(RTCBuff,date,9);
// strcat(RTCBuff,time_);

// Serial_str_ln(RTCBuff);
 Serial_int(gDate.Year);
 Serial_str("-");
 Serial_int(gDate.Month);
 Serial_str("-");
 Serial_int(gDate.Date);
 Serial_str(" ");
 Serial_int(gTime.Hours);
 Serial_str(":");
 Serial_int(gTime.Minutes);
 Serial_str(":");
 Serial_int_ln(gTime.Seconds);
}

void __showtimeanddatefromrtc(void){
	debugu4pc10("hours: ");
	debugu4pc10_int(_timeanddate.hours);
	debugu4pc10("min: ");
	debugu4pc10_int(_timeanddate.min);
	debugu4pc10("sec: ");
	debugu4pc10_int(_timeanddate.sec);
	debugu4pc10("date: ");
	debugu4pc10_int(_timeanddate.date);
	debugu4pc10("Month: ");
	debugu4pc10_int(_timeanddate.month);
	debugu4pc10("Year: ");
	debugu4pc10_int(_timeanddate.year);
	//	  debugu4pc10("month Initiated: ");
	//	  debugu4pc10_float(_timeanddate.month);
}


void __synchroniseRTCBuff(unsigned char *rtcbuff_, int way){ //if way=1 this ftn will set the RTC time from the RTC buffer taken from the internet
	//if way=0 this ftn will set the RTC buffer from the RTC time taken from the microcontroller
	if (way==1){
		char YY_s[2] = {0,0,0,0,0}, MM_s[2] = {0,0}, DD_s[2] = {0,0}, hh_s[2] = {0,0}, *mm_s[2] = {0,0}, *ss_s[2] = {0,0};
		uint8_t YY = 0, MM = 0, DD = 0, hh = 0, mm = 0, ss = 0;
		 int YY_hex, MM_hex, DD_hex, hh_hex, mm_hex, ss_hex;
		memcpy(hh_s, rtcbuff_ + 9, 2);
		memcpy(mm_s, rtcbuff_ + 12, 2);
		memcpy(ss_s, rtcbuff_ + 15, 2);
		memcpy(YY_s, rtcbuff_ + 0, 2);
		memcpy(MM_s, rtcbuff_ + 3, 2);
		memcpy(DD_s, rtcbuff_ + 6, 2);
        Serial_str_ln("");
        Serial_str("date: ");
        Serial_str(YY_s);
        Serial_str(MM_s);
        Serial_str(DD_s);
        Serial_str("time: ");
        Serial_str(hh_s);
        Serial_str(mm_s);
        Serial_str_ln(ss_s);
		hh = atoi(hh_s);
		mm = atoi(mm_s);
		ss = atoi(ss_s);
		YY = atoi(YY_s);
		MM = atoi(MM_s);
		DD = atoi(DD_s);
//		Serial_int(hh);
//		Serial_int(mm);
//		Serial_int(ss);
//		Serial_int(YY);
//		Serial_int(MM);
//		Serial_int(DD);

		RTC_TimeTypeDef sTime = {0};
		RTC_DateTypeDef DateToUpdate = {0};
		sTime.Hours = hh;
		sTime.Minutes = mm;
		sTime.Seconds = ss;
		if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
		{
			Error_Handler();
		}
		DateToUpdate.Month = (uint8_t *)MM;
		DateToUpdate.Date = (uint8_t *)DD;
		DateToUpdate.Year = (uint8_t *)YY;
		unsigned char temp[20] = {0};

//		sprintf(temp, "%.2d", DateToUpdate.Year);
//		__writeDBGStringUart1(temp);
		if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
		{
			Error_Handler();
		}
//		__showtimeanddatefromrtc();
	}
	else if (way==0){
		__gettimeanddatefromrtc();
		unsigned char temp[20] = {0};
		sprintf(temp, "%.2d", _timeanddate.year);
//		Serial_str(temp);
		memcpy(RTCBuff + 0, temp, 2);
		sprintf(temp, "%.2d", _timeanddate.month);
//		Serial_str(temp);
		memcpy(RTCBuff + 3, temp, 2);
		sprintf(temp, "%.2d", _timeanddate.date);
//		Serial_str(temp);
		memcpy(RTCBuff + 6, temp, 2);

		sprintf(temp, "%.2d", _timeanddate.hours);
//		Serial_str(temp);
		memcpy(RTCBuff + 9, temp, 2);
		sprintf(temp, "%.2d", _timeanddate.min);
//		Serial_str(temp);
		memcpy(RTCBuff + 12, temp, 2);
		sprintf(temp, "%.2d", _timeanddate.sec);
//		Serial_str(temp);
		memcpy(RTCBuff + 15, temp, 2);

	}
}

void DecimalToHexadecimal(int decimal, int hexaDecimal)
{
	int reminder;
	while(decimal!=0)
	{
		reminder = decimal%16;
		if(reminder<10)
			reminder = reminder+48;
		else
			reminder = reminder+55;
		hexaDecimal = reminder;
		decimal = decimal/16;
	}
}
