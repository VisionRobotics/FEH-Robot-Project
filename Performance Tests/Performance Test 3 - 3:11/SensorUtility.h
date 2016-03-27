/*  This file contains all the functions used to read and process
 *  data from the robot's sensors */

#ifndef SENSORUTILITY_H
#define SENSORUTILITY_H



#include <FEHLCD.h>
//Detects if any light is on
bool light_on(double cdsValue)
{
    return (cdsValue < LIGHT_THRESH);
}

//Waits until start light is detected or until too much time passes
void wait_for_start_light(int seconds)
{
    LCD.WriteLine(sensor.Value());

    float startTime = TimeNow();
    while (!light_on(sensor.Value()))
    {
        LCD.WriteLine(sensor.Value());
        if (TimeNow() - startTime > seconds) //Deploying anyway
        {
            LCD.WriteLine("Light not detected. Starting anyway");
            break;
        }
    }
}



#endif // SENSORUTILITY_H
