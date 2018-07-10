#include "exTask.h"

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
*@ External 3 Handler
*/
TaskHandle_t        hExternTask3;
/*
*@ External 4 Handler
*/
TaskHandle_t        hExternTask4;
/*
*@ External task 1 definition
*
*/
void externalTask1 ( void * pvParameter )
{
  UNUSED_PARAMETER ( pvParameter );
  unsigned int controlValue = 0;
  hExternQueue1 = xQueueCreate( 0, sizeof( unsigned long ) );

  /* Register log channel */
  traceString controlMark = xTraceRegisterString("task 1");

  /* Register the queue */
  vTraceSetQueueName( (void*) &hExternQueue1, (const char*) "Button Queue");

  for (;;)
  { 
    /* delay and Value increment */
    vTaskDelay( 100 );
    controlValue += 1;
    if ( controlValue > 10000 ) controlValue = 0;
    
    vTracePrintF(controlMark, "Control Value : %u", controlValue);

    if ( bsp_board_button_state_get ( BSP_BOARD_BUTTON_3 ) && ( hExternQueue1 != 0 ) )
    {
      //bsp_board_led_invert ( 3 );
      if ( xQueueSend ( hExternQueue1, (void *) &controlValue, (TickType_t) 1 ) != pdPASS && 0 )
      {
        vTracePrint ( controlMark, "Can't send queue ! in task 1" );
      }
    }
  }
  vTaskDelete ( NULL );
}
/*
*@ External task 2 definition
*
*/
void externalTask2 ( void * pvParameter )
{
  UNUSED_PARAMETER ( pvParameter );
  int queueValue = 0;
  traceString controlMark = xTraceRegisterString("task 2");

  for (;;)
  {
    vTaskDelay ( 1 );

    if ( hExternQueue1 != 0 )
    {
      if ( xQueueReceive ( hExternQueue1, &queueValue, (TickType_t) 1 ) )
      {
        vTracePrintF(controlMark, "Queue Value : %u", queueValue);
      }
    }

  }
  vTaskDelete ( NULL );
}
/*
*@ External task 3 definition
*
*/
void externalTask3 ( void * pvParameter )
{
  UNUSED_PARAMETER ( pvParameter );

  traceString waterMarkMain = xTraceRegisterString("Water Mark from mian's task");
  traceString waterMarkExternal1 = xTraceRegisterString("Water Mark from task 1");
  traceString waterMarkExternal2 = xTraceRegisterString("Water Mark from task 2");
  traceString waterMarkExternal3 = xTraceRegisterString("Water Mark from task 3");
  UBaseType_t uxHighWaterMark;

  for ( ;; )
  {
    vTaskDelay ( 100 );
    for ( int taskNumber = 0; taskNumber < 4; taskNumber ++ )
    {
      switch ( taskNumber )
      {
        case 0:
        /* Calculate the watermark */
        uxHighWaterMark = uxTaskGetStackHighWaterMark( hUnnamedTask );
        /* Send wm value */
        vTracePrintF(waterMarkMain, "Calculated Water Mark %u", uxHighWaterMark);
        break;
        case 1:
        uxHighWaterMark = uxTaskGetStackHighWaterMark( hExternTask1 ); 
        /* Send wm value */
        vTracePrintF(waterMarkExternal1, "Calculated Water Mark %u", uxHighWaterMark);
        break;
        case 2:
        uxHighWaterMark = uxTaskGetStackHighWaterMark( hExternTask2 ); 
        /* Send wm value */
        vTracePrintF(waterMarkExternal2, "Calculated Water Mark %u", uxHighWaterMark);
        break;
        case 3:
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL ); 
        vTracePrintF(waterMarkExternal3, "Calculated Water Mark %u", uxHighWaterMark);
        break;
      }
    }
  }

  vTaskDelete ( NULL );
}
/*
*@ External task 4 definition
*
*/
void externalTask4 ( void * pvParameter )
{
  UNUSED_PARAMETER ( pvParameter );
  traceString waterMarkExternal4 = xTraceRegisterString("Task 4");
  int tmpVar = 0;
  for (;;)
  {
    vTaskDelay(1);
    tmpVar += 1;
    if (tmpVar > 1000) tmpVar = 0, vTracePrint(waterMarkExternal4, "TASK 4 : NULL");
  }
  vTaskDelete (NULL);
}