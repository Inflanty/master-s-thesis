#ifdef _TOUCH_PAD_H_
#define _TOUCH_PAD_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/touch_pad.h"

#define TOUCH_TEST_LOOP_NUM   (10)
#define TOUCH_PAD_NO_CHANGE   (-1)
#define TOUCH_THRESH_NO_USE   (0)

void tp_example_read_task(void *pvParameter);
void tp_example_touch_pad_init();

#endif
