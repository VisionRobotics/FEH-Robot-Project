#ifndef COMPLETEDRIVING_H
#define COMPLETEDRIVING_H

#include <SleepyDriving.h>
#include <SensorUtility.h>

void driveToX(float expectedDistance, float x)
{
    LCD.Write("Driving to x = ");
    LCD.WriteLine(x);
    float speed = DRIVE_SPD;
    if(abs(expectedDistance) <= SPEED_THRESHOLD) speed = SLOW_SPD;
    move_sleep(speed, expectedDistance);
    check_x(x);
}

void driveToXRPS(float x)
{
    LCD.Write("(RPS) Driving to x = ");
    LCD.WriteLine(x);
    if(RPSDropped()) return;

    if (RPS.Heading() > 90 && RPS.Heading() < 270)
    {
        float expectedDistance = getRobotX()-x;
        float speed = DRIVE_SPD;
        if(abs(expectedDistance) <= SPEED_THRESHOLD) speed = SLOW_SPD;
        move_sleep(speed, expectedDistance);
    }
    else
    {
        float expectedDistance = x-getRobotX();
        float speed = DRIVE_SPD;
        if(abs(expectedDistance) <= SPEED_THRESHOLD) speed = SLOW_SPD;
        move_sleep(speed, expectedDistance);
    }
    check_x(x);
}

void confirmX(float x)
{
    LCD.Write("Confirming x = ");
    LCD.WriteLine(x);
    check_x(x);
}

void driveToY(float expectedDistance, float y)
{
    LCD.Write("Driving to y = ");
    LCD.WriteLine(y);
    float speed = DRIVE_SPD;
    if(abs(expectedDistance) <= SPEED_THRESHOLD) speed = SLOW_SPD;
    move_sleep(speed, expectedDistance);
    check_y(y);
}

void driveToYRPS(float y)
{
    LCD.Write("(RPS) Driving to y = ");
    LCD.WriteLine(y);
    if(RPSDropped()) return;

    if (RPS.Heading() < 180)
    {
        float expectedDistance = y-getRobotY();
        float speed = DRIVE_SPD;
        if(abs(expectedDistance) <= SPEED_THRESHOLD) speed = SLOW_SPD;
        move_sleep(speed, expectedDistance);
    }
    else
    {
        float expectedDistance = getRobotY()-y;
        float speed = DRIVE_SPD;
        if(abs(expectedDistance) <= SPEED_THRESHOLD) speed = SLOW_SPD;
        move_sleep(speed, expectedDistance);
    }
    LCD.WriteLine(getRobotY()-y);
    check_y(y);
}

void confirmY(float y)
{
    LCD.Write("Confirming y = ");
    LCD.WriteLine(y);
    check_y(y);
}

void turnToHeading(float expectedTurn, float heading)
{
    LCD.Write("Turning to ");
    LCD.Write(heading);
    LCD.WriteLine(" degrees");
    turn_sleep(expectedTurn);
    check_heading(heading);
}

void confirmHeading(float heading)
{
    LCD.Write("Confirming ");
    LCD.Write(heading);
    LCD.WriteLine(" degrees");
    check_heading(heading);
}


void climbRamp(int count)
{
    if(count >= 30)
    {
        LCD.WriteLine("!!!!Failed ramp!!!!");
        lasso.SetDegree(LASSO_ERROR_REPORT);
        return;
    }
    count++;

    LCD.WriteLine("Up the ramp!!");
    move_sleep(2*DRIVE_SPD, 30);
    Sleep(100);

    bool detected = RPSDetected();
    if(detected && getRobotY() >= 37) return; //was 28

    if(!detected) return;

    if(detected)
    {
        driveToYRPS(24);
        confirmHeading(90);
        turnToHeading(90, 0);
        driveToXRPS(27.3);
        turnToHeading(-93, 93);
    }
    if(!detected)
    {
        LCD.WriteLine("!!!!Failed ramp!!!!");
        lasso.SetDegree(LASSO_ERROR_REPORT);
    }
    climbRamp(count);
}
void climbRamp()
{
    climbRamp(0);
}

void flipSwitch(int direction)
{
    lasso.SetDegree(LASSO_MID);
    Sleep(400);
    //states here
    move(SWITCH_FLIP_SPD, -1.5*direction, 1); //$//Probably can be even lower than 1 second
    Sleep(300);
    lasso.SetDegree(LASSO_UP);
    Sleep(300);
    move(SWITCH_FLIP_SPD, 1.5*direction, 1);
    Sleep(100);
}

#endif // COMPLETEDRIVING_H
