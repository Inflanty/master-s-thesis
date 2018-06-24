#include "clock.h"


time_system_t time_getSystem()
{
  if(! globalTime)
  {
    globalTime = TRUE;
    struct systemTime *sysTime;
    sysTime->timeReal = esp_log_early_timestamp(void);
    sysTime->timeCPU = esp_log_timestamp(void);
    sysTime->timeDiff = (sysTime->timeReal) - (sysTime->timeCPU);
    return GET_SYSTEM_TIME_INIT;
  }
  sysTime->timeReal = esp_log_early_timestamp(void);
  sysTime->timeCPU = esp_log_timestamp(void);
  return GET_SYSTEM_TIME_READY;
};
time_system_t time_calculateDifference()
{
  sysTime->timeDiff = (sysTime->timeReal) - (sysTime->timeCPU);
  return CALCULATE_DIFFERENCE_READY;
};
time_system_t time_checkDifference
{
  if(sysTime->timeDiff > 0)
  {
    return CHECK_DIFFERENCE_CPU_UP;
  }else if(sysTime->timeDiff == 0)
  {
    return CHECK_DIFFERENCE_TIME_EQUAL;
  }else
  {
    return CHECK_DIFFERENCE_CPU_DOWN;
  }
  return CHECK_DIFFERENCE_FAIL;
};
