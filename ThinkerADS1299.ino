/*
  ADS1299 lib was developed by Conor Russomanno (June 2013)
  This example uses the ADS1299 Arduino Library, a software bridge between the ADS1299 TI chip and
  Arduino. See http://www.ti.com/product/ads1299 for more information about the device and the reference
  folder in the ADS1299 directory for more information about the library.

  Note: this Library and example file are still in early stages of development.

  ESP8266 SPI Master Demo Sketch
  Connect the SPI Master device to the following pins on the esp8266:

  GPIO    NodeMCU   Name  |   Uno
 ===================================
   15       D8       SS   |   D10
   13       D7      MOSI  |   D11
   12       D6      MISO  |   D12
   14       D5      SCK   |   D13

*/
#define DEBUG 1
#include <SPI.h>
#include <ADS1299.h>

ADS1299 ADS;

//Arduino Uno - Pin Assignments; Need to use ICSP for later AVR boards
// SCK = 13
// MISO [DOUT] = 12
// MOSI [DIN] = 11
// CS = 10;
// DRDY = 9;

//  0x## -> Arduino Hexadecimal Format
//  0b## -> Arduino Binary Format

boolean deviceIDReturned = false;
boolean startedLogging = false;

uint8_t counter = 0;



boolean debugStart() {

  byte deviceID = ADS.getDeviceID();
#ifdef DEBUG
  Serial.print(millis()); Serial.print("ms: device id "); ADS.printHex(deviceID);
#endif

//  if (deviceID != ADS_ID) {
//    Serial.print("\n\n\nPEACEOUT\n\n\n");
//    return false;
//  }

  //Read ADS1299 Register at address 0x00 (see Datasheet pg. 35 for more info on SPI commands)
#ifdef DEBUG
  Serial.print(millis()); Serial.println("ms 2 register at 0x00\n");
#endif
  ADS.RREG(0x00);

  //PRINT ALL REGISTERS... Read 0x17 addresses starting from address 0x00 (these numbers can be replaced by binary or integer values)
#ifdef DEBUG
  Serial.print(millis()); Serial.print("ms 3 print registers");
#endif
  ADS.printRegisters();

  //Write register command (see Datasheet pg. 38 for more info about WREG)
  uint8_t writeVal = 0b11010110;
#ifdef DEBUG
  Serial.print(millis()); Serial.print("ms 4 write register CONFIG1 "); ADS.printHex(writeVal);
#endif
  ADS.WREG(CONFIG1, writeVal);

  //Repeat PRINT ALL REGISTERS to verify that WREG changed the CONFIG1 register
#ifdef DEBUG
  Serial.print(millis()); Serial.println("ms 5 print registers");
#endif
  ADS.printRegisters();

  //Start data conversions command
  ADS.START(); //must start before reading data continuous
#ifdef DEBUG
  Serial.print(millis()); Serial.println("ms 6 ADS started");
#endif

  return true;
}
void setup() {

#ifdef DEBUG
  Serial.begin(115200);
  Serial.println();
  Serial.print(millis()); Serial.println("ms START");
#endif

  ADS.setup(4, 13, false); // (DRDY pin, CS pin);
  delay(10);  //delay to ensure connection


#ifdef DEBUG
  Serial.print(millis()); Serial.println("ms 0 Reset ads");
#endif
  ADS.RESET();



#ifdef DEBUG
  if (debugStart()) {
    Serial.print(millis()); Serial.println("ms ADS STARTED ads");
  } else {
    Serial.print(millis()); Serial.println("ms !ERROR! ADS FAILED STARTED ads");
  }
  Serial.print("DRDY: "); Serial.println(digitalRead(ADS.DRDY));
#endif
  ADS.RDATAC();
}

void loop(){
  if (Serial.available()) {
    Serial.print(Serial.read());
    debugStart();
  }
  //print data to the serial console for only the 1st 10seconds of
  // while(millis()<10000){
  //   if(startedLogging == false){
  //     Serial.print("Millis: "); //this is to see at what time the data starts printing to check for timing accuracy (default sample rate is 250 sample/second)
  //     Serial.println(millis());
  //     startedLogging = true;
  //   }
  //
  //   //Print Read Data Continuous (RDATAC) to Ardiuno serial monitor...
  //   //The timing of this method is not perfect yet. Some data is getting lost
  //   //and I believe its due to the serial monitor taking too much time to print data and not being ready to recieve to packets
  //   ADS.updateData();
  // }
  ADS.updateData();
}

