#include <FEH.h>
#include <Arduino.h>

// Motors
FEHMotor rightdrive(FEHMotor::Motor1, 9.0);
FEHMotor leftdrive (FEHMotor::Motor0, 9.0);

// ---------- TUNABLE CONSTANTS ----------
static const float BASE_PWR = 25.0;  // straight speed
static const float CORR_PWR = 18.0;  // slower wheel during correction
static const float TURN_PWR = 28.0;  // faster wheel during correction

// Per-sensor thresholds (VOLTS) — YOU MUST CALIBRATE THESE THREE
static const float THRESH_L = 2.5;
static const float THRESH_M = 2.5;
static const float THRESH_R = 2.5;

// Polarity: if "line" reads LOWER voltage than background, keep true.
// If "line" reads HIGHER voltage, set false.
static const bool LINE_IS_LOW = false;

// Debounce to reduce jitter in state changes
static const int STABLE_COUNT = 3;
// --------------------------------------

// Analog optosensors (CHANGE THESE TO MATCH YOUR WIRING)
AnalogInputPin optoL(FEHIO::Pin0);
AnalogInputPin optoM(FEHIO::Pin1);
AnalogInputPin optoR(FEHIO::Pin2);

// ---------- line detection per sensor ----------
static inline bool seesLineL(float v) {
    return LINE_IS_LOW ? (v < THRESH_L) : (v > THRESH_L);
}
static inline bool seesLineM(float v) {
    return LINE_IS_LOW ? (v < THRESH_M) : (v > THRESH_M);
}
static inline bool seesLineR(float v) {
    return LINE_IS_LOW ? (v < THRESH_R) : (v > THRESH_R);
}
// ----------------------------------------------

enum LineState { ON_MIDDLE, ON_LEFT, ON_RIGHT, LOST };

// Motor behaviors (continuous — no long sleeps)
void DriveStraight() {
    rightdrive.SetPercent(BASE_PWR);
    leftdrive.SetPercent(BASE_PWR);
}
void DriveLeft() {
    rightdrive.SetPercent(TURN_PWR);
    leftdrive.SetPercent(CORR_PWR);
}
void DriveRight() {
    rightdrive.SetPercent(CORR_PWR);
    leftdrive.SetPercent(TURN_PWR);
}
void Stop() {
    rightdrive.SetPercent(0);
    leftdrive.SetPercent(0);
}

LineState decideState(bool L, bool M, bool R, LineState prev)
{
    if (M) return ON_MIDDLE;
    if (L && !R) return ON_LEFT;
    if (R && !L) return ON_RIGHT;

    // If both outer sensors see line (wide line / intersection), go straight
    if (L && R) return ON_MIDDLE;

    return LOST;
}

void actOnState(LineState s, LineState lastKnown)
{
    switch (s) {
        case ON_MIDDLE: DriveStraight(); break;
        case ON_LEFT:   DriveLeft();     break;
        case ON_RIGHT:  DriveRight();    break;

        case LOST:
            // Bias toward last known direction
            if (lastKnown == ON_LEFT)       DriveLeft();
            else if (lastKnown == ON_RIGHT) DriveRight();
            else                            DriveStraight();
            break;
    }
}

void ERCMain()
{
    int x, y;
    while (!LCD.Touch(&x, &y)) { }

    LineState state = ON_MIDDLE;
    LineState lastKnown = ON_MIDDLE;

    int stable = 0;
    LineState candidate = ON_MIDDLE;

    while (true)
    {
        // Read voltages
        float vL = optoL.Value();
        float vM = optoM.Value();
        float vR = optoR.Value();

        // Convert to boolean "sees line"
        bool L = seesLineL(vL);
        bool M = seesLineM(vM);
        bool R = seesLineR(vR);

        // Decide next state
        LineState next = decideState(L, M, R, state);

        // Debounce / stability
        if (next == candidate) stable++;
        else { candidate = next; stable = 0; }

        if (stable >= STABLE_COUNT) {
            state = candidate;
            stable = STABLE_COUNT;
        }

        // Update last known (not LOST)
        if (state != LOST) lastKnown = state;

        // Actuate motors
        actOnState(state, lastKnown);

        // Loop delay
        Sleep(0.01);
    }
}