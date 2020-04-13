
#include <OneWire.h>
#include <DallasTemperature.h>

// Don't use pin 13 with LED for parasitic mode
#define ONE_WIRE_BUS A0

/*    Connection:
 *    DS18B20 = (GND, DATA, VCC)
 *    DS18B20.DATA <-> 4.7k <-> VCC
 *    DS18B20.DATA <-> A0
 *    DS18B20.VCC = +5V (optional)
 */

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup(void)
{
  Serial.begin(115200);
  sensors.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(void)
{
  //unsigned int t0 = millis();
  sensors.requestTemperatures();
  if (sensors.isParasitePowerMode()) {
    Serial.print("(P) ");
  }
  Serial.println(sensors.getTempCByIndex(0));
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}
