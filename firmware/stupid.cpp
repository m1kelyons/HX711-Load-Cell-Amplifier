#include "HX711.h"

 /*
 
 Cyclocopter Single Propeller Test Stand Force Balance Program
 
 This example code uses bogde's excellent library: https://github.com/bogde/HX711
 bogde's library is released under a GNU GENERAL PUBLIC LICENSE

 Arduino pin 2 -> HX711 CLK
 3 -> DOUT
 5V -> VCC
 GND -> GND
 
 Most any pin on the Arduino Uno will be compatible with DOUT/CLK.
 
 The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.
 
*/

#include "HX711.h"

#define DOUT1   3
#define CLK1    2
#define DOUT2   5
#define CLK2    4
#define DOUT3   7
#define CLK3    6
#define DOUT4   9
#define CLK4    8

HX711 scale1(DOUT1, CLK1);
HX711 scale2(DOUT2, CLK2);
HX711 scale3(DOUT3, CLK3);
HX711 scale4(DOUT4, CLK4);

float calibration_factor1 = -38346; //-38346 for 50 kg max Load Cell 50 kg (cantilever type)
float calibration_factor2 = -38296;
float calibration_factor3 = -36246;
float calibration_factor4 = -38346;

float force1 = 0.0;
float force2 = 0.0;
float force3 = 0.0;
float force4 = 0.0;

float totalX = 0.0;
float totalZ = 0.0;

float vertical_dist = 3.7625;
float horizontal_dist = 1.27;
float torque_ratio = vertical_dist / horizontal_dist;

void setup() {
  Serial.begin(9600);
  scale1.set_scale();
  scale1.tare();

  scale2.set_scale();
  scale2.tare();

  scale3.set_scale();
  scale3.tare();

  scale4.set_scale();
  scale4.tare();
}

void loop() {

  scale1.set_scale(calibration_factor1); //Adjust to this calibration factor
  force1 = scale1.get_units();
  Serial.print(force1, 4);
  Serial.print(" ");

  scale2.set_scale(calibration_factor2); //Adjust to this calibration factor
  force2 = scale1.get_units();
  Serial.print(force2, 4);
  Serial.print(" ");

  scale3.set_scale(calibration_factor3); //Adjust to this calibration factor
  force3 = scale1.get_units();
  Serial.print(force3, 4);
  Serial.print(" ");

  scale4.set_scale(calibration_factor4); //Adjust to this calibration factor
  force4 = scale1.get_units();
  Serial.print(force4, 4);
  Serial.print("      ");

  //totalX = 1.0/torque_ratio * (force1 + force3 - force2 - force4) 
  totalX = 1.0/torque_ratio * (2 * force3 - force2 - force4);
  Serial.print(totalX, 4);
  Serial.print(" ");

  // totalZ = force1 + force2 + force3 + force4;
  totalZ = force2 + 2 * force3 + force4;
  Serial.print(totalZ, 4);
  Serial.print(" ");

  Serial.println();

  // if(Serial.available())
  // {
  //   char temp = Serial.read();
  //   if(temp != NULL)
  //   {
  //     Serial.print("Receiving Data");
  //   }
  // }
  delay(100); //delay for 1/10 of a second
}