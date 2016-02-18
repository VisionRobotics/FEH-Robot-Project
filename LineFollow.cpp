/*
    Exploration 2: Code for line following using three optosensor system 
*/

#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>

#define ON_LEFT 0
#define ON_MIDDLE 1
#define ON_RIGHT 2

#define MAX_SPEED 15
#define VOLT_THRESH 1.9

//returns true if sensor reading is above threshold
bool isOnLine(double value)
{
    return (value >= VOLT_THRESH);
}

int main(void)
{
    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

    //Line sensors
    AnalogInputPin right_opt(FEHIO::P1_0);
    AnalogInputPin middle_opt(FEHIO::P1_1);
    AnalogInputPin left_opt(FEHIO::P1_2);

    //Motors
    FEHMotor rightDrive(FEHMotor::Motor3, 12.0);
    FEHMotor leftDrive(FEHMotor::Motor2, 12.0);

    while (true)
    {
        int position = ON_MIDDLE;

        //Getting input from sensors
        double left = left_opt.Value();
        double right = right_opt.Value();
        double middle = middle_opt.Value();

        //Determining position on line
        if (isOnLine(middle)){
            position = ON_MIDDLE;
        }

        if (isOnLine(left)){
            position = ON_LEFT;
        }

        if (isOnLine(right)){
            position = ON_RIGHT;
        }

       //Powering motors accordingly
       switch(position)
        {
        case (ON_MIDDLE):
            rightDrive.SetPercent(MAX_SPEED);
            leftDrive.SetPercent(MAX_SPEED);
            break;

        case (ON_LEFT):
            rightDrive.SetPercent(MAX_SPEED);
            leftDrive.SetPercent(MAX_SPEED*0.25);
            break;

        case(ON_RIGHT):
            rightDrive.SetPercent(MAX_SPEED*0.25);
            leftDrive.SetPercent(MAX_SPEED);
            break;
        }

        Sleep(1);
    }


    return 0;
}

