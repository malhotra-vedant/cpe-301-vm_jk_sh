//Jude Koenig
//Shayan Hosseini
//Vedant Malhotra
//CPE 301 - Final
//4/25/23

#include <Stepper.h>

#include <dht.h>        // Include library
#define outPin 13        // Defines pin number to which the sensor is connected

dht DHT;  

int state = 0;

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = A3, en = A5, d4 = A9, d5 = A10, d6 = A11, d7 = A12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int stepsPerRevolution = 200;  
const int rolePerMinute = 100;       

Stepper myStepper(stepsPerRevolution, 22, 26, 24, 28);

//A0 at f0 OUT
//A1 at f1 OUT
//A2 at f2 OUT
//A4 at f4 OUT
volatile unsigned char* port_f = (unsigned char*) 0x31; 
volatile unsigned char* ddr_f = (unsigned char*) 0x30;
volatile unsigned char* pin_f = (unsigned char*) 0x2f;

//A13 at k5 OUT
//A14 at k6 OUT
//A15 at k7 IN
volatile unsigned char* port_k = (unsigned char*) 0x108; 
volatile unsigned char* ddr_k = (unsigned char*) 0x107;
volatile unsigned char* pin_k = (unsigned char*) 0x106;

//2 at e4 IN
//3 at e5 IN
//5 at e3 OUT
volatile unsigned char* port_e= (unsigned char*) 0x2e; 
volatile unsigned char* ddr_e = (unsigned char*) 0x2d;
volatile unsigned char* pin_e = (unsigned char*) 0x2c;

//4 at g5 IN
volatile unsigned char* port_g= (unsigned char*) 0x14; 
volatile unsigned char* ddr_g = (unsigned char*) 0x13;
volatile unsigned char* pin_g = (unsigned char*) 0x12;

//6 at h3 OUT
//7 at h4 OUT
//8 at h5 OUT
//9 at 86 OUT
volatile unsigned char* port_h= (unsigned char*) 0x102; 
volatile unsigned char* ddr_h = (unsigned char*) 0x101;
volatile unsigned char* pin_h = (unsigned char*) 0x100;

//13 at b7 OUT
volatile unsigned char* port_b= (unsigned char*) 0x25; 
volatile unsigned char* ddr_b = (unsigned char*) 0x24;
volatile unsigned char* pin_b = (unsigned char*) 0x23;

//ADC
volatile unsigned char* my_ADMUX = (unsigned char*) 0x7C;
volatile unsigned char* my_ADCSRB = (unsigned char*) 0x7B;
volatile unsigned char* my_ADCSRA = (unsigned char*) 0x7A;
volatile unsigned int* my_ADC_DATA = (unsigned int*) 0x78;

void setup() 
{ 
  //ADC
  adc_init();
  
  //Initalizing all input output
  *ddr_f |= (0x01<<0);
  *ddr_f |= (0x01<<1);
  *ddr_f |= (0x01<<2);
  *ddr_f |= (0x01<<4);
  *ddr_k |= (0x01<<5);
  *ddr_k |= (0x01<<6);
  *ddr_k &= ~(0x01<<7);
  *port_k |= (0x01<<7);
  *ddr_e |= (0x01<<3);
  *ddr_e &= ~(0x01<<4);
  *port_e |= (0x01<<4);
  *ddr_e &= ~(0x01<<5);
  *port_e |= (0x01<<5);
  *ddr_g &= ~(0x01<<5);
  *port_g |= (0x01<<5);
  *ddr_h |= (0x01<<3);
  *ddr_h |= (0x01<<4);
  *ddr_h |= (0x01<<5);
  *ddr_h |= (0x01<<6);
  *ddr_b |= (0x01<<7);

  //Seting LCD pins HIGH and LOW
  *port_k &= ~(0x01<<6); //WRITE LOW
  *port_k |= (0x01<<5);
  *port_f &= ~(0x01<<0);
  *port_f &= ~(0x01<<4);
  *port_f &= ~(0x01<<2);
  *port_f |= (0x01<<1);
  // LCD PINS
  // pinMode(A14,OUTPUT);
  // pinMode(A13,OUTPUT);
  // pinMode(A4,OUTPUT);
  // pinMode(A0,OUTPUT);
  // pinMode(A2,OUTPUT);
  // pinMode(A1,OUTPUT);

  //LCD PINS
  // digitalWrite(A14,LOW); 
  // digitalWrite(A13,HIGH); 
  // digitalWrite(A4,LOW); 
  // digitalWrite(A0,LOW);
  // digitalWrite(A2,LOW);
  // digitalWrite(A1,HIGH);

  //Buttons
  // pinMode(2,INPUT);
  // pinMode(3, INPUT);
  // pinMode(4, INPUT);

  //Fan
  // pinMode(9, OUTPUT);

  //Lights
  // pinMode(5, OUTPUT);
  // pinMode(6, OUTPUT);
  // pinMode(7, OUTPUT);
  // pinMode(8, OUTPUT);

  lcd.begin(16, 2);

  //stepper
  myStepper.setSpeed(rolePerMinute);

} 

