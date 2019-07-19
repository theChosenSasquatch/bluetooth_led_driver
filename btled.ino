#include "BluetoothSerial.h"

char input[9], rgb[3] = {0};
BluetoothSerial SerialBT;

void setup() {
  for (uint8_t i = 0; i < 3; i++) {
    pinMode(12 + i, OUTPUT);
    ledcAttachPin(12 + i, i); //connects GPIO to led driver interface
    ledcSetup(i, 12000, 8); //configures PWM stats.
    ledcWrite(i, 256 - rgb[i]); //turns off to start
  }
  SerialBT.begin("FBI Surveillence Insect #357");
}

void loop() {
  if (SerialBT.available()) {
    for (byte i = 0; i < 11; i++) input[i] = SerialBT.read();
    sscanf(input, "%3u%3u%3u", &rgb[0], &rgb[1], &rgb[2]);
    for (byte i = 0; i < 3; i++) ledcWrite(i, 256 - rgb[i]);
  }
  delay(50);
}
