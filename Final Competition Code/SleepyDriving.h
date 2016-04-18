#ifndef SLEEPYDRIVING_H
#define SLEEPYDRIVING_H

#include <BasicDriving.h>
#include <RPSNavigation.h>

void move_sleep(float percent, float inch)
{
    move(percent, inch);
    Sleep(DFT_SLEEP);
}
void move_sleep(float inch)
{
    move_sleep(DRIVE_SPD, inch);
}

void turn_right_sleep(float percent, float degrees)
{
    turn_right(percent, degrees);
    Sleep(DFT_SLEEP);
}
void turn_right_sleep(float degrees)
{
    turn_right_sleep(TURN_SPD, degrees);
}

void turn_left_sleep(float percent, float degrees)
{
    turn_left(percent, degrees);
    Sleep(DFT_SLEEP);
}
void turn_left_sleep(float degrees)
{
    turn_left_sleep(TURN_SPD, degrees);
}

void turn_sleep(float percent, float degrees)
{
	if(degrees > 0)
	{
		turn_right_sleep(percent, degrees);
	}
	else
	{
		turn_left_sleep(percent, -degrees);
	}
}
void turn_sleep(float degrees)
{
    turn_sleep(TURN_SPD, degrees);
}


#endif // SLEEPYDRIVING_H
