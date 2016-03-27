/*
    This program was used for Performance Test 3 on March 11.
    The procedure consisted of picking up the payload, going up the ramp,
    then dropping the payload off.     
*/

#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <Constants.h>
#include <EquipmentDeclarations.h>
#include <SensorUtility.h>
#include <DriveAndNavigation.h>

int main(void)
{
        ////Initialize////
        LCD.WriteLine("Initializing arms");
        setup_lasso();
        setup_pArm();
        lasso.SetDegree(LASSO_UP);
        pArm.SetDegree(P_ARM_UP);

        RPS.InitializeTouchMenu();

        wait_for_start_light(4);

        ////Main routine////
        //~(10,9?) degrees ~ 0

        LCD.WriteLine("Turning to 0 degrees");
        check_heading(0);
        Sleep(400);
        //(?,?) degrees = 0

        LCD.WriteLine("Driving to x = 20.5");
        move_forward(DRIVE_SPD, 10.5); //guessed value
        Sleep(300);
        check_x_plus(20.5);
        Sleep(400);
        //(20.5,?) degrees = 0

        LCD.WriteLine("Turning to 90 degrees");
        turn_left(DRIVE_SPD, 90);
        Sleep(300);
        check_heading(90);
        Sleep(400);
        //(20.5,?) degrees = 90

        LCD.WriteLine("Driving to y = 17");
        move_forward(DRIVE_SPD, 8); //guessed value
        Sleep(300);
        check_y_plus(17);
        Sleep(400);
        //Coordinates located
        //(20.5,17) degrees = 90

        LCD.WriteLine("Turning to 0 degrees");
        turn_right(DRIVE_SPD, 90);
        Sleep(300);
        check_heading(0);
        Sleep(400);
        //(20.5,17) degrees = 0

        LCD.WriteLine("Driving to x = 27.4");
        move_forward(DRIVE_SPD, 6.9);
        Sleep(300);
        check_x_plus(27.4);
        Sleep(400);
        //(27.4,17) degrees = 0

        LCD.WriteLine("Turning to 270 degrees");
        turn_right(DRIVE_SPD, 90);
        Sleep(300);
        check_heading(270);
        Sleep(400);
        //(27.4,17) degrees = 270


        //*Payload Pickup*//

        //Lower the payload arm
        LCD.WriteLine("Lowering payload arm");
        pArm.SetDegree(P_ARM_DOWN);
        Sleep(700);

        LCD.WriteLine("Driving to y = 16.5");
        move_forward(DRIVE_SPD, 0.5);
        Sleep(300);
        check_y_minus(16.5);
        Sleep(400);
        //(27.4,16.5) degrees = 270

        LCD.WriteLine("Confirming 270 degrees");
        check_heading(270);
        Sleep(400);
        //(27.4,16.5) degrees = 270

        //actual pickup move
        LCD.WriteLine("Driving to y = 12.9");
        move_forward(DRIVE_SPD, 3.6);
        Sleep(400);
        //(27.4,12.9) degrees = 270

        //Raise the payload arm
        LCD.WriteLine("Raising payload arm");
        pArm.SetDegree(P_ARM_UP);
        Sleep(700);

        LCD.WriteLine("Driving to y = 15.5");////
        move_forward(-DRIVE_SPD, 2.6); //guessed value
        Sleep(300);
        check_y_minus(15.5);
        Sleep(400);
        //(27.4,15.5) degrees = 270

        LCD.WriteLine("Turning to 90 degrees");
        turn_left(DRIVE_SPD, 180);
        Sleep(300);
        check_heading(90);
        Sleep(400);
        //(27.4,15.5) degrees = 90

        LCD.WriteLine("Driving to y = 25");
        move_forward(DRIVE_SPD, 11.5); //guessed value
        Sleep(300);
        check_y_plus(25);
        Sleep(400);
        //(27.4,25) degrees = 90

        LCD.WriteLine("Turning to 94 degrees");
        check_heading(94);
        Sleep(400);
        //(27.4,25) degrees = 94

        LCD.WriteLine("Up the ramp!!");
        move_forward(1.8*DRIVE_SPD, 30);
        Sleep(600);
        //(?,?) degrees = ?

        //*Upper Area*//

        LCD.WriteLine("Turning to 90 degrees");
        check_heading(90);
        Sleep(400);
        //(?,?) degrees = 90

        LCD.WriteLine("Turning to 225 degrees");
        turn_right(DRIVE_SPD, 135);
        Sleep(300);
        check_heading(225);
        Sleep(400);
        //(?,?) degrees = 225
        move_forward(DRIVE_SPD, 1.5);
        Sleep(400);

        LCD.WriteLine("Turning to 270 degrees");
        turn_right(DRIVE_SPD, 45);
        Sleep(300);
        check_heading(270);
        Sleep(400);
        //(?,?) degrees = 270

        LCD.WriteLine("Confirming y = 47");
        Sleep(300);
        check_y_minus(47);
        Sleep(400);
        //(?,47) degrees = 270

        LCD.WriteLine("Turning to 180 degrees");
        turn_right(DRIVE_SPD, 90);
        Sleep(300);
        check_heading(180);
        Sleep(400);
        //(?,47) degrees = 180

        LCD.WriteLine("Confirming x = 25");
        check_x_minus(25);
        Sleep(400);
        //Coordinates located
        //(25,47) degrees = 0

        //Baby steps
        LCD.WriteLine("Driving to x = 21.5");
        move_forward(DRIVE_SPD, 3.5);
        Sleep(300);
        check_x_minus(21.5);
        Sleep(300);
        check_heading(180);
        Sleep(400);
        //(21.5,47) degrees = 180

        LCD.WriteLine("Driving to x = 18");
        move_forward(DRIVE_SPD, 3.5);
        Sleep(300);
        check_x_minus(18);
        Sleep(300);
        check_heading(180);
        Sleep(400);
        //(18,47) degrees = 180

        LCD.WriteLine("Driving to x = 14.5");
        move_forward(DRIVE_SPD, 3.5);
        Sleep(300);
        check_x_minus(14.5);
        Sleep(300);
        check_heading(180);
        Sleep(400);
        //(14.5,47) degrees = 180

        LCD.WriteLine("Driving to x = 11");
        move_forward(DRIVE_SPD, 3.5);
        Sleep(300);
        check_x_minus(11);
        Sleep(300);
        check_heading(180);
        Sleep(400);
        //(11,47) degrees = 180

        LCD.WriteLine("Driving to x = 5.5"); //////Deposit spot
        move_forward(DRIVE_SPD, 5.5);
        Sleep(400);
        //(5.5,47) degrees = 180
        //baby stepped

        LCD.WriteLine("Turning to 90 degrees");
        turn_right(DRIVE_SPD, 90);
        Sleep(300);
        check_heading(90);
        Sleep(400);
        //(6.5,47) degrees = 90

        //*Payload Deposit*//
        //Entering DEADZONE (encoders only)

        LCD.WriteLine("Driving to y = 54.5");/////
        move_forward(DRIVE_SPD, 7.5); //half speed
        Sleep(400);
        //(6.5, 54.5) degrees = 90

        //lower the payload arm
        LCD.WriteLine("Depositing payload");
        pArm.SetDegree(P_ARM_DEPOSIT);
        Sleep(400); //tiny sleep
        //(6.5, 54.5) degrees = 90

        LCD.WriteLine("Driving to y = 46");/////
        move_forward(-0.75*DRIVE_SPD, 7.5); //slowwwww
        Sleep(400);
        //(6.5, 46) degrees = 90 (going to misalign here a lot, run until bumpswitch instead?)

        //Raise the payload arm
        LCD.WriteLine("Raising payload arm");
        pArm.SetDegree(P_ARM_UP);
        Sleep(700);
        return 0;
    }

