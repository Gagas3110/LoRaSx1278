#include <SPI.h>
#include <LoRa.h>
#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16,2);            //adress lcd i2c
  
  
String tampung;
char karakter;
boolean komplit=false;
void setup() {
  lcd.begin(); 
lcd.backlight();
  delay(250);
  lcd.noBacklight();
  delay(250);
  lcd.backlight();
  
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");
lcd.setCursor(0,0);
lcd.print("LoRa Receiver");
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    lcd.setCursor(0,1);
    lcd.println("Starting LoRa failed!");
    while (1);
    
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    //Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      char inChar=(char)LoRa.read();
      tampung+= inChar;       //pengiriman perkarakter
      if(inChar=='~'){
        Serial.print(tampung);
         lcd.setCursor(2,1);
        
        lcd.print(tampung);
        lcd.print("      ");
        tampung="";
        
      }
      
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
