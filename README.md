rtc_begin(); // must be used in begining to get started with rtc init for calander and time storage

RTCBuff // this is the buffer which holds the time outside rtc to be used. The date and time is in this format: 24-03-13 12:30:10 (YY-MM-DD hh:mm:ss)

rtc_set_date_time(RTCBuff); // this function is used to update the rtc date and time using the RTCBuff.

rtc_get_date_and_time(); // This function will update the RTCBuff array after reading date and time from the internal rtc of stm32f103 MCU
