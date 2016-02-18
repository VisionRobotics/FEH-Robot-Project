#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHServo.h>
#include <FEHRPS.h>
#include <FEHMotor.h>

int main(void)
{
    LCD.Clear(FEHLCD::Black);
    LCD.SetFontColor(FEHLCD::White);

    /* Light sensors and servo motor

    AnalogInputPin sensor(FEHIO::P0_0); //Light sensor
    FEHServo arm(FEHServo::Servo7);

    //arm.TouchCalibrate(); FEH program used to find the min and max values
    arm.SetMin(500);
    arm.SetMax(2432);


    while (true){
        double CdsValue = sensor.Value();
        LCD.WriteLine(CdsValue);
        Sleep( 100 );

        arm.SetDegree(CdsValue/3.3 * 180);
    }

    */

    
    //Obstacle course

    //Declaring motors
    FEHMotor rightdrive(FEHMotor::Motor0, 12.0);
    FEHMotor leftdrive(FEHMotor::Motor1, 12.0);

    //Declaring microswitches
    DigitalInputPin microFrontRight(FEHIO::P2_0);
    DigitalInputPin microFrontLeft(FEHIO::P2_1);
    DigitalInputPin microBackRight(FEHIO::P2_3);
    DigitalInputPin microBackLeft(FEHIO::P2_2);

    
    //Part 1
    LCD.WriteLine("Part 1");
    rightdrive.SetPercent(30);
    leftdrive.SetPercent(30);

    while (microFrontLeft.Value() || microFrontRight.Value());
    
    rightdrive.SetPercent(0);
    leftdrive.SetPercent(0);
    Sleep(2.0);


    //Part 2
    LCD.WriteLine("Part 2");
    rightdrive.SetPercent(-30);
    leftdrive.SetPercent(-10);

    while (microBackLeft.Value() || microBackRight.Value());
    
    rightdrive.SetPercent(0);
    leftdrive.SetPercent(0);
    Sleep(2.0);

    //Part 3
    LCD.WriteLine("Part 3");
    rightdrive.SetPercent(30);
    leftdrive.SetPercent(30);

    while (microFrontLeft.Value() || microFrontRight.Value());
    
    rightdrive.SetPercent(0);
    leftdrive.SetPercent(0);
    Sleep(2.0);


    //Part 4
    LCD.WriteLine("Part 4");
    rightdrive.SetPercent(-1);
    leftdrive.SetPercent(-30);

    while (microBackLeft.Value() || microBackRight.Value());
    
    rightdrive.SetPercent(0);
    leftdrive.SetPercent(0);
    Sleep(2.0);


    //Part 5
    LCD.WriteLine("Part 5");
    rightdrive.SetPercent(30);
    leftdrive.SetPercent(30);

    while (microFrontLeft.Value() || microFrontRight.Value());
    
    rightdrive.SetPercent(0);
    leftdrive.SetPercent(0);
    Sleep(2.0);

    return 0;
}

