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
*@ External task 1 definition
*
*/
void externalTask1 ( void * pvParameter )
{
  UNUSED_PARAMETER ( pvParameter );
  UBaseType_t uxHighWaterMark;
  unsigned int controlValue = 0;
  hExternQueue1 = xQueueCreate( 0, sizeof( unsigned long ) );

  /* Register log channel */
  traceString waterMark = xTraceRegisterString("Water Mark");
  traceString controlMark = xTraceRegisterString("Control");

  /* Register the queue */
  vTraceSetQueueName( (void*) &hExternQueue1, (const char*) "Button Queue");

  /*  */
  uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );

  /* Send wm value */
  vTracePrintF(waterMark, "Calculated Water Mark %u", uxHighWaterMark);
  for (;;)
  {
    for ( int buttonNumber = 13; buttonNumber <= 16; buttonNumber ++)
    {
      vTaskDelay( 100 );
      controlValue += 1;
      if ( controlValue > 10000 ) controlValue = 0;
    }
    /*  */
    uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );

    /* Send wm value */
    vTracePrintF(waterMark, "Calculated Water Mark %u", uxHighWaterMark );
    vTracePrintF(controlMark, "Calculated Water Mark %u", controlValue);
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
  for (;;)
  {
    if ( hExternQueue1 != 0 )
    {
      if ( xQueueReceive ( hExternQueue1, (void * ) &queueValue,  (TickType_t) 0 ) != pdPASS )
      {

      }
      if ( queueValue != 0 && queueValue != 1 ) bsp_board_led_invert ( queueValue );
    }
  }
  vTaskDelete ( NULL );
}