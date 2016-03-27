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

//Collects CdS cell data for 2 seconds, averages the results, then compares 
//the result to a threshold to determine if the light is red. 
bool is_red()
{
    float average = 0;
    int valueCount = 0;

    float startTime = TimeNow();
    while (TimeNow() - startTime < 2)
    {
        average += sensor.Value();
        valueCount++;
    }
    average = average / valueCount;
    LCD.Write("Average = ");
    LCD.WriteLine(average);
    if (average <= COLOR_THRESH)
        return true;

    return false;
}

#endif // SENSORUTILITY_H
