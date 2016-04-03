#ifndef DRIVEANDNAVIGATION_H
#define DRIVEANDNAVIGATION_H

#include <FEHRPS.h>
#include <math.h>
#include <EquipmentDeclarations.h>
#include <SensorUtility.h>
#include <SleepyDriving.h>

float RPSOffsetX = 0;
float RPSOffsetY = 0;

typedef struct vect{
    float x;
    float y;
}Vect;

void leftSetPercent(float percent)
{
    //left motor runs slightly stronger
    left_motor.SetPercent(percent * LEFT_MOTOR_SCALE);
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

void move_smooth(float percent, float inch) //Moves inputted inches
{
    double counts = inch * INCH_TO_COUNTS;

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    if(inch >= 1) //////////
    {
        float multiplier;
        float startTime = TimeNow();
        float currentTime = startTime;
        while(currentTime-startTime < DELAY_TIME)
        {
            currentTime = TimeNow();
            multiplier = (currentTime-startTime)/DELAY_TIME;
            multiplier = multiplier*multiplier;
            multiplier = 0.7*multiplier+0.3;
            rightSetPercent(percent*multiplier);
            leftSetPercent(percent*multiplier);
        }
    }
    rightSetPercent(percent);
    leftSetPercent(percent);

    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void move(float percent, float inch, float timeout) //Moves inputted inches
{
    if(inch < 0)
    {
        inch = -inch;
        percent = -percent;
    }

    double counts = inch * INCH_TO_COUNTS;

    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    rightSetPercent(percent);
    leftSetPercent(percent);

    float startTime = TimeNow();
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts && TimeNow() - startTime < timeout);

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

/*
void move_up_ramp(float percent, float inch) //Moves inputted inches
{
    if(inch < 0)
    {
        inch = -inch;
        percent = -percent;
    }

    double counts = inch * INCH_TO_COUNTS;

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    rightSetPercent(percent);
    leftSetPercent(percent);

    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
} */

void turn_right(float percent, float degrees)
{
    double counts = degrees * DEGREES_TO_COUNTS;

    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    rightSetPercent(percent);
    leftSetPercent(-percent);

    float startTime = TimeNow();
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts && TimeNow() - startTime < ENCODER_TIMEOUT);

    right_motor.Stop();
    left_motor.Stop();
}
void turn_right(float degrees)
{
    turn_right(DRIVE_SPD, degrees);
}



void turn_left(float percent, float degrees)
{
    double counts = degrees * DEGREES_TO_COUNTS;

    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    rightSetPercent(-percent);
    leftSetPercent(percent);

    float startTime = TimeNow();
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts && TimeNow() - startTime < ENCODER_TIMEOUT);

    right_motor.Stop();
    left_motor.Stop();
}
void turn_left(float degrees)
{
    turn_left(DRIVE_SPD, degrees);
}

void pressButton()
{
	move_indef(-0.6*DRIVE_SPD);
    Sleep(6.0);
}


///////////////////////////////////
////////////////RPS////////////////
///////////////////////////////////
bool RPSDetected()
{
	return RPS.X() >= 0;
}
void calculateRobotOffset()
{
	if(RPSDetected())
	{
        RPSOffsetX = RPS.X()-EXPECTED_RPS_START_X;
        RPSOffsetY = RPS.Y()-EXPECTED_RPS_START_Y;
	}
    else
    {
        LCD.WriteLine("!*!*!*!*!RPS not read on start!*!*!*!*!");
    }
}

float getRobotX()
{
    if(RPSDetected()) return RPS.X()-RPSOffsetX;
	return RPS.X();
}
float getRobotY()
{
    if(RPSDetected()) return RPS.Y()-RPSOffsetY;
	return RPS.Y();
}
float getRobotHeading()
{
	return RPS.Heading();
}

bool RPSDropped()
{
	if(!RPSDetected())
	{
		float startTime = TimeNow();
		while (!RPSDetected())
		{
			if(TimeNow() - startTime > RPS_TIMEOUT_DURATION)
			{
				LCD.WriteLine("!!RPS dropped and timed out!!");
				return true; 
			}
			Sleep(25);
		}
	}
	return false;
}

void check_x_minus(float x_coordinate) //using RPS while robot is in the +x direction
{
	float startTime = TimeNow();
    while(TimeNow() - startTime < CHECK_SLEEP || !RPSDetected())
    {
		if(RPSDropped()) return;

		if(getRobotX() > x_coordinate + POSITION_THRESHOLD/2.0)
		{
			move(PULSE_DRIVE_SPD, PULSE_DIST_POSITION);
			startTime = TimeNow();
		}
		else if(getRobotX() < x_coordinate - POSITION_THRESHOLD/2.0)
		{
			move(-PULSE_DRIVE_SPD, PULSE_DIST_POSITION);
			startTime = TimeNow();
		}
		Sleep(25);
    }
}

