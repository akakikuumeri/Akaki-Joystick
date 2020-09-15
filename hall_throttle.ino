// USB Joystick with hall effect sensors
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//------------------------------------------------------------

//change these to define which pins your hall effect sensors or potentiometers are connected.
//to change button connections, scroll down to loop()
#define X_PIN A1
#define Y_PIN A0
#define T_PIN A2
//change these to change trim and limits. Calibrating your joystick in Windows achieves the same thing
#define X_MIN 0
#define X_MAX 1023
#define X_TRIM 0
#define X_INVERT -1
//to invert an axis, change 1 to -1
#define Y_MIN 0
#define Y_MAX 1023
#define Y_TRIM 0
#define Y_INVERT 1

#define T_MIN 0
#define T_MAX 1023
#define T_TRIM 0
#define T_INVERT 1


#include <Joystick.h>


int value = 0;

Joystick_ Joystick(0x05,JOYSTICK_TYPE_MULTI_AXIS,
  3, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  true, true, false,   // Yes Rx, Ry, no Rz
  false, false,           // No rudder, yes throttle
  false, false, false);  // No accelerator, brake, or steering

void setup() {
  // Initialize Button Pins
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.begin(false); //false = dont send automatically. We will sendState() at the end of the loop
  Joystick.setXAxisRange(-512, 512);
  Joystick.setYAxisRange(-512, 512);
  Joystick.setRxAxisRange(-512, 512);
  Joystick.setRyAxisRange(-512, 512);
}


void loop() {
  //read buttons. Change pins and button numbers here, if you want to have different number connected to different pin
  Joystick.setButton(0, !digitalRead(4)); //pin 2 LOW means button 0 PRESSED
  if (digitalRead(2) && digitalRead(3)) {
    Joystick.setButton(1, 1); // flaps middle
    Joystick.setButton(2, 0);
  } else {
    if (!digitalRead(2)) {
      Joystick.setButton(1, 0); // flaps up
      Joystick.setButton(2, 0);
    }
    else
    {
      Joystick.setButton(1, 0); // flaps full down
      Joystick.setButton(2, 1);
    }
  }

  //read analog axes
  value = map(analogRead(A1) , 0, 1023, -512, 512) * -1;
  Joystick.setXAxis(value);
  value = map(analogRead(A2) , 0, 1023, -512, 512) * -1;
  Joystick.setYAxis(value);
  value = map(analogRead(A0) , 0, 1023, -512, 512) * -1;
  Joystick.setRxAxis(value);
  value = map(analogRead(A3) , 0, 1023, -512, 512);
  Joystick.setRyAxis(value);
  
  Joystick.sendState();
  delay(10);
}
