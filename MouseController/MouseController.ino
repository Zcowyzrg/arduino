
#define BUTTON_PIN 7
#define ENC_PIN_A  2
#define ENC_PIN_B  3

static const int ButtonDebounceMax = 50;

volatile int8_t buttonDebounce = 0;
volatile int8_t ledState = LOW;
volatile int8_t encDir = 0;
volatile int8_t encChanged = 0;
volatile int8_t buttonChanged = 0;
volatile unsigned long buttonDebounceTime = 0;

void buttonISR()
{
  if (buttonDebounce == 0) {
    buttonDebounce = 1;
  }
  buttonDebounceTime = millis();
}

void encPinAISR()
{
  uint8_t aState = digitalRead(ENC_PIN_A);
  uint8_t bState = digitalRead(ENC_PIN_B);
  if (aState ^ bState) {
    ++encDir;
  } else {
    --encDir;
  }
  encChanged = 1;
}


void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(ENC_PIN_A, INPUT_PULLUP);
  pinMode(ENC_PIN_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(ENC_PIN_A), encPinAISR, CHANGE);
}


void loop()
{
  delay(1000/20);
  if (buttonDebounce == 1 && ((millis() - buttonDebounceTime) > ButtonDebounceMax)) {
    buttonDebounce = 0;
    encDir = 0;
    encChanged = 1;
    //ledState ^= 1;
    //digitalWrite(LED_BUILTIN, ledState);
    Serial.println("Button pressed");
  }
  if (encChanged) {
    Serial.print("ENC:");
    Serial.println(encDir);
    analogWrite(LED_BUILTIN, abs(encDir * 10));
    encChanged = 0;
  }
}
