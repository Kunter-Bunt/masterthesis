// Basic demo for accelerometer readings from Adafruit LIS3DH

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10
int intPin = 12;
//breakout address: 18
int LIS3DH_ADDR = 0x18; // change this to 0x19 for alternative i2c address
int reading = 0; //counter for number of readings taken - for diagnostic use

// software SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif


unsigned int readRegister(byte reg) {
  Wire.beginTransmission(LIS3DH_ADDR);
  Wire.write(reg);
  Wire.endTransmission();
  
  Wire.requestFrom(LIS3DH_ADDR, 1);
  return Wire.read();
}


void writeRegister(byte reg, byte data) {
  Wire.beginTransmission(LIS3DH_ADDR);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

/* Initialize accelerometer in the host processor. ----------------------------------*/
//It only needs to be executed one time after power up in initialization routine.
void init_ACC(void)
{
    // configurations for control registers
    writeRegister(0x20, 0x2F); //Write A7h into CTRL_REG1;      // Turn on the sensor, enable X, Y, Z axes with ODR = 100Hz normal mode. 8F for low power mode
    writeRegister(0x21, 0x09); //Write 09h into CTRL_REG2;      // High-pass filter (HPF) enabled
    writeRegister(0x22, 0x40); //Write 40h into CTRL_REG3;      // ACC AOI1 interrupt signal is routed to INT1 pin.
    writeRegister(0x23, 0x00); //Write 00h into CTRL_REG4;      // Full Scale = +/-2 g
    writeRegister(0x24, 0x08); //Write 08h into CTRL_REG5;      // Default value is 00 for no latching. Interrupt signals on INT1 pin is not latched. 
                                                                //Users don’t need to read the INT1_SRC register to clear the interrupt signal.
    // configurations for wakeup and motionless detection

    //THRESHOLD
    writeRegister(0x32, 0x04); //Write 10h into INT1_THS;          // Threshold (THS) = X LSBs * 16 mg/LSB = Y mg.
    //THRESHOLD


    
    writeRegister(0x33, 0x00); //Write 00h into INT1_DURATION;     // Duration = 1LSBs * (1/10Hz) = 0.1s.
    //readRegister();  //Dummy read to force the HP filter to set reference acceleration/tilt value
    writeRegister(0x30, 0x2A); //Write 2Ah into INT1_CFG;          // Enable XLIE, YLIE, ZLIE interrupt generation, OR logic.
 
}

void setup(void) {
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif

  pinMode(15, OUTPUT);

  Serial.begin(115200);
  Serial.println("LIS3DH test!");

  for (int i = 0x00; i <= 0x30; i++){
    if (! lis.begin(i)) {   // change this to 0x19 for alternative i2c address
      Serial.println("Couldnt start");
    }
    else Serial.println(i);
  }
  Serial.println("LIS3DH found!");
  
  lis.setRange(LIS3DH_RANGE_2_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");
  init_ACC();
}

void loop() {
  lis.read();      // get X Y and Z data at once
  // Then print out the raw data
  /*
  Serial.print("X:  "); Serial.print(lis.x); 
  Serial.print("  \tY:  "); Serial.print(lis.y); 
  Serial.print("  \tZ:  "); Serial.print(lis.z); 

  //Or....get a new sensor event, normalized 
  //Display the results (acceleration is measured in m/s^2) 

  /*
  sensors_event_t event; 
  lis.getEvent(&event);
   
  Serial.print("\t\tX: "); Serial.print(event.acceleration.x);
  Serial.print(" \tY: "); Serial.print(event.acceleration.y); 
  Serial.print(" \tZ: "); Serial.print(event.acceleration.z); 
  Serial.print(" m/s^2 ");
*/


  if(digitalRead(intPin) == HIGH) {
    Serial.print("   \tHIGH: ");
    Serial.print(reading++); Serial.print(",  ");
    Serial.print(readRegister(0x21)); Serial.print(",  "); //read register to reset high-pass filter 
    Serial.print(readRegister(0x26)); Serial.print(",  "); //read register to set reference acceleration
    Serial.print(readRegister(LIS3DH_REG_INT1SRC)); Serial.print(",  "); //Read INT1_SRC to de-latch;
    Serial.println();
  }
  else {
    //Serial.print("   \tLOW");
    //Serial.println();
  }
  digitalWrite(15, HIGH);
  delay(100); 
  digitalWrite(15, LOW);
}
