
//  (VCC)--(2k)--+--(+TEPT-)--(GND)
//               `(A0)
// Arduino/hardware/arduino/avr/variants/leonardo/pins_arduino.h

#define ANALOG_PIN A0

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(ANALOG_PIN);

  // print out the value you read:
  if (Serial) {
    Serial.println(sensorValue);
    // send keys to arduino to reset the scale
    if (Serial.available() > 0) {
      Serial.read();
      // realign plotter scale to 0--1000
      Serial.println(0);
      Serial.println(1000);
    }
  }
  delay(1000/50);
  digitalWrite(LED_BUILTIN, (millis() / 1024) & 0x01);
}
