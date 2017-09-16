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

#include "Master/Master.h"
#include "Master/BallControl/Axis.h"
#include "Master/BallControl/DOF.h"
#include <PID/DiscreteTimePID/DiscreteTimePID.h>

/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId pidTaskHandle;
osThreadId touchPanelTaskHandle;
osThreadId rxTaskHandle;
osThreadId txTaskHandle;
//osSemaphoreId txSemaphoreHandle;
//osSemaphoreId rxSemaphoreHandle;

/* USER CODE BEGIN Variables */
Master* master;
DiscreteTimePID* XPid;
DiscreteTimePID* YPid;

XAxis 				*XPos;
YAxis 				*YPos;
RollDOF 			*Roll;
PitchDOF 			*Pitch;

double kpX = 0.05;
double kiX = 0.08;
double kdX = 0.04;
double nX = 8;

double kpY = 0.05;
double kiY = 0.08;
double kdY = 0.04;
double nY = 8;

double dt = 0.02;

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
	master = new Master;



	XPos = new XAxis(master->Panel);
	YPos = new YAxis(master->Panel);
	Roll = new RollDOF(master->Platform.Controller);
	Pitch= new PitchDOF(master->Platform.Controller);


	XPid = new DiscreteTimePID(kpX,kiX,kdX,dt,nX,XPos,Pitch);
	YPid = new DiscreteTimePID(kpY,kiY,kdY,dt,nY,YPos,Roll);

	/* USER CODE END Init */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* Create the semaphores(s) */
	/* definition and creation of txSemaphore */
//	osSemaphoreDef(txSemaphore);
//	txSemaphoreHandle = osSemaphoreCreate(osSemaphore(txSemaphore), 1);
//
//	/* definition and creation of rxSemaphore */
//	osSemaphoreDef(rxSemaphore);
//	rxSemaphoreHandle = osSemaphoreCreate(osSemaphore(rxSemaphore), 1);

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
	osThreadDef(rxTask, StartRxTask, osPriorityRealtime, 0, 128);
	rxTaskHandle = osThreadCreate(osThread(rxTask), NULL);

	/* definition and creation of txTask */
	osThreadDef(txTask, StartTxTask, osPriorityRealtime, 0, 128);
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

	master->Communicator.Bluetooth.begin();

	StartProcedure();
	bool stopbuff = true;

	/* Infinite loop */
	for(;;)
	{
		prev_td = td;
		td = master->Panel.IsTouched();

		bool cmdFlag = false;
		Command cmd = master->Communicator.receiveCmd(&cmdFlag);



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

			XPid->Reset();
			YPid->Reset();
			YPid->Stop();
			XPid->Stop();

			Roll->Set(0);
			Pitch->Set(0);

			StartProcedure();
		}

		if(td){
			X = master->Panel.GetX();
			Y = master->Panel.GetY();

			char str[50];
			char xstr[10];
			char ystr[10];
			ftostr(X,xstr);
			ftostr(Y,ystr);
			sprintf(str,"X = %s\r\nY = %s\r\n",xstr,ystr);
			master->Communicator.Bluetooth.writeStr(str);

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



		osDelay(500);
	}
	/* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Application */



void StartProcedure(void){
	master->Platform.Controller.Start();
	double q[6] = {0,0,0,0,0,0};
	master->Platform.Controller.Move(q);
	osDelay(100);

	q[2] = -0.01;
	master->Platform.Controller.Move(q);
	osDelay(300);

	q[2] = 0;
	master->Platform.Controller.Move(q);
	osDelay(100);

	q[2] = -0.002;
	master->Platform.Controller.Move(q);
	osDelay(100);

}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
