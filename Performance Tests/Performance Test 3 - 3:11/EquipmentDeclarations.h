/*  This file declares all the motors, tools and sensors connected to the Proteus.
    Make sure everything is plugged into the right ports! */

#ifndef EQUIPMENTDECLARATIONS_H
#define EQUIPMENTDECLARATIONS_H

#include <FEHMotor.h>
#include <FEHServo.h>

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
AnalogInputPin sensor(FEHIO::P2_7); //double check

//Lasso
FEHServo lasso(FEHServo::Servo7);

//Payload arm
FEHServo pArm(FEHServo::Servo0);

void setup_lasso()
{
    lasso.SetMin(680);
    lasso.SetMax(2400);
    lasso.SetDegree(LASSO_UP);
}

void setup_pArm()
{
    pArm.SetMin(535); //////
    pArm.SetMax(1840); //////
    pArm.SetDegree(P_ARM_UP);
}

#endif // EQUIPMENTDECLARATIONS_H
