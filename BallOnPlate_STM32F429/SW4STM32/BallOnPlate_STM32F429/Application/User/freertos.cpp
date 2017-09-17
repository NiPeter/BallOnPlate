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

#include <PID/DiscreteTimePID/DiscreteTimePID.h>

#include "StewardPlatform/BallControl/Axis.h"
#include "StewardPlatform/BallControl/DOF.h"
#include "StewardPlatform/StewardPlatform.h"

/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId pidTaskHandle;

/* USER CODE BEGIN Variables */
StewardPlatform* stewardPlatform;
DiscreteTimePID* XPid;
DiscreteTimePID* YPid;

XAxis 				*XPos;
YAxis 				*YPos;
RollDOF 			*Roll;
PitchDOF 			*Pitch;

double kpX = 0.065;
double kiX = 0.03;
double kdX = 0.044;
double nX = 10;

double kpY = 0.065;
double kiY = 0.03;
double kdY = 0.044;
double nY = 10;

double dt = 0.005;

float X,Y;
int td,prev_td,td_inc;

double setpointX = 0;
double setpointY = 0;

float outX,outY;
double errorX;
double errorY;
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
extern void StartPIDTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

void StartProcedure(void);

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	stewardPlatform = new StewardPlatform;



	XPos = new XAxis(stewardPlatform->TouchPanel);
	YPos = new YAxis(stewardPlatform->TouchPanel);
	Roll = new RollDOF(stewardPlatform->Platform.Controller);
	Pitch= new PitchDOF(stewardPlatform->Platform.Controller);


	XPid = new DiscreteTimePID(kpX,kiX,kdX,dt,nX,XPos,Pitch);
	YPid = new DiscreteTimePID(kpY,kiY,kdY,dt,nY,YPos,Roll);

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

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
  osThreadDef(pidTask, StartPIDTask, osPriorityHigh, 0, 256);
  pidTaskHandle = osThreadCreate(osThread(pidTask), NULL);

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
	int inc = 0;
	stewardPlatform->CommunicationCenter.Bluetooth.begin();

	StartProcedure();
	bool stopbuff = true;

	/* Infinite loop */
	for(;;)
	{
		prev_td = td;
		td = stewardPlatform->TouchPanel.IsTouched();

		bool cmdFlag = false;
		Command cmd = stewardPlatform->CommunicationCenter.receiveCmd(&cmdFlag);



		if(cmdFlag){
			switch(cmd.getType()){

			case Stop:
				stopbuff = false;
				break;

			case Start:
				stopbuff = true;
				break;

			case setTargetX:
				setpointX = cmd.getParam();
				break;

			case setTargetY:
				setpointY = cmd.getParam();
				break;

			default:
				break;
			}
		}
		td = td && stopbuff;

		if( ((prev_td == true) && (td == false))  ){
			td_inc++;

			XPid->Reset();
			YPid->Reset();
			YPid->Stop();
			XPid->Stop();

			Roll->Set(0);
			Pitch->Set(0);

			StartProcedure();
		}

		if(td){
			X = stewardPlatform->TouchPanel.GetX();
			Y = stewardPlatform->TouchPanel.GetY();

			YPid->Start();
			XPid->Start();
		}else{
			X = 0;
			Y = 0;
		}

		XPid->Tune(kpX,kiX,kdX,nX);
		YPid->Tune(kpY,kiY,kdY,nY);


		XPid->SetInput(23+setpointX);
		YPid->SetInput(19+setpointY);

		outX = XPid->GetOutput();
		outY = YPid->GetOutput();

		errorX = XPid->GetError();
		errorY = YPid->GetError();


		inc++;
		if( inc == 50){
			cmd = Command(pidXError,errorX);
			stewardPlatform->CommunicationCenter.sendCmd(cmd);

			cmd = Command(pidYError,errorY);
			stewardPlatform->CommunicationCenter.sendCmd(cmd);
			inc=0;
		}


		osDelay(10);
	}
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Application */

/**
 *
 * @param huart
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){

	stewardPlatform->UART_TxCpltCallback(huart);
}
/********************************************************/



/*
 *
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	stewardPlatform->UART_RxCpltCallback(huart);

}
/********************************************************/



void StartProcedure(void){
	stewardPlatform->Platform.Controller.Start();
	double q[6] = {0,0,0,0,0,0};
	stewardPlatform->Platform.Controller.Move(q);
	osDelay(100);

	q[2] = -0.01;
	stewardPlatform->Platform.Controller.Move(q);
	osDelay(300);

	q[2] = 0;
	stewardPlatform->Platform.Controller.Move(q);
	osDelay(100);

	q[2] = -0.002;
	stewardPlatform->Platform.Controller.Move(q);
	osDelay(100);

}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
