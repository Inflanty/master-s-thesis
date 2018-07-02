#ifndef _EX_TASK_H_
#define _EX_TASK_H_
/*
*
*@ This file provide tasks
*
*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "boards.h"

/* 
*@ Struct for button use
*/
struct button {
  bool        status;
  uint8_t     number;
};

/*
*@ External 1 Queue
*/
QueueHandle_t       hExternQueue1;
/*
*@ External 1 Handler
*/
TaskHandle_t        hExternTask1;
/*
*@ External 2 Handler
*/
TaskHandle_t        hExternTask2;

/*
*@ External task 1 definition
*
*/
void externalTask1  ( void * pvParameter );
/*
*@ External task 2 definition
*
*/
void externalTask2  ( void * pvParameter );


#endif