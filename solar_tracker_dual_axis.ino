#include <Servo.h>

// horizontal servo
Servo horizontal;
int servo_horizontal = 90;

int servo_horizontal_limit_high = 180; //180
int servo_horizontal_limit_low = 0; //65

Servo vertical;
int servo_vertical = 90;

int servo_vertical_limit_high = 180; //120
int servo_vertical_limit_low = 0; //15


// LDR pin connections
int ldrTR = A4; // LDR top right
int ldrTL = A2; // LDR top left
int ldrBR = A5; // LDR bottom right
int ldrBL = A1; // LDR bottom left


void setup() {
  Serial.begin(9600);
  // servo connections
  horizontal.attach(6);
  vertical.attach(5);
  // move servos
  horizontal.write(90);
  vertical.write(45);
  delay(3000);
}


void loop() {

  int tr = analogRead(ldrTR); // top right
  int tl = analogRead(ldrTL); // top left
  int br = analogRead(ldrBR); // bottom right
  int bl = analogRead(ldrBL); // bottom left

  int dtime = 50; // change for debugging only
  int tol = 50;

  int avt = (tl + tr) / 2; // average value top
  int avd = (bl + br) / 2; // average value bottom
  int avl = (tl + bl) / 2; // average value left
  int avr = (tr + br) / 2; // average value right

  int dvert = avt - avd;  // check the difference of up and down
  int dhoriz = avl - avr; // check the difference of left and right

  // check if the difference is in the tolerance else change vertical angle
  if (-1 * tol > dvert || dvert > tol) {
    if (avt > avd) {
      servo_vertical = ++servo_vertical;
      if (servo_vertical > servo_vertical_limit_high) {
        servo_vertical = servo_vertical_limit_high;
      }
    }
    else if (avt < avd) {
      servo_vertical = --servo_vertical;
      if (servo_vertical < servo_vertical_limit_low) {
        servo_vertical = servo_vertical_limit_low;
      }
    }
    vertical.write(servo_vertical);
  }

  // check if the difference is in the tolerance else change horizontal angle
  if (-1 * tol > dhoriz || dhoriz > tol) {
    if (avl > avr) {
      servo_horizontal = ++servo_horizontal;
      if (servo_horizontal < servo_horizontal_limit_low) {
        servo_horizontal = servo_horizontal_limit_low;
      }
    }
    else if (avl < avr) {
      servo_horizontal = --servo_horizontal;
      if (servo_horizontal > servo_horizontal_limit_high) {
        servo_horizontal = servo_horizontal_limit_high;
      }
    }
    else if (avl == avr) {
      // nothing
    }
    horizontal.write(servo_horizontal);
  }
  
  delay(dtime);
  
}
