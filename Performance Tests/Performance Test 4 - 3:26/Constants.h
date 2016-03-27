#ifndef CONSTANTS_H
#define CONSTANTS_H

#define DFT_SLEEP 300
#define LIGHT_THRESH .6 //Values below this correspond to a detected start light
#define BLUE_THRESH .4
#define RED_THRESH .15
#define COLOR_THRESH .3243333

#define back_up_distance 1 //change
#define push_distance .5 //change

//Min and max angles for both arms
#define LASSO_MIN 680
#define LASSO_MAX 2400
#define P_ARM_MIN 535
#define P_ARM_MAX 1840

//Angles for each arm position
#define LASSO_UP 180
#define LASSO_MID 87
#define LASSO_DOWN 12
#define P_ARM_UP 42 //?
#define P_ARM_DOWN 152 //?
#define P_ARM_DEPOSIT 130 //?

//Conversion constants
#define INCH_TO_COUNTS 40.48905172
#define DEGREES_TO_COUNTS 2.43888

#define PI 3.14159265358979323846

//Motor utility (Bound to change)
#define LEFT_MOTOR_SCALE .94
#define DRIVE_SPD 35
#define PULSE_DRIVE_SPD 15
#define PULSE_DIST 0.82 //degree

#define headingThreshold 0.000609 //+/- 2 degrees
#define delayTime 0.5


#endif // CONSTANTS_H
