#include "Joystick.h"

/* Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_MULTI_AXIS, 8, 0,
  true, true, false, false, false, false,
  false, false, true, true, true);
*/
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  8, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  true, true, true,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering


int steerValue = 0;
int acceleratorValue = 0;
int brakeValue = 0;

int lastButtonState[12] = {0,0,0,0,0,0,0,0};

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
/*  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  */
  Joystick.begin();
/*
  Joystick.setSteeringRange(0, 1023);
  Joystick.setAcceleratorRange(0, 1023);
  Joystick.setBrakeRange(0, 1023);
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);
*/

  Joystick.setRxAxisRange(0, 1023);
  Joystick.setRyAxisRange(0, 1023);
  Joystick.setRyAxisRange(0, 1023);
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);

}

void loop() {
  steerValue = analogRead(A0);
  acceleratorValue = analogRead(A1);
  brakeValue = analogRead(A2);

  Joystick.setRxAxis(steerValue);
  Joystick.setRyAxis(acceleratorValue);
  Joystick.setRzAxis(brakeValue);

  Joystick.setXAxis(0);
  Joystick.setYAxis(0);

   // Read pin values
  for (int index = 0; index < 8; index++)
  {
    int currentButtonState = !digitalRead(index + 2);
    if (currentButtonState != lastButtonState[index])
    {
      switch (index) {
        case 0: // UP
          Joystick.setButton(index, currentButtonState);
          break;
        case 1: // RIGHT
          Joystick.setButton(index, currentButtonState);
          break;
        case 2: // DOWN
          Joystick.setButton(index, currentButtonState);
          break;
        case 3: // LEFT
          Joystick.setButton(index, currentButtonState);
          break;
        case 4: // R
          Joystick.setButton(index, currentButtonState);
          break;
        case 5: // A
          Joystick.setButton(index, currentButtonState);
          break;
        case 6: // B
          Joystick.setButton(index, currentButtonState);
          break;
        case 7: // START
          Joystick.setButton(index, currentButtonState);
          break;
/*        case 8: // X
          Joystick.setButton(index - 4, currentButtonState);
          break;
        case 9: // Y
          Joystick.setButton(index - 4, currentButtonState);
          break;
        case 10: // START
          Joystick.setButton(index - 4, currentButtonState);
          break;
        case 11: // SELECT
          Joystick.setButton(index - 4, currentButtonState);
          break; */
      }
      lastButtonState[index] = currentButtonState;
    }
  }

  Joystick.sendState();

  delay(10);

}
