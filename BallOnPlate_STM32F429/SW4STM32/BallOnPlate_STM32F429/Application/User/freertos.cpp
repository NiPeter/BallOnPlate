/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V.
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "tim.h"
#include "gpio.h"
#include "adc.h"
#include "usart.h"

#ifdef __cplusplus
}
#endif

#include "PlatformController/PlatformController.hpp"
#include "BallControl/DOF.h"

#include "TouchPanel/TouchPanel_4W/TouchPanel_4W.hpp"
#include "BallControl/Axis.h"

#include "PID/DiscreteTimePID/DiscreteTimePID.h"

#include "Communicator/Serial/HC05/HC05.hpp"
#include "Communicator/Communicator.hpp"


/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId pidTaskHandle;
osThreadId touchPanelTaskHandle;
osThreadId rxTaskHandle;
osThreadId txTaskHandle;
osSemaphoreId txSemaphoreHandle;
osSemaphoreId rxSemaphoreHandle;

/* USER CODE BEGIN Variables */

HC05	Bluetooth(&huart1);
Communicator Comm(&Bluetooth);

Servo Servos[6] = {

		Servo(&htim4,TIM_CHANNEL_2),	// PB7 - Niebieski

		Servo(&htim3,TIM_CHANNEL_1),	// PB4 - Pomarañczowy
		Servo(&htim2,TIM_CHANNEL_2),	// PB3 - Fioletowy

		Servo(&htim9,TIM_CHANNEL_2), 	// PE6 - Br¹zowy
		Servo(&htim9,TIM_CHANNEL_1),	// PE5 - ¯ó³ty

		Servo(&htim3,TIM_CHANNEL_3),	// PC8 - Bia³y

};
Steward_Struct Steward = {
		{ 0.075, 	0.5236 	}, // Base_Struct {r , alpha}
		{ 0.05,		1.7453	}, // Platform_Struct {r , alpha}
		{ 0.01653,	0.095	}  // Drive_Struct {a , s}
};
PlatformController 	Controller(Servos,&Steward);
RollDOF 			Roll(Controller);
PitchDOF 			Pitch(Controller);

AnalogPin 			XAnalog(&hadc1,X_ADC_GPIO_Port,X_ADC_Pin);
AnalogPin 			YAnalog(&hadc2,Y_ADC_GPIO_Port,Y_ADC_Pin);
Pin					XGnd(X_GND_GPIO_Port,X_GND_Pin);
Pin					YGnd(Y_GND_GPIO_Port,Y_GND_Pin);
TouchPanel4W 		Panel(XAnalog,XGnd,YAnalog,YGnd);

XAxis 				XPos(Panel);
YAxis 				YPos(Panel);


double kpX = 0.05;
double kiX = 0.08;
double kdX = 0.04;
double nX = 8;

double kpY = 0.05;
double kiY = 0.08;
double kdY = 0.04;
double nY = 8;

double dt = 0.02;


double setpointX = 0;
double setpointY = 0;

DiscreteTimePID XPid(kpX,kiX,kdX,dt,nX,&XPos,&Pitch);
DiscreteTimePID YPid(kpY,kiY,kdY,dt,nY,&YPos,&Roll);



float X,Y;
int td,prev_td,td_inc;


float x,y,z,roll,pitch,yaw;

float outX,outY;
double errorX, sumErrorX, dErrorX;
double errorY, sumErrorY, dErrorY;
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
extern void StartPIDTask(void const * argument);
extern void StartTouchPanelTask(void const * argument);
extern void StartRxTask(void const * argument);
extern void StartTxTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

void StartProcedure(void);

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of txSemaphore */
  osSemaphoreDef(txSemaphore);
  txSemaphoreHandle = osSemaphoreCreate(osSemaphore(txSemaphore), 15);

  /* definition and creation of rxSemaphore */
  osSemaphoreDef(rxSemaphore);
  rxSemaphoreHandle = osSemaphoreCreate(osSemaphore(rxSemaphore), 15);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 512);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of pidTask */
  osThreadDef(pidTask, StartPIDTask, osPriorityHigh, 0, 512);
  pidTaskHandle = osThreadCreate(osThread(pidTask), NULL);

  /* definition and creation of touchPanelTask */
  osThreadDef(touchPanelTask, StartTouchPanelTask, osPriorityAboveNormal, 0, 256);
  touchPanelTaskHandle = osThreadCreate(osThread(touchPanelTask), NULL);

  /* definition and creation of rxTask */
  osThreadDef(rxTask, StartRxTask, osPriorityBelowNormal, 0, 128);
  rxTaskHandle = osThreadCreate(osThread(rxTask), NULL);

  /* definition and creation of txTask */
  osThreadDef(txTask, StartTxTask, osPriorityBelowNormal, 0, 128);
  txTaskHandle = osThreadCreate(osThread(txTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */

  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
	Bluetooth.begin();

	StartProcedure();
	bool stopbuff = true;

	/* Infinite loop */
	for(;;)
	{
		prev_td = td;
		td = Panel.IsTouched();

		bool cmdFlag = false;
		Command cmd = Comm.receiveCmd(&cmdFlag);



		if(cmdFlag){
			switch(cmd.getType()){
			case Stop:
				stopbuff = false;
				break;
			case Start:
				stopbuff = true;
				break;
			default:
				break;
			}
		}
		td = td && stopbuff;

		if( ((prev_td == true) && (td == false))  ){
			td_inc++;

			XPid.Reset();
			YPid.Reset();
			YPid.Stop();
			XPid.Stop();

			Roll.Set(0);
			Pitch.Set(0);

			StartProcedure();
		}

		if(td){
			X = Panel.GetX();
			Y = Panel.GetY();
			YPid.Start();
			XPid.Start();
		}else{
			X = 0;
			Y = 0;
		}

		XPid.Tune(kpX,kiX,kdX,nX);
		YPid.Tune(kpY,kiY,kdY,nY);


		XPid.SetInput(23+setpointX);
		YPid.SetInput(19+setpointY);

		outX = XPid.GetOutput();
		outY = YPid.GetOutput();

		errorX = XPid.GetError();
		errorY = YPid.GetError();



		osDelay(10);
	}
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Application */



void StartProcedure(void){
	Controller.Start();
	double q[6] = {0,0,0,0,0,0};
	Controller.Move(q);
	osDelay(100);

	q[2] = -0.01;
	Controller.Move(q);
	osDelay(300);

	q[2] = 0;
	Controller.Move(q);
	osDelay(100);

	q[2] = -0.002;
	Controller.Move(q);
	osDelay(100);

}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
