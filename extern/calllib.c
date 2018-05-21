#include "calllib.h"

int caloriesValue(call_reason_t reason)
{
    int calories = 0;
    switch(reason){
        case PIZZA:
            calories = 2269;
        break;
        case BURGER:
            calories = 354;
        break;
        case LASAGNE:
            calories = 344;
        break;
        case FRIES:
            calories = 380;
        break;
        case CHIP:
            calories = 1217;
        break;
        case CAKES:
            calories = 1531;
        break;
        default:
            calories = -1;
        break;
    }
    return calories;
}
bool holdRegister(holdingRegister *regReceive)
{
    if(regReceive == dataRx)
    {
        if(dataRx->hold)
        {
            return 0;//register is hold
        }else
        {
            dataRx->hold = 1;
        }
    }else if(regReceive == dataTx)
    {
        if(dataTx->hold)
        {
            return 0;//register is hold
        }else
        {
            dataTx->hold = 1;
        }
    }else
    {
        return 0;
    }
    return 1;
}
