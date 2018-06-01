/*
 * define.h
 *
 *  Created on: 2018��5��7��
 *      Author: AIERXUAN
 */

#ifndef _DEFINE_H_
#define _DEFINE_H_

#include "xuartlite.h"
#include "xuartps.h"
#include "xgpiops.h"

//״̬����ֵ����
extern int XStatus_bluetooth;
extern int XStatus_heartbeat;
extern int XStatus_display;

//�˿�ָ�붨��
extern XUartLite uart_bluetooth; //����
extern XUartPs uart_heartbeat; //���ʼ���
extern XGpioPs gpio_display;//��Ļ

//���ö���
extern XUartPs_Config *Config_uart;
extern XGpioPs_Config *Config_gpio;

#endif /* DEFINE_H_ */
