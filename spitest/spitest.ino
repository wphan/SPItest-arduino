/* SPI - SERIAL BRIDGE FOR ARDUINO
 * 
 * For Arduino UNO
 * MOSI: 11 or ICSP-4
 * MISO: 12 OR ICSP-1
 * SCK:  13 or ICSP-3
 * SS(slave): 10
 */

#include <SPI.h>

const int overoCS = 10;
const int numbytes = 32;
SPISettings settingsOvero(12000000, LSBFIRST, SPI_MODE0);

void setup() {
  pinMode(overoCS, OUTPUT);
  SPI.begin();
  Serial.begin(115200);
}

void loop() {
  char buffer[numbytes]; 
  
  //reading from Overo
  SPI.beginTransaction(settingsOvero);
  digitalWrite(overoCS, LOW);
  for(int i = 0; i<numbytes; i++)
      buffer[i] = SPI.transfer(0);
  digitalWrite(overoCS, HIGH);
  Serial.println("read");
  SPI.endTransaction();
  
  
  //write to Overo, data in reverse :O
  SPI.beginTransaction(settingsOvero);
  digitalWrite(overoCS, LOW);
  for(int i = (numbytes - 1); i > 0; i--)
    SPI.transfer(buffer[i]);
  digitalWrite(overoCS, HIGH);
  Serial.println("wrote");
  SPI.endTransaction();
  
  Serial.println("hi");
  delay(1);
}
