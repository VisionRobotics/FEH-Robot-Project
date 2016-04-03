#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <Constants.h>
#include <EquipmentDeclarations.h>
#include <SensorUtility.h>
#include <SleepyDriving.h>
#include <BetterDriving.h>
/*
To Do:
-Diagnal drives/fewer steps
-Slow at end of encoder drives
-Reduce uneeded checks
-Dropoff payload
-2 more switches

-timer timeouts on encoder checks <-- check for sure??
-increase color_thres?
-log RPS
-have the move forwards count each encoder
*/
int main(void)
{
   initialize_robot();

   /*
   while (!microBackLeft.Value())
   {
       LCD.Clear();
       LCD.Write(RPS.X());
       LCD.Write("  ");
       LCD.WriteLine(RPS.Y());
       LCD.WriteLine(is_red());
   } */

   wait_for_start_light(32);
   calculateRobotOffset();
   /*
   while (!microBackLeft.Value())
   {
       LCD.Clear();
       LCD.Write(RPSOffsetX);
       LCD.Write("  ");
       LCD.WriteLine(RPSOffsetY);
   } */


   //*Go to payload*//
                            //(10.25,10.5) Angle ~ 0
   confirmHeading(0); 		  //(?,?) Angle = 0
   driveToX(9, 20.25); 	    //(20.25,?) Angle = 0
   turnToHeading(-90, 90);	//(20.25,?) Angle = 90
   driveToY(6.5, 17);			  //(20.25,17) Angle = 90
							              //Coordinates located
   turnToHeading(90, 0);	  //(20.25,17) Angle = 0
   driveToX(7.15, 27.4);	  //(27.4,17) Angle = 0
   turnToHeading(90, 270);  //(27.4,17) Angle = 270

   //*Payload Pickup*//
   lowerPArm();
   driveToY(0.5, 16.25);		//(27.4,16.25) Angle = 270
   confirmHeading(270);		  //(27.4,16.25) Angle = 270
   LCD.WriteLine("Moving forward for pickup");
   move_sleep(3.2);			    //(27.4,13.05) Angle = 270
   raisePArm();
   driveToY(-3.95, 17);	    //(27.4,17) Angle = 270


   //*Go up ramp*//
   turnToHeading(-180, 90);	//(27.4,17) Angle = 90
   driveToY(8, 24);		    	//(27.4,24) Angle = 90
   confirmHeading(90);      //(27.4,24) Angle = 90
   turnToHeading(90, 0);    //(27.4,24) Angle = 0
   driveToXRPS(26.6);       //(26.6,24) Angle = 90
   turnToHeading(-93, 93);	//(26.6,24) Angle = 93

   climbRamp();
                            //(?,?) Angle = ?

   //*Go to buttons*//
   turnToHeading(90, 0);    //(?,?) Angle = 0
   confirmX(27.6);			    //(27.6, ?) Angle = 0
   turnToHeading(90, 270);  //(27.6, ?) Angle = 270

   driveToYRPS(55);         //(27.6, 55) Angle = 270
   confirmHeading(270);		  //(27.6, 55) Angle = 270
   driveToY(-3.6, 58.6);	  //(27.6, 58.6) Angle = 270
   confirmHeading(270);	    //(27.6, 58.6) Angle = 270
   driveToY(-3.6, 62.2);	  //(27.6, 62.2) Angle = 270
   confirmHeading(270);		  //(27.6, 62.2) Angle = 270

   //Button actions*//
   if(is_red())
   {
	     driveToY(5, 57.5);
       confirmHeading(270);

       lasso.SetDegree(LASSO_DOWN);
       Sleep(500);

	     driveToY(-2.5, 60);
       confirmHeading(270);

       pressButton();

       driveToY(2.5, 57.7);
       confirmHeading(270);

       lasso.SetDegree(LASSO_UP);
       Sleep(500);
   }
   else
   {
       pressButton();

       driveToY(2.5, 60);	  //(27.6, 60) Angle = 270
       confirmHeading(270); //(27.6, 60) Angle = 270
       driveToY(2.5, 57.7); //(27.6, 57.7) Angle = 270
       confirmHeading(270); //(27.6, 57.7) Angle = 270
   }

   //*Go to switches*//
   driveToY(6.45, 51.25);   //(27.6, 51.25) Angle = 270
   confirmHeading(270); 	  //(27.6, 51.25) Angle = 270
   turnToHeading(-90, 0);   //(27.6, 51.25) Angle = 0
   driveToX(-3.6, 24.2);    //(24.2, 51.25) Angle = 0
   turnToHeading(90, 270);  //(24.2, 51.25) Angle = 270
   driveToY(4.25, 47);      //(24.2, 47) Angle = 270
   confirmHeading(270); 	  //(24.2, 47) Angle = 270
   turnToHeading(90, 180);  //(24.2, 47) Angle = 180
   driveToX(6.85, 17.35);   //(17.35, 47) Angle = 180
   confirmHeading(180); 	  //(17.35, 47) Angle = 180
   driveToX(3.35, 13.75);   //(13.75, 47) Angle = 180
   confirmHeading(180); 	  //(13.75, 47) Angle = 180
   turnToHeading(90, 90);   //(13.75, 47) Angle = 90

   //*Flip switch*//
   confirmHeading(90);      //(13.75, 47) Angle = 90
   lasso.SetDegree(LASSO_MID);
   Sleep(1000);
   //states here
   move(0.75*DRIVE_SPD, -1.6*rightSwitchDirection());
   Sleep(1000);
   lasso.SetDegree(LASSO_UP);
   Sleep(1000);
   move(0.75*DRIVE_SPD, 1.6*rightSwitchDirection());
   Sleep(600);

   //*Move to lower level*//
   turnToHeading(90, 0);    //(13.75, 47) Angle = 0
   driveToX(8.85, 19.35);   //(19.35, 47) Angle = 0
   confirmHeading(0);       //(19.35, 47) Angle = 0
   driveToX(8.65, 27.6);    //(27.6, 47) Angle = 0
   confirmHeading(0);       //(27.6, 47) Angle = 0
   turnToHeading(-90, 90);  //(27.6, 47) Angle = 90

   lowerPArm();
   Sleep(400);
   raisePArm();

   move_sleep(-1.1*DRIVE_SPD, 27);

   //*Going to end button*//
   driveToYRPS(23);			    //(?, 23) Angle = 270
   turnToHeading(-90, 180);	//(?, 23) Angle = 180
   driveToXRPS(27.5);		    //(27.5, 23) Angle = 180
   driveToX(3.5, 24);	      //(24, 23) Angle = 180
   turnToHeading(135, 45);	//(24, 23) Angle = 45

   LCD.WriteLine("plsssss");
   move_indef(-2*DRIVE_SPD);
   return 0;
}
