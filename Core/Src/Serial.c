/*
 * Serial.c
 *
 *  Created on: Feb 8, 2023
 *      Author: Arsalan Ali Mujtaba
 */



#include "Serial.h"

void Serial_str(char *holder){
		  int sizeofholder=strlen(holder);
		  HAL_UART_Transmit(&huart1,holder,sizeofholder,2000);
	  }
void Serial_int(int holder){
    unsigned char temp[20] = {0};
    sprintf(temp, "%d", holder);
    int sizeofholder=strlen(temp);
    HAL_UART_Transmit(&huart1,temp,sizeofholder,2000);
}

void Serial_float(float holder){
    unsigned char temp[20] = {0};
    sprintf(temp, "%lf", holder);
    int sizeofholder=strlen(temp);
    HAL_UART_Transmit(&huart1,temp,sizeofholder,2000);
}


void Serial_str_ln(char *holder){
		  int sizeofholder=strlen(holder);
		  HAL_UART_Transmit(&huart1,holder,sizeofholder,2000);
		  HAL_UART_Transmit(&huart1,"\n",strlen("\n"),2000);
	  }
void Serial_int_ln(int holder){
    unsigned char temp[20] = {0};
    sprintf(temp, "%d", holder);
    int sizeofholder=strlen(temp);
    HAL_UART_Transmit(&huart1,temp,sizeofholder,2000);
	  HAL_UART_Transmit(&huart1,"\n",strlen("\n"),2000);
}
void Serial_float_ln(float holder){
    unsigned char temp[20] = {0};
    sprintf(temp, "%lf", holder);
    int sizeofholder=strlen(temp);
    HAL_UART_Transmit(&huart1,temp,sizeofholder,2000);
	HAL_UART_Transmit(&huart1,"\n",strlen("\n"),2000);
}

