#ifndef SENSORUTILITY_H
#define SENSORUTILITY_H

#include <FEHLCD.h>
#include <FEHRPS.h>

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
        LCD.Clear();
        LCD.WriteLine((int)(TimeNow() - startTime));
        if (TimeNow() - startTime > seconds) //Deploying anyway
        {
            LCD.WriteLine("Light not detected. Starting anyway");
            break;
        }
        Sleep(25);
    }
}

//Collects CdS cell data for 2 seconds, averages the results, then compares
//the result to a threshold to determine if the light is red.
bool is_red()
{
    float average = 0;
    int valueCount = 0;

    Sleep(150);
    float startTime = TimeNow();
    while (TimeNow() - startTime < FUEL_LIGHT_READ_TIME)
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

//forward = 1, backward = -1
int rightSwitchDirection()
{
    if(RPS.BlueSwitchDirection() == 2) return -1;
    return 1;
}

//forward = 1, backward = -1
int middleSwitchDirection()
{
    if(RPS.WhiteSwitchDirection() == 2) return -1;
    return 1;
}

//forward = 1, backward = -1
int leftSwitchDirection()
{
    if(RPS.RedSwitchDirection() == 2) return -1;
    return 1;
}

#endif // SENSORUTILITY_H
