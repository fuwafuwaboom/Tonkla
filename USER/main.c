
#include "system.h"

//Task priority    
#define START_TASK_PRIO	1

//Task stack size 	
#define START_STK_SIZE 	256  

//Task handle     /
TaskHandle_t StartTask_Handler;

//Task function   
void start_task(void *pvParameters);

//Main function 
int main(void)
{ 
  systemInit(); //Hardware initialization 
	
	//Create the start task /
	xTaskCreate((TaskFunction_t )start_task,            //Task function   
							(const char*    )"start_task",          //Task name       
							(uint16_t       )START_STK_SIZE,        //Task stack size 
							(void*          )NULL,                  //Arguments passed to the task function 
							(UBaseType_t    )START_TASK_PRIO,       //Task priority   
							(TaskHandle_t*  )&StartTask_Handler);   //Task handle         					
	vTaskStartScheduler();  //Enables task scheduling //	
}
 
//Start task task function 
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL(); //Enter the critical area 
	
    //Create the task //
   	xTaskCreate(Balance_task,  "Balance_task",  BALANCE_STK_SIZE,  NULL, BALANCE_TASK_PRIO,  NULL);	//Vehicle motion control task 
	  xTaskCreate(MPU6050_task, "MPU6050_task", MPU6050_STK_SIZE, NULL, MPU6050_TASK_PRIO, NULL);	//IMU data read task  
    xTaskCreate(show_task,     "show_task",     SHOW_STK_SIZE,     NULL, SHOW_TASK_PRIO,     NULL); //The OLED display displays tasks 
    xTaskCreate(led_task,      "led_task",      LED_STK_SIZE,      NULL, LED_TASK_PRIO,      NULL);	//LED light flashing task 
    xTaskCreate(pstwo_task,    "PSTWO_task",    PS2_STK_SIZE,      NULL, PS2_TASK_PRIO,      NULL);	//Read the PS2 controller task 
    xTaskCreate(data_task,     "DATA_task",     DATA_STK_SIZE,     NULL, DATA_TASK_PRIO,     NULL);	//Usartx3, Usartx1 and CAN send data task 
	
    vTaskDelete(StartTask_Handler); //Delete the start task 

    taskEXIT_CRITICAL();            //Exit the critical section
}






