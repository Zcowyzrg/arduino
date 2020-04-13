
// AtMega32U4: Arduino/hardware/arduino/avr/variants/leonardo/pins_arduino.h
// http://pinoutguide.com/images/arduino/micro.png
// Servo: red=vcc black=gnd white=pwm(D9)

#include <Servo.h>

#define JOY_X      A2
#define JOY_Y      A3
#define SERVO_PIN   9

uint8_t led_counter = 0;
Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
}

void loop() {
  int joy_x = analogRead(JOY_X);
  int joy_y = analogRead(JOY_Y);
  // adjust the servo in (0, 180) range; 90 is the mid-point
  int val = map(joy_y, 0, 1023, 0, 180);
  servo.write(val);
  // print the value if the port is open
  if (Serial) {
    Serial.print(joy_x);
    Serial.print(' ');
    Serial.println(joy_y);
    // send keys to arduino to reset the scale
    if (Serial.available() > 0) {
      Serial.read();
      // realign plotter scale to 0--1000
      Serial.println(0);
      Serial.println(1000);
    }
  }
  delay(20);        // delay in between reads for stability
  ++led_counter;
  digitalWrite(LED_BUILTIN, (led_counter >> 5) & 1);
}
