#include "exTask.h"

/*
*@ External task 1 definition
*
*/
void externalTask1 ( void * pvParameter )
{
  UNUSED_PARAMETER ( pvParameter );
  uint8_t * buttonNo = 0;
  hExternQueue1 = xQueueCreate( 0, sizeof( unsigned long ) );
  vTraceSetQueueName( (void*) &hExternQueue1, (const char*) "Button Queue");

  for (;;)
  {
    for ( int buttonNumber = 0; buttonNumber < 4; buttonNumber ++)
    {
      if ( bsp_board_button_state_get( buttonNumber ) )
      {
        *buttonNo = buttonNumber;
        if ( hExternQueue1 != 0 )
        {
          if ( xQueueSend ( hExternQueue1, (void *) buttonNo, (TickType_t) 10 ) != pdPASS )
          {
            //
          }
        }
        while ( bsp_board_button_state_get( buttonNumber ) ) { vTaskDelay ( 20 ); };
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
  uint8_t * buttonNumber = 0;
  for (;;)
  {
    if ( hExternQueue1 != 0 )
    {
      if ( xQueueReceive ( hExternQueue1, (void * ) buttonNumber,  (TickType_t) 0 ) )
      {
        bsp_board_led_invert ( * buttonNumber );
      }
    }
  }
  vTaskDelete ( NULL );
}