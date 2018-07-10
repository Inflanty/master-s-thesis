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
extern QueueHandle_t       hExternQueue1;
/*
*@ External 1 Handler
*/
extern TaskHandle_t        hExternTask1;
/*
*@ External 2 Handler
*/
extern TaskHandle_t        hExternTask2;
/*
*@ External 3 Handler
*/
extern TaskHandle_t        hExternTask3;
/*
*@ External 4 Handler
*/
extern TaskHandle_t        hExternTask4;
/*
*@ External handler form main
*/
extern TaskHandle_t        hUnnamedTask;

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
/*
*@ External task 3 definition
*
*/
void externalTask3 ( void * pvParameter );
/*
*@ External task 4 definition
*
*/
void externalTask4 ( void * pvParameter );


#endif