#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include <DriveAndNavigation.h>
#include <EquipmentDeclarations.h>
#include <SensorUtility.h>


int main(void)
{
    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

    //move_forward_smooth(DRIVE_SPD, 15);
    //while(true);

    RPS.InitializeTouchMenu();
    setup_lasso();
    //Put lasso in upright postion
    LCD.WriteLine("Setting lasso upright");
    lasso.SetDegree(UP_POSITION);

    wait_for_start_light(2);
    //Sleep(1000);

    //Initial check
    LCD.WriteLine("Turning to 90 degrees");
    check_heading(90);
    Sleep(400);
    //(?,?) degrees = 90

    LCD.WriteLine("Confirming y = 25");
    move_forward_smooth(DRIVE_SPD, 10); //partial
    Sleep(300);
    check_y_plus(25);
    Sleep(400);
    //(?,25) degrees = 90

    LCD.WriteLine("Turning to 0 degrees");
    turn_right(DRIVE_SPD, 90);
    Sleep(300);
    check_heading(0);
    Sleep(400);
    //(?,25) degrees = 0

    LCD.WriteLine("Confirming x = 10");
    check_x_plus(10);
    Sleep(400);
    //Coordinates located
    //(10,25) degrees = 0

    LCD.WriteLine("Driving to x = 29");
    move_forward_smooth(DRIVE_SPD, 19);
    Sleep(300);
    check_x_plus(29);
    Sleep(400);
    //(29,25) degrees = 0

    LCD.WriteLine("Turning to 87 degrees");
    turn_left(DRIVE_SPD, 87);
    Sleep(300);
    check_heading(87);
    Sleep(400);
    //(29,25) degrees = 87

    LCD.WriteLine("Get ready...");
    Sleep(1000);

    LCD.WriteLine("Up the ramp!!");
    move_forward_smooth(2*DRIVE_SPD, 35);
    Sleep(400);
    //(?,?) degrees = ?

    //*Upper Area*//

    LCD.WriteLine("Turning to 90 degrees");
    check_heading(90);
    Sleep(400);
    //(?,?) degrees = 90

    LCD.WriteLine("Turning to 270 degrees");
    turn_left(DRIVE_SPD, 180);
    Sleep(300);
    check_heading(270);
    Sleep(400);
    //(?,?) degrees = 270

    LCD.WriteLine("Confirming y = 43");
    Sleep(300);
    check_y_minus(43);
    Sleep(400);
    //(?,45) degrees = 270

    LCD.WriteLine("Turning to 180 degrees");
    turn_right(DRIVE_SPD, 90);
    Sleep(300);
    check_heading(180);
    Sleep(400);
    //(?,45) degrees = 180

    LCD.WriteLine("Confirming x = 25");
    check_x_minus(25);
    Sleep(400);
    //Coordinates located
    //(25,45) degrees = 0

    LCD.WriteLine("Driving to x = 7.5");
    move_forward_smooth(DRIVE_SPD, 17.5);
    Sleep(300);
    check_x_plus(7.5);
    Sleep(400);
    //(7.5,45) degrees = 180

    LCD.WriteLine("Turning to 90 degrees");
    turn_right(DRIVE_SPD, 90);
    Sleep(300);
    check_heading(90);
    Sleep(400);
    //(7.5,45) degrees = 90

    LCD.WriteLine("Confirming y = 45");
    Sleep(300);
    check_y_plus(45);
    Sleep(400);
    //(7.5,45) degrees = 270

    //*Switch time*//

    LCD.WriteLine("Turning to 91 degrees");
    check_heading(91);
    Sleep(400);
    //(7.5,45) degrees = 92

    //Drive foward until both bump switches are hit
    float startTime = TimeNow();
    LCD.WriteLine("Moving foward");
    drive_foward_indef(-PULSE_DRIVE_SPD);
    while (!microBackLeft.Value() || !microBackRight.Value())
    {
        /*
        if (TimeNow() - startTime > 3.0) // less than bottom
        {
            if (!microBackLeft.Value())
            {
                leftSetPercent(DRIVE_SPD*1.5);

            }
            else
            {
                rightSetPercent(DRIVE_SPD*1.5);

            }

        } */
        if (TimeNow() - startTime > 2.5)
        {
            break;
        }
    }
    right_motor.Stop();
    left_motor.Stop();
    Sleep(400);

    //Back up a set distance
    LCD.WriteLine("Backing up Beep Beep");
    move_forward(DRIVE_SPD*.75, back_up_distance);
    Sleep(600);

    //lower the lasso
    LCD.WriteLine("Lowering");
    lasso.SetDegree(DOWN_POSITION);
    Sleep(700);

    //drive foward to push
    LCD.WriteLine("Pushing");
    move_forward(-DRIVE_SPD, push_distance);

    LCD.WriteLine("Raising");
    lasso.SetDegree(UP_POSITION);
    Sleep(700);

    return 0;
}

