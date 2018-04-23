#ifndef _PLATFORM_H_
#define _PLATFORM_H_

typedef enum{
    MEASURE_DONE,
    MEASURE_READY,
    MEASURE_BLOCK,
    MEASURE_NONE
}measure_control_t;

typedef enum{
    MEASURE_TYPE_XYZ,
    MEASURE_TYPE_ANGLE,
    MEASURE_TYPE_SPEED
}measure_type_t;

typedef double measure_value_t
typedef bool measure_control_fail_t
struct measurement{
    measure_value_t Value_1;
    measure_value_t Value_2;
    measure_value_t Value_3;

    measure_value_t Value_supp;

    measure_control_t MeasureControl;
}

struct measurement *measurementGlobalData;

typedef enum {
    STORAGE_LOCAL,
    STORAGE_GLOBAL,
    STORAGE_DONE,
    STORAGE_NONE,
    STORAGE_BREAK
} storage_type_t;
//
//  Save value, choose storage type, local or global
//
void mes_saveValue(storage_type_t storeType);
//
//  Do measure, choose measure type from measure_type_t. Return measure done or fail
//
measure_control_t mes_doMeasure(measure_type_t mType);
//
//  Do direct accelerometer measure. Return 0 or 1 depend of status
//
measure_control_fail_t mes_accelerometerRead();
//
//  Do direct angle measure. Return 0 or 1 depend of status
//
measure_control_fail_t mes_angleRead();
//
//  Do direct speed measure. Return 0 or 1 depend of status
//
measure_control_fail_t mes_speedRead();

#endif //_PLATFORM_H_
