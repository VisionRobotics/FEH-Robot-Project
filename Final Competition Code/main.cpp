#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <Constants.h>
#include <EquipmentDeclarations.h>
#include <SensorUtility.h>
#include <CompleteDriving.h>

int main(void)
{
   initialize_robot();
   print_useful_info();
   while (!microBackLeft.Value()); //Waiting for final action

   wait_for_start_light(34);
   calculateRobotOffset();

   //Go to payload//            //(10.25,10.5) Angle ~ 0
   turn_sleep(-20, 20);         //(?,?) Angle ! 20
   move_sleep(18.25);
   turnToHeading(20, 0);		  //(?,?) Angle = 0
   driveToXRPS(27.35);			  //(27.35,?) Angle = 0  TRYING RPS HERE
   turnToHeading(90, 270);      //(27.35,?) Angle = 270
   lowerPArm();
   Sleep(250);
   driveToYRPS(17);             //(?,17) Angle = 270  TRYING RPS HERE

   //Payload Pickup//           //Coordinates located
   confirmHeading(270);		     //(27.35,17) Angle = 270
   LCD.WriteLine("Moving forward for pickup");
   move_sleep(3.2);			     //(27.35,13.8) Angle = 270
   raisePArm();
   driveToY(-3.2, 17);	         //(27.35,17) Angle = 270

   //Go up ramp//
   turnToHeading(-183, 87);	  //(27.35,17) Angle = 87
   driveToY(8, 24);		        //(27.35,24) Angle = 87
   turnToHeading(-4, 93);       //(27.35,24) Angle = 93

   climbRamp();

   //Go to buttons//            //(?,?) Angle = ?
   confirmHeading(93);          //(?,?) Angle = 93
   driveToYRPS(58);             //(?, 58) Angle = 93
   turnToHeading(90, 0);        //(?, 58) Angle = 0

   if(!RPSDetected())
   {
       move(1);
       confirmHeading(0);
   }

   confirmX(27.95);			   //(27.95, 58) Angle = 0
   turnToHeading(90, 270);    //(27.95, 58) Angle = 270
   driveToYRPS(62.2);         //(27.95, 62.2) Angle = 270
   confirmHeading(270);		  	//(27.95, 62.2) Angle = 270

   //Button actions//
   if(is_red())
   {
       driveToY(3, 59.2);
       confirmHeading(268);
       lasso.SetDegree(LASSO_DOWN);
       Sleep(500);

       pressButton();

       move(getRobotY()-56);
       lasso.SetDegree(LASSO_UP);
       Sleep(DFT_SLEEP);
       check_y(56);
   }
   else
   {
       pressButton();
       driveToYRPS(56); 		//(27.95, 56) Angle = 270 //$//TRYING RPS HERE
   }

   //Go to right switch//
   turnToHeading(57, 213);		    //(27.95, 56) Angle = 213
   move_sleep(16.517);			    //(~14.3, ~43.4) Angle = 265
   turnToHeading(33, 180);        //(~14.3, ~43.4) Angle = 270
   driveToXRPS(14.3);      	    //(14.3, 43.4) Angle = 180
   turnToHeading(90, 90);         //(14.3, 43.4) Angle = 90
   flipSwitch(rightSwitchDirection());

   //Go to middle switch//
   turnToHeading(-85, 175);  	   //(14.3, 43.4) Angle = 175
   move_sleep(4.5);           	//(9.75, 43.4) Angle = 175
   turn_sleep(85);            	//(9.75, 43.4) Angle = 90
   confirmHeading(90);
   flipSwitch(middleSwitchDirection());

   //Go to left switch//
   turn_sleep(-90);          	   //(9.75, 43.4) Angle = 180
   move_sleep(4.4);           	//(5.75, 43.4) Angle = 180
   turn_sleep(93);            	//(5.75, 43.4) Angle = 87
   confirmHeading(87);
   flipSwitch(leftSwitchDirection());
   turn_sleep(12);          	   //(5.75, 43.4) Angle = 75
   move(2.2);
   turn_sleep(-23);

   //Deposit supplies//
   move_sleep(6);
   depositPArm();
   Sleep(400);
   move_sleep(-DEPOSIT_SPD, 5.75);
   raisePArm();

   //Move to lower level//
   turn_sleep(90);    			   //(5.75, 43.4) Angle = 0
   driveToX(25.5, 27.6);   		//(5.75, 43.4) Angle = 0
   turnToHeading(-85, 90);  	   //(27.6, 43.4) Angle = 90

   move_sleep(-DOWN_RAMP_SPD, 26);

   //Going to end button//
   driveToYRPS(21);         	   //(?, 21) Angle = 270
   turn_sleep(-90);              //(?, 21) Angle = 180
   move_sleep(getRobotX()-24);   //(24, 21) Angle = 180
   turnToHeading(-44, 227);		//(24, 21) Angle = 227

   LCD.WriteLine("plsssss");
   move_indef(END_BUTTON_SPD);
   return 0;
}
