#include <FEH.h>
#include <Arduino.h>
#include "FEHIO.h"
#include "FEHLCD.h"
#include <FEHUtility.h>
#include <FEHServo.h>
#include <FEHLCD.h>

// Declare things like Motors, Servos, etc. here
// For example:
// FEHMotor leftMotor(FEHMotor::Motor0, 6.0);
// FEHServo servo(FEHServo::Servo0);



void ERCMain()
{
    float CdSvalue,cdSmin,cdsmax,degree;
    int x_position, y_position;
    //declare an analog input on Pin3
    AnalogInputPin CdS_cell(FEHIO::Pin2); 
    FEHServo servo(FEHServo::Servo0); // declare servo arm
    servo.SetMin(500); // set minimum value for servo
    servo.SetMax(2272); // set maximum value for servo

    //Part 1
    /*
    while(!LCD.Touch(&x_position, &y_position))
    {
        CdSvalue = CdS_cell.Value();
        LCD.WriteLine(CdSvalue);
        Sleep(.2);
        LCD.Clear();
    }
    */
    //Part 2
    while(!LCD.Touch(&x_position, &y_position))
    {
        CdSvalue = CdS_cell.Value(); 
        cdSmin = .35;
        cdsmax = 5; //Set values for min and max CdS values based on testing
        LCD.WriteLine(CdSvalue);
        degree = (CdSvalue - cdSmin) * 180 / (cdsmax - cdSmin); // calculate degree to set servo to based on CdS value
        servo.SetDegree(degree); // set servo degree based on CdS value
        LCD.WriteLine(degree);
        Sleep(.2);
        LCD.Clear();
    }
    
}