#ifndef CONSTANTS_H
#define CONSTANTS_H

#define PI 3.14159265358979323846

//Conversion constants
#define INCH_TO_COUNTS 40.48905172
#define DEGREES_TO_COUNTS 2.43888


//Useful sleep times (int = milliseconds float = seconds)
#define DFT_SLEEP 50 //was 75
#define CHECK_SLEEP 0.1
#define FUEL_LIGHT_READ_TIME 0.25 //WAS 0.5
#define RPS_TIMEOUT_DURATION 0.6
#define ENCODER_TIMEOUT 4


//Drive utility  
#define END_BUTTON_SPD 70
#define DOWN_RAMP_SPD 39
#define DRIVE_SPD 45
#define TURN_SPD 45
#define SWITCH_FLIP_SPD 26
#define DEPOSIT_SPD 26
#define SLOW_SPD 20
#define PULSE_DRIVE_SPD 15
#define PULSE_DIST_POSITION 0.10 //inches (was 0.25)
#define PULSE_DIST_HEADING 0.41 //degree (was 0.82)
#define SPEED_THRESHOLD 4 //inches to drive


//RPS
#define HEADING_THRESHOLD 0.000152 //+/- 1 degrees
#define POSITION_THRESHOLD 0.5 //+-0.25
#define DELAY_TIME 0.5
#define EXPECTED_RPS_START_X 10.25 
#define EXPECTED_RPS_START_Y 10.5
#define RPS_ERROR -1
#define RPS_DEAD_ZONE -2


//CdS cell thresholds
#define LIGHT_THRESH .6 //For detecting start light
#define BLUE_THRESH .4
#define RED_THRESH .15
#define COLOR_THRESH .35


//Arm angles
//Min and max angles for both arms
#define LASSO_MIN 680
#define LASSO_MAX 2400
#define P_ARM_MIN 535
#define P_ARM_MAX 1840

//Angles for each arm position
#define LASSO_UP 180
#define LASSO_MID 87
#define LASSO_ERROR_REPORT 140
#define LASSO_DOWN 12
#define P_ARM_UP 42 
#define P_ARM_DOWN 148
#define P_ARM_DEPOSIT 132


#endif // CONSTANTS_H