int value= 0;

int toggle = 1;
 
void loop() 
{ 
  *port_e &= ~(0x01<<3);
  //digitalWrite(5,LOW);
  *port_h &= ~(0x01<<3);
  //digitalWrite(6,LOW);
  *port_h &= ~(0x01<<4);
  //digitalWrite(7,LOW);
  *port_h &= ~(0x01<<5);
  //digitalWrite(8,LOW);
  *port_h &= ~(0x01<<6);
  //digitalWrite(9,LOW);
  if(state==0)
  {
    *port_e |= (0x01<<3);
    //digitalWrite(5,HIGH);
    if(*pin_g & (0x01 <<5)/*digitalRead(4)==HIGH*/)
    {
      state=1;
      delay(500);
    }
  }
  if(state==1)
  {
    *port_h |= (0x01<<4);
    //digitalWrite(7,HIGH);
  }
  else if(state==2)
  {
    *port_h |= (0x01<<3);
    //digitalWrite(6,HIGH);
    *port_h |= (0x01<<6);
    //digitalWrite(9,HIGH);
  }
  else if(state==4)
  {
    *port_h |= (0x01<<5);
    //digitalWrite(8,HIGH);
    lcd.clear();
    lcd.print("Water lvl Low!");
    if(*pin_g & (0x01 <<5)/*digitalRead(4)==HIGH*/)
    {
      state=0;
      delay(500);
    }
    if(*pin_e & (0x01 <<5)/*digitalRead(3)==HIGH*/)
    {
      state=1;
      delay(500);
    }    
  }
  if(state==1 || state==2)
  {
    value = adc_read(15);                    //analogRead(A15);
    lcd.clear();
    int readData = DHT.read11(outPin);

    float t = DHT.temperature;        
    float h = DHT.humidity;           

    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.print("Tmp = ");
    lcd.print(t);
    lcd.print("C");
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print("Humid = ");
    lcd.print(h);
    lcd.print("%");

    delay(250);

    if(h>15.00)
    {
      state=2;
    }
    else
    {
      state=1;
    }

    if(*pin_g & (0x01 <<5)/*digitalRead(4)==HIGH*/)
    {
      state=0;
      delay(500);
    }

    if(value>120)
    {
      state=4;
      delay(500);
    }
    if(*pin_e & (0x01 <<4)/*digitalRead(2)==HIGH*/)
    {
      myStepper.step(stepsPerRevolution*toggle);
      toggle*=-1;
      delay(500);
    }
  }
} 

void adc_init()
{
  // setup the A register
  *my_ADCSRA |= 0b10000000; // set bit   7 to 1 to enable the ADC
  *my_ADCSRA &= 0b11011111; // clear bit 6 to 0 to disable the ADC trigger mode
  *my_ADCSRA &= 0b11110111; // clear bit 5 to 0 to disable the ADC interrupt
  *my_ADCSRA &= 0b11111000; // clear bit 0-2 to 0 to set prescaler selection to slow reading
  // setup the B register
  *my_ADCSRB &= 0b11110111; // clear bit 3 to 0 to reset the channel and gain bits
  *my_ADCSRB &= 0b11111000; // clear bit 2-0 to 0 to set free running mode
  // setup the MUX Register
  *my_ADMUX  &= 0b01111111; // clear bit 7 to 0 for AVCC analog reference
  *my_ADMUX  |= 0b01000000; // set bit   6 to 1 for AVCC analog reference
  *my_ADMUX  &= 0b11011111; // clear bit 5 to 0 for right adjust result
  *my_ADMUX  &= 0b11100000; // clear bit 4-0 to 0 to reset the channel and gain bits
}
unsigned int adc_read(unsigned char adc_channel_num)
{
  // clear the channel selection bits (MUX 4:0)
  *my_ADMUX  &= 0b11100000;
  // clear the channel selection bits (MUX 5)
  *my_ADCSRB &= 0b11110111;
  // set the channel number
  if(adc_channel_num > 7)
  {
    // set the channel selection bits, but remove the most significant bit (bit 3)
    adc_channel_num -= 8;
    // set MUX bit 5
    *my_ADCSRB |= 0b00001000;
  }
  // set the channel selection bits
  *my_ADMUX  += adc_channel_num;
  // set bit 6 of ADCSRA to 1 to start a conversion
  *my_ADCSRA |= 0x40;
  // wait for the conversion to complete
  while((*my_ADCSRA & 0x40) != 0);
  // return the result in the ADC data register
  return *my_ADC_DATA;
}