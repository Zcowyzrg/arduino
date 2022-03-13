/**
 * Stepper motor control with A4988 - Pololu 2128
 * ==================================================
 * Please, next time do not connect signals to 9V !!!
 * ==================================================
 */

// CD/DVD sleigh motor
#define STEPS_PER_TURN 20
#define STEP_PIN 8
#define DIR_PIN  9
#define MS1_PIN 10
#define MS2_PIN 11

void setup() {
  //Serial.begin(9600);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(MS1_PIN, OUTPUT);
  pinMode(MS2_PIN, OUTPUT);
  digitalWrite(DIR_PIN, 1); 
}

// pins 8--11 is PORTB 4--7 (Arduino Micro)
void make_turn(byte steps, byte ms1, byte ms2, byte mask, byte shift)
{
  digitalWrite(LED_BUILTIN, 1);
  digitalWrite(MS1_PIN, ms1);
  digitalWrite(MS2_PIN, ms2);
  for (int i=0; i<STEPS_PER_TURN * steps; i++) {
    for (byte j=0; j<16; j++) {
      digitalWrite(STEP_PIN, (j & mask) >> shift);
      delay(1);
    }
  }
  digitalWrite(LED_BUILTIN, 0);
}

void loop() {
  // setup FULL stepping
  make_turn(2, 0, 0, 0b1000, 3);
  delay(1000);
  make_turn(2, 1, 0, 0b0100, 2);
  delay(1000);
  make_turn(2, 0, 1, 0b0010, 1);
  delay(1000);
  make_turn(2, 1, 1, 0b0001, 0);
  delay(2000);
}
