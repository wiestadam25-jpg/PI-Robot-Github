#include <FEH.h>
#include <Arduino.h>

//Pivot Constants
#define Apple_Pickup_ANGLE 90
#define Apple_Dropoff_ANGLE 0
#define Window_ANGLE 45
#define Lever_Down_ANGLE 90
#define Lever_Up_ANGLE 0
#define Servo_Max_Angle 180
#define Servo_Min_Angle 0

//Hello
// Declare things like Motors, Servos, etc. here
// For example:
// FEHMotor leftMotor(FEHMotor::Motor0, 6.0);
// FEHServo servo(FEHServo::Servo0);

FEHMotor rightdrive(FEHMotor::Motor1,9.0);
FEHMotor leftdrive(FEHMotor::Motor0,9.0);
FEHServo arm(FEHServo::Servo0);

void Pivot_Set_Angle(int degree);
void Drive_Forward();
void Drive_Back();
void Turn_Right();
void Turn_Left();
void Stop();

void Pivot_Set_Angle(int degree){
    arm.SetDegree(degree);
    return;
}

void Drive_Forward(){
    rightdrive.SetPercent(25.);
    leftdrive.SetPercent(25.);
    return;
}

void Drive_Back(){
    rightdrive.SetPercent(-25.);
    leftdrive.SetPercent(-25.);
    return;
}

void Turn_Right(){
    rightdrive.SetPercent(-15.);
    leftdrive.SetPercent(15.);
    Sleep(3.0);
    Stop();
    return;
}

void Turn_Left(){
    rightdrive.SetPercent(15.);
    leftdrive.SetPercent(-15.);
    Sleep(3.0);
    Stop();
    return;
}

void Stop(){
    rightdrive.SetPercent(0.);
    leftdrive.SetPercent(0.);
    return;
}



void ERCMain()
{
    // Your code here!
    int x,y;

    //Calibrate the arm servo to get the min and max values for the servo. This only needs to be done once per servo, so you can comment this out after you get the values and set them with SetMin() and SetMax()
    arm.TouchCalibrate();

    //Set the min and max values for the servo so that it can function properly.
    arm.SetMin(Servo_Min_Angle);
    arm.SetMax(Servo_Max_Angle);

    while(!LCD.Touch(&x,&y)){

    }

}