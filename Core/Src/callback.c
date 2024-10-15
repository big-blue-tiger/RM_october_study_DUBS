#include "main.h"
#include "usart.h"
//
// Created by 28672 on 24-10-15.
//
uint8_t Recieve_buffer[18];
uint8_t Recieve_data[18];
float x_r = 0;
int x_r_in;
float linear_mapping(int be0,int ed0,float be1,float ed1,int val)
{
    return be1 + (ed1-be1)*(float)(val-be0)/(float)(ed0-be0);
}
void buffer_analysis()
{
    x_r_in = ((int)(Recieve_buffer[1] & 0x07)<<8) | ((int)Recieve_buffer[0]);
    x_r = linear_mapping(364,1684,-1.0,1.0,x_r_in);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
    for(int i = 0; i < 18; i++)
        Recieve_buffer[i] = Recieve_data[i];
		buffer_analysis();
    HAL_UART_Receive_DMA(&huart1, Recieve_data, 18);
}