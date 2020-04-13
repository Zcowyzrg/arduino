#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Also based on YWRobot LCM1602 IIC V1
// @see https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/schematics#!pin-configuration
// @see http://henrysbench.capnfatz.com/henrys-bench/arduino-displays/ywrobot-lcm1602-iic-v1-lcd-arduino-tutorial/
// @see https://pinoutguide.com/images/arduino/micro.png - SDA=D2 SCL=D3
// Control over backlight only when properly initialized with full constructor

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

uint8_t xpos = 0;
uint8_t ypos = 1;
bool escaped_mode = false;

static const uint8_t MAX_LCD_COLUMN = 16;
static const uint8_t MAX_LCD_ROW = 2;

void setup()
{
  Serial.begin(9600);
  lcd.begin(MAX_LCD_COLUMN, MAX_LCD_ROW);
  //lcd.backlight();    // turned on by default
  lcd.setCursor(0, 0);  // (column, line)
  lcd.print("READY.");
  lcd.setCursor(xpos, ypos);
  //lcd.autoscroll();
  lcd.cursor();
}

void advance_cursor(uint8_t num)
{
  xpos += num;
  if (xpos == MAX_LCD_COLUMN) {
    ypos = 1 - ypos;
    xpos = 0;
    lcd.setCursor(xpos, ypos);
  }
}

void loop()
{
  if (Serial) {
    while (Serial.available()) {
      // let the backtick (`) be our escape character
      int c = Serial.read();
      if (escaped_mode) {
        switch (c) {
          case 'l':
            lcd.clear();
            xpos = ypos = 0;
            break;
          case 'b':
            lcd.noBlink();
            break;
          case 'B':
            lcd.blink();
            break;
          case 'c':
            lcd.noCursor();
            break;
          case 'C':
            lcd.cursor();
            break;
          case '`':
            lcd.write('`');
            advance_cursor(1);
            break;
          default:
            lcd.home();
            lcd.print("[lbBcC]");
            advance_cursor(7);
            break;
        }
        escaped_mode = false;
      } else if (c == '`') {
        escaped_mode = true;
      } else {
        lcd.write(c);
        advance_cursor(1);
      }
    }
  }
  delay(20);
  // blink internal LED every ~1s
  unsigned long int tm_seconds = millis() / 1024;
  digitalWrite(LED_BUILTIN, tm_seconds & 0x01);
}
