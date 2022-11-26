#include <SPI.h>
#include <LoRa.h>

int sensorValue;
float gasSensor=0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  sensorValue=analogRead(gasSensor);
  Serial.print("nilaiGasCO: ");
  Serial.println(sensorValue);

  // send packet
  LoRa.beginPacket();
  //LoRa.print("Gas CO:  ");
  LoRa.print(sensorValue);
  LoRa.print("ppm");
  LoRa.print("~");
  LoRa.endPacket();

  
  delay(5000);
}