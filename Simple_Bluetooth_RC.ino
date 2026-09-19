/*
╔══════════════════════════════════════════════════════════╗
║                         CREDITS                          ║
╠══════════════════════════════════════════════════════════╣
║ Project     : Simple Bluetooth RC                        ║
║ Author      : ziihan                                     ║
║ GitHub      : zii-han                                    ║
║ Instagram   : zii._han2510                               ║
║ Created     : 19 September 2026                          ║
║ Updated     : 19 September 2026                          ║
║ Version     : 1.0.0                                      ║
║ Status      : Stable                                     ║
║ Language    : C++ / Arduino                              ║
║ Board       : ESP32 DevKit V1                            ║
║ License     : MIT                                        ║
╠══════════════════════════════════════════════════════════╣
║ Description : A simple RC controlled by a mobile         ║
║               phone via Bluetooth.                       ║
║ Support Me  :                                            ║
║ Thanks To   : Everyone who supported this project.       ║
╠══════════════════════════════════════════════════════════╣
║ DISCLAIMER!!                                             ║
║ This project is made for educational purposes.           ║
║ Feel free to use, modify, and experiment with it         ║
║ howeveryou like, as this project was created             ║
║ specifically for learning and exploration. :)            ║
╠══════════════════════════════════════════════════════════╣
║ CHANGELOG :                                              ║
║   v1.0.0 - 19 September 2026                             ║
║     • Initial release                                    ║
║     • Added Bluetooth RC control                         ║
║     • Added ESP32 DevKit V1 support                      ║
╚══════════════════════════════════════════════════════════╝
*/

#define in1 13
#define in2 12
#define in3 14
#define in4 27
#define enA 18
#define enB 19

#include "BluetoothSerial.h"

String device_name = "Rover";

int velocity[] = { 0, 0 };

BluetoothSerial BT;

void setup() {
  Serial.begin(115200);

  //pin
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  BT.begin(device_name);
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
}

void loop() {
  char cmd;

  if (BT.available() > 0) {
    cmd = BT.read();
    if (cmd != NULL) {
      //STOP
      if (cmd == 'S') {
        velocity[0] = 0;
        velocity[1] = 0;
        setSpeed();
        motor(0, 0, 0, 0);
      }
      //maju
      else if (cmd == 'F') {
        velocity[0] = 255;
        velocity[1] = 255;
        setSpeed();
        motor(1, 0, 0, 1);
      }
      //mundur
      else if (cmd == 'B') {
        velocity[0] = 255;
        velocity[1] = 255;
        setSpeed();
        motor(0, 1, 1, 0);
      }
      //maju kanan
      else if (cmd == 'I') {
        velocity[0] = 255;
        velocity[1] = 127;
        setSpeed();
        motor(1, 0, 0, 1);
      }
      //maju kiri
      else if (cmd == 'G') {
        velocity[0] = 127;
        velocity[1] = 255;
        setSpeed();
        motor(1, 0, 0, 1);
      }
      //mundur kanan
      else if (cmd == 'J') {
        velocity[0] = 127;
        velocity[1] = 255;
        setSpeed();
        motor(0, 1, 1, 0);
      }
      //mundur kiri
      else if (cmd == 'H') {
        velocity[0] = 255;
        velocity[1] = 127;
        setSpeed();
        motor(0, 1, 1, 0);
      }
      //kanan(spin)
      else if (cmd == 'R') {
        velocity[0] = 255;
        velocity[1] = 255;
        setSpeed();
        motor(1, 0, 1, 0);
      }
      //kiri(spin)
      else if (cmd == 'L') {
        velocity[0] = 255;
        velocity[1] = 255;
        setSpeed();
        motor(0, 1, 0, 1);
      }
    }
  }
}

void motor(int kananA, int kananB, int kiriA, int kiriB) {
  digitalWrite(in1, kananA);
  digitalWrite(in2, kananB);
  digitalWrite(in3, kiriA);
  digitalWrite(in4, kiriB);
}

void setSpeed() {
  analogWrite(enA, map(velocity[0], 0, 100, 0, 255));
  analogWrite(enB, map(velocity[1], 0, 100, 0, 255));
}