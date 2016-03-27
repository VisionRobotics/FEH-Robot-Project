/*
    This program was used for Performance Test 4: reading the fuel light
    and pushing the corresponding button. 
*/
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <Constants.h>
#include <EquipmentDeclarations.h>
#include <SensorUtility.h>
#include <DriveAndNavigation.h>

/*
To Do:
-checks abort when RPS < 0
-split main into functions
-increase color_thres?
-log RPS
-PID?
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

   wait_for_start_light(7);

   ////Main routine////
   //~(10,9?) degrees ~ 0

   LCD.WriteLine("Turning to 0 degrees");
   check_heading_sleep(0);
   //(?,?) degrees = 0

   LCD.WriteLine("Driving to x = 20.5");
   move_sleep(10.5); //guessed value
   check_x_plus_sleep(20.5);
   //(20.5,?) degrees = 0

   LCD.WriteLine("Turning to 90 degrees");
   turn_left_sleep(90);
   check_heading_sleep(90);
   //(20.5,?) degrees = 90

   LCD.WriteLine("Driving to y = 17");
   move_sleep(8); //guessed value
   check_y_plus_sleep(17);
   //Coordinates located
   //(20.5,17) degrees = 90

   LCD.WriteLine("Turning to 0 degrees");
   turn_right_sleep(90);
   check_heading_sleep(0);
   //(20.5,17) degrees = 0

   LCD.WriteLine("Driving to x = 26.9");
   move_sleep(6.6);
   check_x_plus_sleep(26.9);
   //(26.9,17) degrees = 0

   LCD.WriteLine("Turning to 90 degrees");
   turn_left_sleep(90);
   check_heading_sleep(90);
   //(26.9,17) degrees = 90

   LCD.WriteLine("Driving to y = 25");
   move_sleep(8); //guessed value
   check_y_plus_sleep(25);
   //(26.9,25) degrees = 90

   LCD.WriteLine("Turning to 93 degrees");
   check_heading_sleep(93);
   //(26.9,25) degrees = 93 //used to be 27.1

   LCD.WriteLine("Up the ramp!!");
   move_sleep(2*DRIVE_SPD, 30);
   Sleep(300);
   //(?,?) degrees = ?


   LCD.WriteLine("Turning to 0 degrees");
   turn_right_sleep(90);
   check_heading_sleep(0);
   //(?,?) degrees = 0


   LCD.WriteLine("Checking x = 28.2");
   check_x_sleep(28.2);
   //(28.2, ?) Angle = 180

   LCD.WriteLine("Turning to 270 degrees");
   turn_right_sleep(90);
   check_heading_sleep(270);
   //(28.2, ?) Angle = 270

   //Scoot//
   LCD.WriteLine("Checking y = 52.5");
   move_sleep(-DRIVE_SPD, 52.5-RPS.Y()); //find correct location
   check_y_sleep(52.5);
   //(28.2, 52.5) Angle = 270

   LCD.WriteLine("Checking 270 degrees");
   check_heading_sleep(270);
   //(28.2, 52.5) Angle = 270

   LCD.WriteLine("Checking y = 55");
   move_sleep(-DRIVE_SPD, 2.5);
   check_y_sleep(55);
   //(28.2, 55) Angle = 270

   LCD.WriteLine("Checking 270 degrees");
   check_heading_sleep(270);
   //(28.2, 55) Angle = 270

   LCD.WriteLine("Checking y = 57.5");
   move_sleep(-DRIVE_SPD, 2.5);
   check_y_sleep(57.5);
   //(28.2, 57.5) Angle = 270

   LCD.WriteLine("Checking 270 degrees");
   check_heading_sleep(270);
   //(28.2, 57.5) Angle = 270

   LCD.WriteLine("Checking y = 60");
   move_sleep(-DRIVE_SPD, 2.5);
   check_y_sleep(60);
   //(28.2, 60) Angle = 270

   LCD.WriteLine("Checking 270 degrees");
   check_heading_sleep(270);
   //(28.2, 60) Angle = 270

   LCD.WriteLine("Checking y = 62.2");
   move_sleep(-DRIVE_SPD, 2.2);
   check_y_sleep(62.2);
   //(28.2, 62.2) Angle = 270

   LCD.WriteLine("Checking 270 degrees");
   check_heading_sleep(270);
   //(28.2, 62.2) Angle = 270

   //Checks light
   if(is_red())
   {
       move_sleep(5);
       check_y_sleep(57.5);
       check_heading_sleep(270);

       lasso.SetDegree(LASSO_DOWN);
       Sleep(500);

       move_sleep(-2.5);
       check_y_sleep(60);
       check_heading_sleep(270);

       move_indef(-0.6*DRIVE_SPD);
       Sleep(6.0);

       move_sleep(2.5);
       check_y_sleep(57.5);
       check_heading_sleep(270);

       lasso.SetDegree(LASSO_UP);
       Sleep(500);
   }
   else
   {
       move_indef(-0.6*DRIVE_SPD);
       Sleep(6.0);

       LCD.WriteLine("Driving to y = 60");
       move_sleep(2.5);
       check_y_sleep(60);
       check_heading_sleep(270);
       //(28.2, 60) Angle = 270

       LCD.WriteLine("Driving to y = 57.5");
       move_sleep(2.5);
       check_y_sleep(57.5);
       check_heading_sleep(270);
       //(28.2, 57.5) Angle = 270
   }

   //Backing up
   LCD.WriteLine("Driving to y = 56");
   move_sleep(1.5);
   check_y_sleep(56);
   check_heading_sleep(270);
   //(28.2, 56) Angle = 270

   LCD.WriteLine("Driving to y = 53");
   move_sleep(DRIVE_SPD, 3);
   check_y_sleep(53);
   check_heading_sleep(270);
   //(28.2, 53) Angle = 270

   LCD.WriteLine("Driving to y = 50");
   move_sleep(DRIVE_SPD, 3);
   check_y_sleep(50);
   check_heading_sleep(270);
   //(28.2, 50) Angle = 270


   LCD.WriteLine("Turning sliders toward ramp");
   turn_left_sleep(180);
   check_heading_sleep(90);
   //(28.2, ?) Angle = 90


   //Driving down
   move(-1.1*DRIVE_SPD, 27);

   //Going to button
   LCD.WriteLine("Checking y = 23");
   move_sleep(23-RPS.Y()); //find correct location
   check_y_sleep(23);
   //(?, 23) degrees = 270

   LCD.WriteLine("Turning to 180 degrees");
   turn_left_sleep(90);
   check_heading_sleep(180);
   //(?, 23) degrees = 180

   LCD.WriteLine("Checking x = 27.5");
   move_sleep(27.5-RPS.Y()); //find correct location
   check_x_sleep(27.5);
   //(27.5, 23) degrees = 180

   LCD.WriteLine("Driving to x = 24");
   move_sleep(3.5);
   check_x_sleep(24);
   //(24, 23) degrees = 180

   LCD.WriteLine("Turning to 45");
   turn_right(135);
   check_heading(45);
   //(24, 23) degrees = 45

   LCD.WriteLine("plsssss");
   move_indef(-2*DRIVE_SPD);
   return 0;
}

