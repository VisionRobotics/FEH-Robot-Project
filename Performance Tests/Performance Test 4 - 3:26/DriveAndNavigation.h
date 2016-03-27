#ifndef DRIVEANDNAVIGATION_H
#define DRIVEANDNAVIGATION_H

#include <FEHRPS.h>
#include <math.h>
#include <EquipmentDeclarations.h>
#include <SensorUtility.h>

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
        while(currentTime-startTime < delayTime)
        {
            currentTime = TimeNow();
            multiplier = (currentTime-startTime)/delayTime;
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


void move(float percent, float inch) //Moves inputted inches
{
    double counts = inch * INCH_TO_COUNTS;

    if(inch < 0)
    {
        inch = -inch;
        percent = -percent;
    }

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
}
void move(float inch)
{
    move(DRIVE_SPD, inch);
}

void move_sleep(float percent, float inch)
{
    move(percent, inch);
    Sleep(DFT_SLEEP);
}
void move_sleep(float inch)
{
    move_sleep(DRIVE_SPD, inch);
}

void turn_right(float percent, float degrees)
{
    double counts = degrees * DEGREES_TO_COUNTS;

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    rightSetPercent(percent);
    leftSetPercent(-percent);

    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);


    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}
void turn_right(float degrees)
{
    turn_right(DRIVE_SPD, degrees);
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

void turn_left(float percent, float degrees)
{
    double counts = degrees * DEGREES_TO_COUNTS;

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    rightSetPercent(-percent);
    leftSetPercent(percent);

    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}
void turn_left(float degrees)
{
    turn_left(DRIVE_SPD, degrees);
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

//RPS Stuff (bound to change)
void check_x_minus(float x_coordinate) //using RPS while robot is in the +x direction
{
    //check whether the robot is within an acceptable range
    while(RPS.X() < x_coordinate - 1 || RPS.X() > x_coordinate + 1)
    {
        if(RPS.X() > x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            move(PULSE_DRIVE_SPD, PULSE_DIST);

        }
        else if(RPS.X() < x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            move(-PULSE_DRIVE_SPD, PULSE_DIST);

        }

        Sleep(25);
    }
}

void check_x_plus(float x_coordinate) //using RPS while robot is in the +x direction
{
    //check whether the robot is within an acceptable range
    while(RPS.X() < x_coordinate - 1 || RPS.X() > x_coordinate + 1)
    {
        if(RPS.X() > x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            move(-PULSE_DRIVE_SPD, PULSE_DIST);

        }
        else if(RPS.X() < x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            move(PULSE_DRIVE_SPD, PULSE_DIST);

        }

        Sleep(25);
    }
}

void check_y_minus(float y_coordinate) //using RPS while robot is in the -y direction
{
    LCD.WriteLine("Checking y minus");
    //check whether the robot is within an acceptable range
    while(RPS.Y() < y_coordinate - 1 || RPS.Y() > y_coordinate + 1)
    {
        if(RPS.Y() > y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            move(PULSE_DRIVE_SPD, PULSE_DIST);
        }
        else if(RPS.Y() < y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            move(-PULSE_DRIVE_SPD, PULSE_DIST);
        }

        Sleep(25);
    }
}

void check_y_plus(float y_coordinate) //using RPS while robot is in the +y direction
{
    LCD.WriteLine("Checking y plus");

    //check whether the robot is within an acceptable range
    while(RPS.Y() < y_coordinate - 1 || RPS.Y() > y_coordinate + 1)
    {
        if(RPS.Y() > y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            move(-PULSE_DRIVE_SPD, PULSE_DIST);

        }
        else if(RPS.Y() < y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            move(PULSE_DRIVE_SPD, PULSE_DIST);

        }

        Sleep(25);
    }
}
void check_x_minus_sleep(float x_coordinate)
{
    check_x_minus(x_coordinate);
    Sleep(DFT_SLEEP);
}
void check_x_plus_sleep(float x_coordinate)
{
    check_x_plus(x_coordinate);
    Sleep(DFT_SLEEP);
}

void check_y_minus_sleep(float y_coordinate)
{
    check_y_minus(y_coordinate);
    Sleep(DFT_SLEEP);
}
void check_y_plus_sleep(float y_coordinate)
{
    check_y_plus(y_coordinate);
    Sleep(DFT_SLEEP);
}

void check_y(float y_coordinate)
{
    if (RPS.Heading() < 180)
    {
        check_y_plus(y_coordinate);
    }else{
        check_y_minus(y_coordinate);
    }
}
void check_y_sleep(float y_coordinate)
{
    check_y(y_coordinate);
    Sleep(DFT_SLEEP);
}

void check_x(float x_coordinate)
{
    if (RPS.Heading() > 90 && RPS.Heading() < 270)
    {
        check_x_minus(x_coordinate);
    }else{
        check_x_plus(x_coordinate);
    }
}
void check_x_sleep(float x_coordinate)
{
    check_x(x_coordinate);
    Sleep(DFT_SLEEP);
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
    //LCD.WriteLine("Checking heading");
    float RPSHeading = RPS.Heading();

    //Directional unit vector for targetHeading and RPSHeading
    Vect th;
    th.x = cos(targetHeading*PI/180);
    th.y = sin(targetHeading*PI/180);
    Vect rh;
    rh.x = cos(RPSHeading*PI/180);
    rh.y = sin(RPSHeading*PI/180);

    while (1-dot(th,rh) > headingThreshold)
    {
        if (isLeft(rh, th))
        {
            turn_right(PULSE_DRIVE_SPD, PULSE_DIST);
        }
        else
        {
            turn_left(PULSE_DRIVE_SPD, PULSE_DIST);
        }

        Sleep(50);
        RPSHeading = RPS.Heading();
        rh.x = cos(RPSHeading*PI/180);
        rh.y = sin(RPSHeading*PI/180);

    }
}
void check_heading_sleep(float targetHeading)
{
    check_heading(targetHeading);
    Sleep(50);
}

#endif // DRIVEANDNAVIGATION_H
