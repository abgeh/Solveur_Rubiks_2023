#include <Wire.h>
#include <ArduCAM.h>
#include <SPI.h>
#include "memorysaver.h"
//This demo can only work on OV2640_MINI_2MP_PLUS platform.
#if !(defined OV2640_MINI_2MP_PLUS)
  #error Please select the hardware platform and camera module in the ../libraries/ArduCAM/memorysaver.h file
#endif
#define BMPIMAGEOFFSET 54
const char bmp_header[54] PROGMEM =
//header from 24bit 320 x 240 image
{
0x42, 0x4D, 0x38, 0x84, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00,
0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00,
0x00, 0x00, 0x02, 0x84, 0x03, 0x00, 0x47, 0x30, 0x00, 0x00, 0x47, 0x30, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// set pin 7 as the slave select for the digital pot:
const int CS = 7;
const int USER_BUTTON_Pin = PC13;
ArduCAM myCAM( OV2640, CS );




void Capture(ArduCAM myCAM)
{
  uint32_t length = 0;
  myCAM.flush_fifo(); //Flush the FIFO
  myCAM.clear_fifo_flag(); //Clear the capture done flag
  myCAM.start_capture();//Start capture


  while (!myCAM.get_bit(ARDUCHIP_TRIG , CAP_DONE_MASK));

  length = myCAM.read_fifo_length();
  //Serial.print(F("FifoLength:,"));
  //Serial.print(length, DEC);
  //Serial.println(",");

  if (length >= MAX_FIFO_SIZE) //8M
  {
    Serial.println(F("Over size."));
    return ;
  }
  if (length == 0 ) //0 kb
  {
    Serial.println(F("Size is 0."));
    return ;
  }

  myCAM.CS_LOW();
  myCAM.set_fifo_burst();
  //Serial.print("Image:,");
  char VH, VL;
  int i = 0, j = 0;
  
  for (i = 0 ; i <240 ; i++)
  {
    for (j = 0; j < 320; j++)
    {
      VH = SPI.transfer(0x00);;
      VL = SPI.transfer(0x00);;  
      
     // RGB565 to RGB88 Conversion
      unsigned int val565 = VH*256 + VL;

      byte r = (val565 & 0xF800) >> 8;  //  >> 11 << 3
      byte b = (val565 & 0x07E0) >> 3;  // >> 5 << 2
      byte g = (val565 & 0x001F) << 3;  // >> 0 << 3

      Serial.print(r,DEC);
      Serial.print(" ");
      delayMicroseconds(90);
      Serial.print(b,DEC);
      Serial.print(" ");
      delayMicroseconds(90);
      Serial.print(g,DEC);
      Serial.print(" ");
      delayMicroseconds(90);    
    }
  }
  myCAM.CS_HIGH();          //Clear the capture done flag
  myCAM.clear_fifo_flag();
}


void setup() {
// put your setup code here, to run once:

uint8_t vid, pid;
uint8_t temp;
#if defined(__SAM3X8E__)
  Wire1.begin();
  Serial.begin(115200);
#else
  Wire.begin();
  Serial.begin(1000000);
#endif
pinMode(USER_BUTTON_Pin, INPUT_PULLUP);

Serial.println(F("ACK CMD ArduCAM Start! END"));    
pinMode(CS, OUTPUT);          // set the CS as an output:
digitalWrite(CS, HIGH);
SPI.begin();                  // initialize SPI: 
myCAM.write_reg(0x07, 0x80);  // Reset the CPLD
delay(100);
myCAM.write_reg(0x07, 0x00);
delay(100);
while(1){                      // Check if the ArduCAM SPI bus is OK
  myCAM.write_reg(ARDUCHIP_TEST1, 0x55);
  temp = myCAM.read_reg(ARDUCHIP_TEST1);
  if (temp != 0x55){
    Serial.println(F("ACK CMD SPI interface Error! END"));
    delay(1000);continue;
  }else{
    Serial.println(F("ACK CMD SPI interface OK. END"));break;
  }
}
 
while(1){                         //Check if the camera module type is OV2640
  myCAM.wrSensorReg8_8(0xff, 0x01);
  myCAM.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
  myCAM.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
  if ((vid != 0x26 ) && (( pid != 0x41 ) || ( pid != 0x42 ))){
    Serial.println(F("ACK CMD Can't find OV2640 module! END"));
    delay(1000);continue;
  }
  else{
    Serial.println(F("ACK CMD OV2640 detected. END"));break;
  } 
}

//Change to BMP capture mode and initialize the OV2640 module
myCAM.set_format(BMP);
myCAM.InitCAM();
delay(1000);
}


void loop()
{    //put your main code here, to run repeatedly: 
 if (digitalRead(USER_BUTTON_Pin) == LOW) { // check if the user button is pressed (active LOW)
    for (int i=0;i<1;i++) {
      Capture(myCAM);
      //delay (2000);
    }
  }
}
