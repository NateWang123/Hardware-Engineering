/*
 * define.c
 *
 *  Created on: 2018��5��7��
 *      Author: AIERXUAN
 */


#include "define.h"

int XStatus_bluetooth = 0;
int XStatus_heartbeat = 0;
int XStatus_display = 0;

//�˿�ָ�붨��
XUartLite uart_bluetooth; //����
XUartPs uart_heartbeat; //���ʼ���
XGpioPs gpio_display;//��Ļ

//���ö���
XUartPs_Config *Config_uart;
XGpioPs_Config *Config_gpio;
