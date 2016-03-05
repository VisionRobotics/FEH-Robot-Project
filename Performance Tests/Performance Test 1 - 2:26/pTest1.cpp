/*
 *  This program was used for performance test 1 on 2/26/16.
 *  Course strategy: move forward, turn left, drive up ramp at high speed.
 */

#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>

#define LIGHT_THRESH .45 //Vaules below this correspond to a detected start light
#define DEFAULT_SPD 30  //Standard driving speed, 30% power
#define TURBO_SPD 60   //For driving up the ramp

//Motors
FEHMotor right_motor(FEHMotor::Motor0, 12.0);
FEHMotor left_motor(FEHMotor::Motor1, 12.0);

//Encoders
DigitalEncoder right_encoder(FEHIO::P3_0);
DigitalEncoder left_encoder(FEHIO::P0_0);

//Button board
ButtonBoard buttons(FEHIO::Bank1);

//cds cell
AnalogInputPin sensor(FEHIO::P2_7);

void move_forward(int percent, double inch)
{
    double INCH_TO_COUNTS = 40.48905172;
    double counts = inch * INCH_TO_COUNTS;

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(-percent);
    left_motor.SetPercent(percent*.97); //left motor runs slightly stronger

    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}
void move_backward(int percent, double inch)
{
    double INCH_TO_COUNTS = 40.48905172;
    double counts = inch * INCH_TO_COUNTS;

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(-percent*.97);

    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}
void turn_right(int percent, int degrees)
{
    double counts = degrees * 4.8777777;

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
void turn_left(int percent, int degrees)
{
    double counts = degrees * 4.8777777;

    //Reset encoder counts
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    left_motor.SetPercent(-percent);

    //While the count from the left encoder is less than total count,
    //keep running motors
    while((left_encoder.Counts()) < counts);

    //Turn off motors
    left_motor.Stop();

}

int light_on(double cdsValue) //Dectects if any light is on
{
    return (cdsValue < LIGHT_THRESH);
}

int main(void)
{

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

    LCD.WriteLine("Waiting to be placed in start area");
    Sleep(3.0);

    LCD.WriteLine("Deploying");
    LCD.WriteLine("Waiting for light...");

    float startTime = TimeNow();
    while (!light_on(sensor.Value()))
    {
        if (TimeNow() - startTime > 10) //Deploying anyway after 10 seconds
        {
            LCD.WriteLine("Light not detected. Starting anway");
            break;
        }
        if (buttons.MiddlePressed())
            break;
    }

    move_forward(DEFAULT_SPD, 23.5); //inches
    LCD.WriteLine("Foward 17 inches");
    Sleep(600);

    turn_left(DEFAULT_SPD, 58); //58 degrees towards ramp
    LCD.WriteLine("Turning left 58 degrees");
    Sleep(600);

    Sleep(1.5);
    LCD.WriteLine("LET'S DO THIS SHIT!");
    move_forward(TURBO_SPD, 150); //TORA TORA TORA (up the ramp)

    Sleep(6.0);

    return 0;
}

