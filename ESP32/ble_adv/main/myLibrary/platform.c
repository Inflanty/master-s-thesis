#include "platform.h"

void mes_saveValue(storage_type_t storeType)
{
    switch(storeType)
    {
        case STORAGE_GLOBAL : return STORAGE_DONE; break;
        case STORAGE_LOCAL  : return STORAGE_NONE; break;
        default             : return STORAGE_BREAK; break;
    }
}
measure_control_t mes_doMeasure(measure_type_t mType)
{
    switch(mType)
    {
        case MEASURE_TYPE_XYZ   : if(mes_accelerometerRead()){return MEASURE_DONE}; return MEASURE_NONE; break;
        case MEASURE_TYPE_ANGLE : if(mes_angleRead()){return MEASURE_DONE}; return MEASURE_NONE; break;
        case MEASURE_TYPE_SPEED : if(mes_speedRead()){return MEASURE_DONE}; return MEASURE_NONE; break;
        default                 : return MEASURE_BLOCK; break;
    }
}
measure_control_fail_t mes_accelerometerRead()
{
    // Function body depend of platform
    return 1;
}
measure_control_fail_t mes_angleRead()
{
    // Function body depend of platform
    return 1;
}
measure_control_fail_t mes_speedRead()
{
    // Function body depend of platform
    return 1;
}
// mes_doMeasure -> mes_saveValue -> ble_prepareData -> ble_sendData -> [ble_readResponse ?]
