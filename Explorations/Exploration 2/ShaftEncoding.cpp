/*
    Exploration 2: Running a course using shaft encoding only
*/
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>

//Declarations for encoders & motors
ButtonBoard buttons(FEHIO::Bank3);
DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_1);
FEHMotor right_motor(FEHMotor::Motor0,12.0);
FEHMotor left_motor(FEHMotor::Motor1,12.0);

void move_forward(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);

    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}
void turn_right(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();


    //Set both motors to desired percent
    right_motor.SetPercent(percent);

    //While the count from the right encoder is less than total count,
    //keep running motors
    while((right_encoder.Counts()) < counts);

    //Turn off motors
    right_motor.Stop();

}
void turn_left(int percent, int counts) //using encoders
{
    //Reset encoder counts
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    left_motor.SetPercent(percent);

    //While the count from the left encoder is less than total count,
    //keep running motors
    while((left_encoder.Counts()) < counts);

    //Turn off motors
    left_motor.Stop();

}


int main(void)
{
    int motor_percent = 15; //Input power level here
    int expected_counts = 567; //Input theoretical counts here

    //Initialize the screen (GO BUCKS!)
    LCD.Clear( FEHLCD::Scarlet );
    LCD.SetFontColor( FEHLCD::Gray );

    LCD.WriteLine("Shaft Encoder Lab Test");
    LCD.WriteLine("Press middle button");
    while(!buttons.MiddlePressed()); //Wait for middle button to be pressed
    while(buttons.MiddlePressed()); //Wait for middle button to be unpressed

    move_forward(motor_percent, expected_counts); 

    Sleep(2.0); //Wait for counts to stabilize

    turn_left(motor_percent, 439);
    Sleep(2.0);

    move_forward(motor_percent, 405);
    Sleep(2.0);

    turn_right(motor_percent, 439);
    Sleep(2.0);


    move_forward(motor_percent, 162);


    //Print out data
    LCD.Write("Theoretical Counts: ");
    LCD.WriteLine(expected_counts);
    LCD.Write("Motor Percent: ");
    LCD.WriteLine(motor_percent);
    LCD.Write("Actual LE Counts: ");
    LCD.WriteLine(left_encoder.Counts());
    LCD.Write("Actual RE Counts: ");
    LCD.WriteLine(right_encoder.Counts());

    return 0;
}
