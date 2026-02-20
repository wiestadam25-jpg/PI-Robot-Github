#include <FEH.h>
#include <Arduino.h>

//Hello
// Declare things like Motors, Servos, etc. here
// For example:
// FEHMotor leftMotor(FEHMotor::Motor0, 6.0);
// FEHServo servo(FEHServo::Servo0);

FEHMotor rightdrive(FEHMotor::Motor1,9.0);
FEHMotor leftdrive(FEHMotor::Motor0,9.0);

//Declaring Digital Encoders
DigitalEncoder left_encoder(FEHIO::Pin9);
DigitalEncoder right_encoder(FEHIO::Pin8);

void Drive_Forward();
void Drive_Back();
void Turn_Right();
void Turn_Left();
void Stop();
void Motor_25();
void Motor40();
void Motor60();

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

void Motor25(){
    //Sets motors to 25% power
    leftdrive.SetPercent(25.0);
    rightdrive.SetPercent(25.0);

    //Reseting encoder counts
    left_encoder.ResetCounts();
    right_encoder.ResetCounts();

    //Wait until encoder reaches 243 counts
    while(left_encoder.Counts() < 243 || right_encoder.Counts() < 243);

    //Stop Motor
    leftdrive.Stop();
    rightdrive.Stop();

    //Print Actual Encoder Values
    LCD.WriteLine(left_encoder.Counts());
    LCD.WriteLine(right_encoder.Counts());
}

void Motor40(){
    //Sets motors to 25% power
    leftdrive.SetPercent(40.0);
    rightdrive.SetPercent(40.0);

    //Reseting encoder counts
    left_encoder.ResetCounts();
    right_encoder.ResetCounts();

    //Wait until encoder reaches 243 counts
    while(left_encoder.Counts() < 243 || right_encoder.Counts() < 243);

    //Stop Motor
    leftdrive.Stop();
    rightdrive.Stop();

    //Print Actual Encoder Values
    LCD.WriteLine(left_encoder.Counts());
    LCD.WriteLine(right_encoder.Counts());
}

void Motor60(){
    //Sets motors to 25% power
    leftdrive.SetPercent(60.0);
    rightdrive.SetPercent(60.0);

    //Reseting encoder counts
    left_encoder.ResetCounts();
    right_encoder.ResetCounts();

    //Wait until encoder reaches 243 counts
    while(left_encoder.Counts() < 243 || right_encoder.Counts() < 243);

    //Stop Motor
    leftdrive.Stop();
    rightdrive.Stop();

    //Print Actual Encoder Values
    LCD.WriteLine(left_encoder.Counts());
    LCD.WriteLine(right_encoder.Counts());
}

void ERCMain()
{
    int x, y;
    while(!LCD.Touch(&x, &y));
    Motor25();
    while(!LCD.Touch(&x, &y));
    Motor40();
    while(!LCD.Touch(&x, &y));
    Motor60();
}