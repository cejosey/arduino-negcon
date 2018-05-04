#include "Joystick.h"

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_MULTI_AXIS, 8, 0,
  true, true, true, false, false, false,
  false, false, true, true, true);

int steerValue = 0;
int acceleratorValue = 0;
int brakeValue = 0;
int lValue = 0;

int lastButtonState[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);

  Joystick.begin();

  Joystick.setSteeringRange(0, 1023);
  Joystick.setAcceleratorRange(0, 1023);
  Joystick.setBrakeRange(0, 1023);
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);
  Joystick.setZAxisRange(-1, 0);

}

void loop() {
  steerValue = analogRead(A0);
  acceleratorValue = analogRead(A1);
  brakeValue = analogRead(A2);
//  lValue = analogRead(A3);

  Joystick.setSteering(steerValue);
  Joystick.setAccelerator((acceleratorValue/2) + 512);
  Joystick.setBrake(-((brakeValue/2) + 512));

   // Read pin values
  for (int index = 0; index < 12; index++)
  {
    int currentButtonState = !digitalRead(index + 2);
    if (currentButtonState != lastButtonState[index])
    {
      switch (index) {
        case 0: // UP
          if (currentButtonState == 1) {
            Joystick.setYAxis(-1);
          } else {
            Joystick.setYAxis(0);
          }
          break;
        case 1: // RIGHT
          if (currentButtonState == 1) {
            Joystick.setXAxis(1);
          } else {
            Joystick.setXAxis(0);
          }
          break;
        case 2: // DOWN
          if (currentButtonState == 1) {
            Joystick.setYAxis(1);
          } else {
            Joystick.setYAxis(0);
          }
          break;
        case 3: // LEFT
          if (currentButtonState == 1) {
            Joystick.setXAxis(-1);
          } else {
            Joystick.setXAxis(0);
          }
          break;
        case 4: // L
          Joystick.setButton(index - 4, currentButtonState);
          Joystick.setZAxis(currentButtonState);
          break;
        case 5: // R
          Joystick.setButton(index - 4, currentButtonState);
          break;
        case 6: // A
          Joystick.setButton(index - 4, currentButtonState);
          break;
        case 7: // B
          Joystick.setButton(index - 4, currentButtonState);
          break;
        case 8: // X
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
          break;
      }
      lastButtonState[index] = currentButtonState;

      //lValue = 0;
    }
  }

  Joystick.sendState();

  delay(10);

}
