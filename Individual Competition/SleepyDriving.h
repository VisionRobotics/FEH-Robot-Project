#ifndef SLEEPYDRIVING_H
#define SLEEPYDRIVING_H

#include <DriveAndNavigation.h>

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
    turn_right_sleep(DRIVE_SPD, degrees);
}

void turn_left_sleep(float percent, float degrees)
{
    turn_left(percent, degrees);
    Sleep(DFT_SLEEP);
}
void turn_left_sleep(float degrees)
{
    turn_left_sleep(DRIVE_SPD, degrees);
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
	turn_sleep(DRIVE_SPD, degrees);
}


//useless now
void check_x_sleep(float x_coordinate)
{
    check_x(x_coordinate);
}

void check_x_minus_sleep(float x_coordinate)
{
    check_x_minus(x_coordinate);
}
void check_x_plus_sleep(float x_coordinate)
{
    check_x_plus(x_coordinate);
}

void check_y_minus_sleep(float y_coordinate)
{
    check_y_minus(y_coordinate);
}
void check_y_plus_sleep(float y_coordinate)
{
    check_y_plus(y_coordinate);
}
void check_y_sleep(float y_coordinate)
{
    check_y(y_coordinate);
}

void check_heading_sleep(float targetHeading)
{
    check_heading(targetHeading);
}

#endif // SLEEPYDRIVING_H
