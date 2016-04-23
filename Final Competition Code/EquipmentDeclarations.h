/*  This file declares all the motors, tools and sensors connected to the Proteus.
    Make sure everything is plugged into the right ports! */

#ifndef EQUIPMENTDECLARATIONS_H
#define EQUIPMENTDECLARATIONS_H

#include <FEHMotor.h>
#include <FEHServo.h>
#include <FEHRPS.h>

//Motors
FEHMotor right_motor(FEHMotor::Motor0, 12.0);
FEHMotor left_motor(FEHMotor::Motor1, 12.0);

//Encoders
DigitalEncoder right_encoder(FEHIO::P3_2);
DigitalEncoder left_encoder(FEHIO::P0_0);

//Bump switches
DigitalInputPin microBackRight(FEHIO::P3_0);
DigitalInputPin microBackLeft(FEHIO::P0_7);

//CdS Cell
AnalogInputPin sensor(FEHIO::P2_7);

//Lasso
FEHServo lasso(FEHServo::Servo7);

//Payload arm
FEHServo pArm(FEHServo::Servo0);

void setup_lasso()
{
    lasso.SetMin(LASSO_MIN);
    lasso.SetMax(LASSO_MAX);
    lasso.SetDegree(LASSO_UP);
}

void setup_pArm()
{
    pArm.SetMin(P_ARM_MIN);
    pArm.SetMax(P_ARM_MAX);
    pArm.SetDegree(P_ARM_UP);
}

void raisePArm()
{
	LCD.WriteLine("Raising payload arm");
	pArm.SetDegree(P_ARM_UP);
}
void lowerPArm()
{
	LCD.WriteLine("Lowering payload arm");
	pArm.SetDegree(P_ARM_DOWN);
}

//Places arm in the payload deposit angle
void depositPArm()
{
    LCD.WriteLine("Lowering payload arm");
    pArm.SetDegree(P_ARM_DEPOSIT);
}

void initialize_robot()
{
    setup_lasso();
    setup_pArm();
    lasso.SetDegree(LASSO_UP);
    pArm.SetDegree(P_ARM_UP);

    RPS.InitializeTouchMenu();
}

#endif // EQUIPMENTDECLARATIONS_H
