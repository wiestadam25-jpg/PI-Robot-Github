#include <FEH.h>
#include <Arduino.h>

//Hello
// Declare things like Motors, Servos, etc. here
// For example:
// FEHMotor leftMotor(FEHMotor::Motor0, 6.0);
// FEHServo servo(FEHServo::Servo0);

FEHMotor rightdrive(FEHMotor::Motor1,9.0);
FEHMotor leftdrive(FEHMotor::Motor0,9.0);
void Drive_Forward();
void Drive_Back();
void Turn_Right();
void Turn_Left();
void Stop();

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
    DigitalInputPin fr_switch(FEHIO::Pin6);
    DigitalInputPin fl_switch(FEHIO::Pin7);
    DigitalInputPin br_switch(FEHIO::Pin8);
    DigitalInputPin bl_switch(FEHIO::Pin9);
    
    int x,y;
    while(!LCD.Touch(&x,&y)){

    }

    Drive_Forward();
    while(fr_switch.Value() == 1 && fl_switch.Value() == 1){

    }

    Stop();
    Drive_Back();
    Sleep(1.0);
    Stop();
    Turn_Left();
    Drive_Forward();
    while(fr_switch.Value() == 1 && fl_switch.Value() == 1){

    }

    Stop();
    Drive_Back();
    Sleep(1.0);
    Stop();
    Turn_Right();

    Drive_Forward();
    while(fr_switch.Value() == 1 && fl_switch.Value() == 1){

    }
    Stop();
}