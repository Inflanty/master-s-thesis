#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "esp_log.h"

/**
 * @brief Function which returns timestamp to be used in log output
 *
 * This function is used in expansion of ESP_LOGx macros.
 * In the 2nd stage bootloader, and at early application startup stage
 * this function uses CPU cycle counter as time source. Later when
 * FreeRTOS scheduler start running, it switches to FreeRTOS tick count.
 *
 * For now, we ignore millisecond counter overflow.
 *
 * @return timestamp, in milliseconds
 */
// ------ uint32_t esp_log_timestamp(void);

/**
 * @brief Function which returns timestamp to be used in log output
 *
 * This function uses HW cycle counter and does not depend on OS,
 * so it can be safely used after application crash.
 *
 * @return timestamp, in milliseconds
 */
// ------ uint32_t esp_log_early_timestamp(void);

typedef uint32_t time_t;
typedef uint8_t time_system_t;
bool globalTime = FALSE;

struct systemTime{
  time_t timeReal;
  time_t timeCPU;
  time_t timeDiff;
};

typedef enum{
  GET_SYSTEM_TIME_INIT = 1,
  GET_SYSTEM_TIME_READY,
  GET_SYSTEM_TIME_FAIL,
  CALCULATE_DIFFERENCE_READY,
  CHECK_DIFFERENCE_FAIL,
  CHECK_DIFFERENCE_CPU_UP,
  CHECK_DIFFERENCE_TIME_EQUAL,
  CHECK_DIFFERENCE_CPU_DOWN,
}time_system_t;

time_system_t time_getSystem();
time_system_t time_calculateDifference();
time_system_t time_checkDifference();

#endif // _CLOCK_H_

// getSysTime() -> {GET_SYS_TIME_READY} ->  calculateTimeDifference() -> {TIME_DIFFERENCE_READY} -> checkDifference() -> {}
// checkSystemTime()
