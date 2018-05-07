#include "Joystick.h"

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_MULTI_AXIS, 8, 0,
  true, true, true, false, false, false,
  false, false, true, true, true);

int steerValue = 0;
int acceleratorValue = 0;
int brakeValue = 0;
int IValue = 0;
int IIValue = 0;
int analogOverride = 0;
int gamePlayOverride = 0;

int lastButtonState[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

void setup() {
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
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

  Joystick.setSteeringRange(0, 1024);
  Joystick.setAcceleratorRange(0, 1024);
  Joystick.setBrakeRange(0, 1024);
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);
  Joystick.setZAxisRange(-1, 1);

  Joystick.setZAxis(-1);

}

void loop() {
  steerValue = analogRead(A0);
  acceleratorValue = analogRead(A1);
  brakeValue = analogRead(A2);
//  lValue = analogRead(A3);

  IValue = !digitalRead(9);
  IIValue = !digitalRead(11);

  analogOverride = !digitalRead(0);
  gamePlayOverride = !digitalRead(1);

  if (analogOverride == 1) {
    Joystick.setSteering(512);
    Joystick.setAccelerator(512);
    Joystick.setBrake(512);
    Joystick.setZAxis(0);
  } else {
    Joystick.setSteering(steerValue);
  
    if (IValue == 1) {
      Joystick.setAccelerator(1024);
    } else {
      Joystick.setAccelerator(acceleratorValue);
    }
    if (IIValue == 1) {
      Joystick.setBrake(1024);
    } else {
      Joystick.setBrake(brakeValue);
    }
  }
   // Read pin values
  for (int index = 0; index < 12; index++)
  {
    int currentButtonState = !digitalRead(index + 2);
    if (currentButtonState != lastButtonState[index])
    {
      switch (index) {
        case 0: // UP
          if (currentButtonState == 1) {
            Joystick.setYAxis(1);
          } else {
            Joystick.setYAxis(0);
          }
          break;
        case 1: // RIGHT
          if (currentButtonState == 1) {
            if (gamePlayOverride == 1) {
              Joystick.setButton(4, currentButtonState);
            } else {
                Joystick.setXAxis(1);
            }
          } else {
            if (gamePlayOverride == 1) {
              Joystick.setButton(4, currentButtonState);
            } else {
                Joystick.setXAxis(0);
            }          }
          break;
        case 2: // DOWN
          if (currentButtonState == 1) {
            Joystick.setYAxis(-1);
          } else {
            Joystick.setYAxis(0);
          }
          break;
        case 3: // LEFT
          if (currentButtonState == 1) {
            if (gamePlayOverride == 1) {
              Joystick.setButton(2, currentButtonState);
            } else {
                Joystick.setXAxis(1);
            }
          } else {
            if (gamePlayOverride == 1) {
              Joystick.setButton(2, currentButtonState);
            } else {
                Joystick.setXAxis(0);
            }          }
          break;
        case 4: // L
          // Joystick.setButton(index - 4, currentButtonState);
          if (currentButtonState == 1) {
            Joystick.setZAxis(1);
          } else {
            Joystick.setZAxis(-1);
          }
          break;
        case 5: // R
          Joystick.setButton(index - 4, currentButtonState);
          break;
        case 6: // A
          Joystick.setButton(index - 4, currentButtonState);
          break;
/*        case 7: // B = I - gas
          Joystick.setButton(index - 4, currentButtonState);
          if (currentButtonState == 1) {
            Joystick.setAccelerator(1023);
          } else {
            Joystick.setAccelerator(acceleratorValue);
          }
          break; */
        case 8: // X = B
          Joystick.setButton(index - 4, currentButtonState);
          break;
/*        case 9: // Y = II - brakes
          Joystick.setButton(index - 4, currentButtonState);
          if (currentButtonState == 1) {
            Joystick.setBrake(1023);
          } else {
            Joystick.setBrake(brakeValue);
          }
          break; */
        case 10: // START
          Joystick.setButton(index - 4, currentButtonState);
          break;
        case 11: // SELECT
          Joystick.setButton(index - 4, currentButtonState);
          break;
      }
      lastButtonState[index] = currentButtonState;

    }
  }

  Joystick.sendState();

  delay(10);

}
