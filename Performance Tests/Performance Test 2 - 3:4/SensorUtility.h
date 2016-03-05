/*  This file contains all the functions used to read and process
 *  data from the robot's sensors */

#ifndef SENSORUTILITY_H
#define SENSORUTILITY_H

#define LIGHT_THRESH .45 //Vaules below this correspond to a detected start light

#define back_up_distance 1 //change
#define push_distance .5 //change
#define UP_POSITION 180
#define DOWN_POSITION 77

//Detects if any light is on
bool light_on(double cdsValue)
{
    return (cdsValue < LIGHT_THRESH);
}

//Waits until start light is detected or until too much time passes
void wait_for_start_light(int seconds)
{
    float startTime = TimeNow();
    while (!light_on(sensor.Value()))
    {
        if (TimeNow() - startTime > seconds) //Deploying anyway
        {
            LCD.WriteLine("Light not detected. Starting anyway");
            break;
        }
    }
}



#endif // SENSORUTILITY_H