void check_x_plus(float x_coordinate) //using RPS while robot is in the +x direction
{
    float startTime = TimeNow();
    while(TimeNow() - startTime < CHECK_SLEEP || !RPSDetected())
    {
		if(RPSDropped()) return;

		if(getRobotX() > x_coordinate + POSITION_THRESHOLD/2.0)
		{
			move(-PULSE_DRIVE_SPD, PULSE_DIST_POSITION);
			startTime = TimeNow();
		}
		else if(getRobotX() < x_coordinate - POSITION_THRESHOLD/2.0)
		{
			move(PULSE_DRIVE_SPD, PULSE_DIST_POSITION);
			startTime = TimeNow();
		}
		Sleep(25);
    }
}

void check_y_minus(float y_coordinate) //using RPS while robot is in the -y direction
{
    float startTime = TimeNow();
    while(TimeNow() - startTime < CHECK_SLEEP || !RPSDetected())
    {
		if(RPSDropped()) return;
		
		if(getRobotY() > y_coordinate + POSITION_THRESHOLD/2.0)
		{
			move(PULSE_DRIVE_SPD, PULSE_DIST_POSITION);
			startTime = TimeNow();
		}
		else if(getRobotY() < y_coordinate - POSITION_THRESHOLD/2.0)
		{
			move(-PULSE_DRIVE_SPD, PULSE_DIST_POSITION);
			startTime = TimeNow();
		}
		Sleep(25);
    }
}

void check_y_plus(float y_coordinate) //using RPS while robot is in the +y direction
{
    float startTime = TimeNow();
    while(TimeNow() - startTime < CHECK_SLEEP || !RPSDetected())
    {
		if(RPSDropped()) return;
		
		if(getRobotY() > y_coordinate + POSITION_THRESHOLD/2.0)
		{
			move(-PULSE_DRIVE_SPD, PULSE_DIST_POSITION);
			startTime = TimeNow();
		}
		else if(getRobotY() < y_coordinate - POSITION_THRESHOLD/2.0)
		{
			move(PULSE_DRIVE_SPD, PULSE_DIST_POSITION);
			startTime = TimeNow();
		}
		Sleep(25);
    }
}


void check_y(float y_coordinate)
{
	if(RPSDropped()) return;
	
    if (RPS.Heading() < 180)
    {
        check_y_plus(y_coordinate);
    }else{
        check_y_minus(y_coordinate);
    }
}


void check_x(float x_coordinate)
{
	if(RPSDropped()) return;
	
    if (RPS.Heading() > 90 && RPS.Heading() < 270)
    {
        check_x_minus(x_coordinate);
    }else{
        check_x_plus(x_coordinate);
    }
}

bool isLeft(Vect v1, Vect v2)
{
    if(v1.x == 0 && v2.x == 0)
    {
        return v2.y > v1.y;
    }

    float det = v1.x*v2.y - v2.x*v1.y;
    if (det < 0) return true;
    if (det > 0) return false;

    float d1 = v1.x*v1.x + v1.y*v1.y;
    float d2 = v2.x*v2.x + v2.y*v2.y;
    return d1 > d2;
}


void updateVector(Vect *v, float angle)
{
    v->x = cos(angle*PI/180);
    v->y = sin(angle*PI/180);
}

float dot(Vect v1, Vect v2) {
    return v1.x*v2.x + v1.y*v2.y;
}

void check_heading(float targetHeading)
{
    if(RPSDropped()) return;
	
	float RPSHeading = RPS.Heading();
    Vect th;
    th.x = cos(targetHeading*PI/180);
    th.y = sin(targetHeading*PI/180);
    Vect rh;
    rh.x = cos(RPSHeading*PI/180);
    rh.y = sin(RPSHeading*PI/180);

	float startTime = TimeNow();
    while (TimeNow() - startTime < CHECK_SLEEP || !RPSDetected())
    {
		Sleep(50);
		if(RPSDropped()) return;

		RPSHeading = RPS.Heading();
		rh.x = cos(RPSHeading*PI/180);
		rh.y = sin(RPSHeading*PI/180);
		
		if(1-dot(th,rh) > HEADING_THRESHOLD)
		{
			startTime = TimeNow();
			if (isLeft(rh, th))
			{
                turn_right(PULSE_DRIVE_SPD, PULSE_DIST_HEADING);
			}
			else
			{
                turn_left(PULSE_DRIVE_SPD, PULSE_DIST_HEADING);
			}
		}
    }
}




#endif // DRIVEANDNAVIGATION_H
