/*
 * define.c
 *
 *  Created on: 2018年5月7日
 *      Author: AIERXUAN
 */


#include "define.h"

int XStatus_bluetooth = 0;
int XStatus_heartbeat = 0;
int XStatus_display = 0;

//端口指针定义
XUartLite uart_bluetooth; //蓝牙
XUartPs uart_heartbeat; //心率监测板
XGpioPs gpio_display;//屏幕

//配置定义
XUartPs_Config *Config_uart;
XGpioPs_Config *Config_gpio;
