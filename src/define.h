/*
 * define.h
 *
 *  Created on: 2018年5月7日
 *      Author: AIERXUAN
 */

#ifndef _DEFINE_H_
#define _DEFINE_H_

#include "xuartlite.h"
#include "xuartps.h"
#include "xgpiops.h"

//状态反馈值定义
extern int XStatus_bluetooth;
extern int XStatus_heartbeat;
extern int XStatus_display;

//端口指针定义
extern XUartLite uart_bluetooth; //蓝牙
extern XUartPs uart_heartbeat; //心率监测板
extern XGpioPs gpio_display;//屏幕

//配置定义
extern XUartPs_Config *Config_uart;
extern XGpioPs_Config *Config_gpio;

#endif /* DEFINE_H_ */
