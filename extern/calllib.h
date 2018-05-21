#ifndef _CALLLIB_H_
#define _CALLLIB_H_
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define registerVal 256
//for building into .o lib file run : gcc -o calllib.o -c calllib.c
typedef enum{
    PIZZA = 0,
    BURGER,
    LASAGNE,
    FRIES,
    CHIP,
    CAKES,
    ALL_WITH_FAT,
}call_reason_t;

//  Holding register : uint8_t register

typedef struct{
    bool hold;
    uint8_t data[registerVal];
}holdingRegister;

//init global
holdingRegister *dataRx, *dataTx;

bool holdRegister(holdingRegister *regRecive);
//make callback fnc for register hold ?
int caloriesValue(call_reason_t reason);

#endif //_CALLLIB_H_
