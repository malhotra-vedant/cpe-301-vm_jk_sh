
//A0 A1 A2 A4 A13 A14 A15 2 3 4 5 6 7 8 9 13 14

#include <Stepper.h>

//A0 at f0  
//A1 at f1 
//A2 at f2 
//A4 at f4 
volatile unsigned char* port_f = (unsigned char*) 0x31; 
volatile unsigned char* ddr_f = (unsigned char*) 0x30;
volatile unsigned char* pin_f = (unsigned char*) 0x2f;

//A13 at k5 
//A14 at k6
//A15 at k7 
volatile unsigned char* port_k = (unsigned char*) 0x108; 
volatile unsigned char* ddr_k = (unsigned char*) 0x107;
volatile unsigned char* pin_k = (unsigned char*) 0x106;

//2 at e4
//3 at e5
//5 at e3
volatile unsigned char* port_e= (unsigned char*) 0x2e; 
volatile unsigned char* ddr_e = (unsigned char*) 0x2d;
volatile unsigned char* pin_e = (unsigned char*) 0x2c;

//4 at g5
volatile unsigned char* port_g= (unsigned char*) 0x14; 
volatile unsigned char* ddr_g = (unsigned char*) 0x13;
volatile unsigned char* pin_g = (unsigned char*) 0x12;

//6 at h3
//7 at h4
//8 at h5
//9 at 86
volatile unsigned char* port_h= (unsigned char*) 0x102; 
volatile unsigned char* ddr_h = (unsigned char*) 0x101;
volatile unsigned char* pin_h = (unsigned char*) 0x100;

//13 at b7
volatile unsigned char* port_b= (unsigned char*) 0x25; 
volatile unsigned char* ddr_b = (unsigned char*) 0x24;
volatile unsigned char* pin_b = (unsigned char*) 0x23;

//14 at j1
volatile unsigned char* port_j= (unsigned char*) 0x105; 
volatile unsigned char* ddr_j= (unsigned char*) 0x104;
volatile unsigned char* pin_j = (unsigned char*) 0x103;


const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 17;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  myStepper.setSpeed(rolePerMinute);
  // initialize the serial port:
  Serial.begin(9600);
  *ddr_a &= 0xFE;
  *port_a |= 0x1;

}

void loop() {

  if (*pin_a & 0x1){
    Serial.println("Opening..");
    myStepper.step(stepsPerRevolution);
    delay(500);
    Serial.println("Open.");

  } else {
    Serial.println("Closing..");
    myStepper.step(-stepsPerRevolution);
    delay(500);
    Serial.println("Closed.");

  }
}