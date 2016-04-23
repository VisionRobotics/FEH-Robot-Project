/*
    These methods drive the robot using encoder counts. 
    This file includes the basic ability to move forward and
    make turns. Note that most of the methods have overloaded versions
    with default speeds and timeouts for convenience. 
*/

#ifndef BASICDRIVING_H
#define BASICDRIVING_H

#include <FEHRPS.h>
#include <math.h>
#include <EquipmentDeclarations.h>
#include <SensorUtility.h>

void leftSetPercent(float percent)
{
    left_motor.SetPercent(percent);
}

void rightSetPercent(float percent)
{
    right_motor.SetPercent(-percent);
}

void move_indef(float percent) //Drives forever....Careful bro
{
    rightSetPercent(percent);
    leftSetPercent(percent);
}

void move(float percent, float inch, float timeout) //Moves inputted inches
{
    if(inch < 0) //drives in reverse
    {
        inch = -inch;
        percent = -percent;
    }

    //Different counts for different precision. Slow counts allows for 
    //more precise movement and less overshooting when driving. 
    double fullCounts = inch * INCH_TO_COUNTS;
    double slowCounts = fullCounts - abs(percent) / 105.0 * INCH_TO_COUNTS;

    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    rightSetPercent(percent);
    leftSetPercent(percent);

    float startTime = TimeNow();
    while((left_encoder.Counts() + right_encoder.Counts()) / 2.0 < fullCounts && TimeNow() - startTime < timeout)
    {
        if((left_encoder.Counts() + right_encoder.Counts()) / 2.0 > slowCounts && percent > SLOW_SPD)
        {
            //Slowing down near the end of the trip
            rightSetPercent(abs(percent)/percent*SLOW_SPD);
            leftSetPercent(abs(percent)/percent*SLOW_SPD);
        }
    }

    right_motor.Stop();
    left_motor.Stop();
}
void move(float inch)
{
    move(DRIVE_SPD, inch, ENCODER_TIMEOUT);
}
void move(float percent, float inch)
{
    move(percent, inch, ENCODER_TIMEOUT);
}

void turn_right(float percent, float degrees)
{
    double fullCounts = degrees * DEGREES_TO_COUNTS;
    double slowCounts = fullCounts - abs(percent) / 105.0 * INCH_TO_COUNTS;

    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    rightSetPercent(percent);
    leftSetPercent(-percent);

    float startTime = TimeNow();
    while((left_encoder.Counts() + right_encoder.Counts()) / 2.0 < fullCounts && TimeNow() - startTime < ENCODER_TIMEOUT)
    {
        if((left_encoder.Counts() + right_encoder.Counts()) / 2.0 > slowCounts && percent > SLOW_SPD)
        {
            rightSetPercent(abs(percent)/percent*SLOW_SPD);
            leftSetPercent(-abs(percent)/percent*SLOW_SPD);
        }
    }

    right_motor.Stop();
    left_motor.Stop();
}
void turn_right(float degrees)
{
    turn_right(TURN_SPD, degrees);
}

void turn_left(float percent, float degrees)
{
    double fullCounts = degrees * DEGREES_TO_COUNTS;
    double slowCounts = fullCounts - abs(percent) / 105.0 * INCH_TO_COUNTS;

    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    rightSetPercent(-percent);
    leftSetPercent(percent);

    float startTime = TimeNow();
    while((left_encoder.Counts() + right_encoder.Counts()) / 2.0 < fullCounts && TimeNow() - startTime < ENCODER_TIMEOUT)
    {
        if((left_encoder.Counts() + right_encoder.Counts()) / 2.0 > slowCounts && percent > SLOW_SPD)
        {
            rightSetPercent(-abs(percent)/percent*SLOW_SPD);
            leftSetPercent(abs(percent)/percent*SLOW_SPD);
        }
    }

    right_motor.Stop();
    left_motor.Stop();
}
void turn_left(float degrees)
{
    turn_left(TURN_SPD, degrees);
}

void pressButton()
{
	move_indef(-0.6*DRIVE_SPD);
    Sleep(5.6);
}

#endif // BASICDRIVING_H
