/*
    *   Author  : Jan Głos
    *   Date    : 20.04.2018
    *
    *
    *
    *                        :: extern/main.c ::
    *   :: This file provide polygon for scratch code implementation ::
*/

#include <stdio.h>
#include <stdlib.h>
#include "../intro.h"
#include "calllib.h"

#define RAND_DIV 70
typedef double position_d;
typedef double pid_type_d;
typedef double motor_values_d;

typedef enum {
    MOTOR_DC = 1,
    MOTOR_AC,
    MOTOR_ACDC,
    MOTOR_NONE,

    MOTOR_LOCAL,
    MOTOR_GLOBAL,
    MOTOR_DONE
} motor_type_t;

struct motor{
    const int Power;
    const int Voltage;
    const double Speed;
    const double Curent;

    char Name;
    motor_values_d CurentTmp;
    motor_values_d SpeedTmp;
    motor_values_d LoadMultipler;

};

struct motor *motorObjectGlobal;

motor_values_d motorTakeLoad(motor_type_t motor__, motor_values_d Load)
{
    switch(motor__)
    {
        case MOTOR_LOCAL : return  MOTOR_NONE; break;
        case MOTOR_GLOBAL : if(motorObjectGlobal -> LoadMultipler < 3){ motorObjectGlobal -> CurentTmp = motorObjectGlobal -> Curent * motorObjectGlobal -> LoadMultipler; }; return MOTOR_DONE; break;
    }
}
void motorMake(motor_type_t motorType, char* MotorName){
    switch( motorType )
    {
    case MOTOR_DC:          ;struct motor MotorDC = {.Name = *MotorName, .SpeedTmp = 0, .CurentTmp = 0, }; motorObjectGlobal = &MotorDC; break;
    case MOTOR_AC:          break;
    case MOTOR_ACDC:        break;
    case MOTOR_NONE:        break;
    default:                break;
    }
}
//Generate random load value from 0 to 70 %
motor_values_d motorRandLoad()
{
    int load = rand() % RAND_DIV;
    if (load < 60) {motorObjectGlobal->LoadMultipler;   return ((load)/2) * (0.128);}
    else                                                return 100;
}
void motorIn(motor_values_d input)
{
    printf("Motor IN detected value : %f", input);
}
void motorOut(motor_values_d output)
{
    printf("Motor OUT detected value : %f", output);
}
void pwmOutShow(pid_type_d currentPWM)
{
    printf("Current PWM : %f\n", (double) currentPWM);
}
position_d getPositionTarget()
{
    position_d positionTarget = 0;

    printf("Provide position target end put enter ! : \n");

    positionTarget = (position_d) getchar();

    return positionTarget;
}
position_d readCurrentPosition()
{
    position_d positionDefined = 0;

    printf("Provide current position end put enter ! : \n");

    positionDefined = (position_d) getchar();

    return positionDefined;
}
double limit(double limit, double limitated)
{
    if ( limitated >= limit )
    {
        limitated = limit;
    }
    else if ( limitated <= -limit )
    {
        limitated = -limit;
    }

    return limitated;
}
void PIDcontroll()
{
    position_d      currentPosition = 0;
    position_d      targetPosition  = getPositionTarget();
    pid_type_d      deviation       = 1,    lastDeviation       = 1;
    pid_type_d      integral        = 1;
    pid_type_d      derivative      = 1;
    pid_type_d      pwm             = 0;

    pid_type_d KP = 1;
    pid_type_d KI = 0.3;
    pid_type_d KD = 0.01;

    while(1)
    {
        currentPosition     = readCurrentPosition();

        for(int i = 0; i < 1; i ++)
        {
            deviation           = targetPosition - currentPosition;

            integral            += deviation;

            derivative          = deviation - lastDeviation;

            pwm                 = (KP * deviation) + (KI * integral) + (KD * derivative);

            pwm                 = limit(100, pwm);

            lastDeviation       = deviation;

            pwmOutShow(pwm);
        }
        printf("EXIT :: PWM = %f\n", (double) pwm);
    }
}
void call(int (*fncXlib)(call_reason_t), call_reason_t theSzama)
{
    int szamaValue = fncXlib(theSzama);
    printf("Your szama provide you %d calories, goodbye fit life\n", szamaValue);
}



int main()
{
    printf("%s\n", log_U);
    call(caloriesValue, BURGER);
    return 0;
}
