/*
 * main.c
 *
 *  Created on: 2018Äê4ÔÂ30ÈÕ
 *      Author: AIERXUAN
 */

#include "main.h"
#include "string.h"

#define UARTLITE_DEVICE_ID	XPAR_UARTLITE_0_DEVICE_ID
#define BUFFER_SIZE 6
#define GROUPS 100
#define DELAY 5000
int main(){

	Config_uart = XUartPs_LookupConfig(XPAR_PS7_UART_0_DEVICE_ID);
	Config_gpio = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);

	XStatus_bluetooth = XUartLite_Initialize (&uart_bluetooth, XPAR_AXI_UARTLITE_0_DEVICE_ID);
	XStatus_heartbeat = XUartPs_CfgInitialize (&uart_heartbeat, Config_uart, Config_uart->BaseAddress);
	XStatus_display = XGpioPs_CfgInitialize (&gpio_display,Config_gpio,Config_gpio->BaseAddr);

	XUartPs_SetBaudRate(&uart_heartbeat,XUARTPS_DFT_BAUDRATE);

	OLED_Init();

Loop:
	OLED_Clear();
	OLED_ShowCHinese(0,2,0);//您
	OLED_ShowCHinese(18,2,1);//好
	OLED_ShowString(36,2,"!");//!
	OLED_ShowCHinese(0,4,2);//欢
	OLED_ShowCHinese(18,4,3);//迎
	OLED_ShowCHinese(36,4,4);//使
	OLED_ShowCHinese(54,4,5);//用
	OLED_ShowCHinese(72,4,6);//本
	OLED_ShowCHinese(90,4,7);//产
	OLED_ShowCHinese(108,4,8);//品
	sleep(3);

	u8 data_buffer[BUFFER_SIZE] = {};
	u8 control_buffer[BUFFER_SIZE] = {0xfd,0x0,0x0,0x0,0x0,0x0};
	u8 ppg_buffer[BUFFER_SIZE] = {0xfc,0x0,0x0,0x0,0x0,0x0};
	u8 ecg_buffer[BUFFER_SIZE] = {0xf9,0x0,0x0,0x0,0x0,0x0};


	int count = 0;
	u32 high = 0;
	u32 low = 0;
	u32 heart_beat = 0;
	while(1)
	{
		//接收上位机开始信号:06 05 04 03 02 01
		while(1){
			XUartLite_Recv(&uart_bluetooth,&data_buffer[0],6);
			usleep(500000);
			int flag = 1;
			int i = 6;

			for(i = 6;i > 0;i--){
				if(data_buffer[6 - i] != i){
					flag = 0;
					break;
				}
			}

			if(flag)
				break;
		}

		//开始测试
		OLED_Clear();

		OLED_ShowCHinese(0,2,13);//正
		OLED_ShowCHinese(18,2,14);//在
		OLED_ShowCHinese(36,2,15);//检
		OLED_ShowCHinese(54,2,16);//测
		OLED_ShowCHinese(72,2,17);//请
		OLED_ShowCHinese(90,2,18);//稍
		OLED_ShowCHinese(108,2,19);//候

		OLED_ShowCHinese(0,4,16);//测
		OLED_ShowCHinese(18,4,26);//试
		OLED_ShowCHinese(36,4,27);//时
		OLED_ShowCHinese(54,4,28);//间
		OLED_ShowCHinese(72,4,29);//约
		OLED_ShowNum(90,4,30,2,16);//30
		OLED_ShowCHinese(108,4,30);//秒

		sleep(1);
		//心率开始接受心率监测内容
		while(1){
			//心率工作
			XUartPs_Send(&uart_heartbeat,&control_buffer[0],BUFFER_SIZE);
			usleep(DELAY);
			XUartPs_Recv(&uart_heartbeat,data_buffer,BUFFER_SIZE);
			usleep(DELAY);

			//检测数据是否有效
			if(data_buffer[1] >=100 && data_buffer[1] <= 160 && data_buffer[2] >=50 && data_buffer[2]<=100 &&data_buffer[3]>=50 &&data_buffer[3] <=100)
				count++;
			else continue;

			//发送心率、血压数据
			XUartLite_Send(&uart_bluetooth, &data_buffer,BUFFER_SIZE);
			usleep(DELAY);

			//计算心率、血压
			high += data_buffer[1];
			low += data_buffer[2];
			heart_beat += data_buffer[3];

//			ECG由于设备问题无法实现
//			//检测并发送ecg
//			XUartPs_Send(&uart_heartbeat,&ecg_buffer[0],BUFFER_SIZE);
//			usleep(DELAY );
//			XUartPs_Recv(&uart_heartbeat,data_buffer,BUFFER_SIZE);
//			usleep(DELAY);
//			XUartLite_Send(&uart_bluetooth, &data_buffer,BUFFER_SIZE);
//			usleep(DELAY);

			//检测并发送ppg
			XUartPs_Send(&uart_heartbeat,&ppg_buffer[0],BUFFER_SIZE);
			usleep(DELAY);
			XUartPs_Recv(&uart_heartbeat,data_buffer,BUFFER_SIZE);
			usleep(DELAY);
			XUartLite_Send(&uart_bluetooth, &data_buffer,BUFFER_SIZE);
			usleep(DELAY);

			//显示反馈数据
			if(count >= GROUPS){
				break;
			}
		}

		OLED_Clear();
		OLED_ShowCHinese(18,2,22);//收
		OLED_ShowCHinese(36,2,23);//缩
		OLED_ShowCHinese(54,2,12);//压
		OLED_ShowString(72,2,":");//：
		OLED_ShowNum(90,2,high/GROUPS,3,16);

		OLED_ShowCHinese(18,4,24);//舒
		OLED_ShowCHinese(36,4,25);//张
		OLED_ShowCHinese(54,4,12);//压
		OLED_ShowString(72,4,":");//：
		OLED_ShowNum(90,4,low/GROUPS,2,16);

		OLED_ShowCHinese(18,6,9);//心
		OLED_ShowCHinese(36,6,10);//率
		OLED_ShowString(54,6,":");//：
		OLED_ShowNum(72,6,heart_beat/GROUPS,2,16);
		sleep(10);
		goto Loop;
	}
}

