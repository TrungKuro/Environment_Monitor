// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLwUaGg59B"
#define BLYNK_DEVICE_NAME "ESP Gateway"
#define BLYNK_AUTH_TOKEN "d-h5xU15_p8at43vrqFbIUHBMM3bmsQE"

// Comment this out to disable prints and save space
// #define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "HshopLTK";
char pass[] = "HshopLTK@2311";

#define LED D4
#define BTN D3
bool btnState = HIGH;

// This function is called every time the Virtual Pin 5 state changes
BLYNK_WRITE(V5)
{
  // Set incoming value from pin V5 to a variable
  int value = param.asInt();

  digitalWrite(LED, value);
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();

  if (digitalRead(BTN)) // Release = HIGH
  {
    btnState = HIGH;
  }
  else // Push = LOW
  {
    if (btnState)
    {
      digitalWrite(LED, !digitalRead(LED));
      Blynk.virtualWrite(V5, digitalRead(LED));
      delay(100);

      btnState = LOW;
    }
  }
}
