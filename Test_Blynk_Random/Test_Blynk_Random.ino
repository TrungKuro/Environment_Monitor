#define BLYNK_TEMPLATE_ID "TMPLwUaGg59B"
#define BLYNK_DEVICE_NAME "ESP Gateway"
#define BLYNK_AUTH_TOKEN "d-h5xU15_p8at43vrqFbIUHBMM3bmsQE"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

double pH = 0.0;
int tds = 0;
int ntu = 0;
double cur = 0.0;
double vol = 0.0;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "HshopLTK";
char pass[] = "HshopLTK@2311";

BlynkTimer timer;

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  Serial.println("Connect OK!");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  pH = random(0, 15) + (random(0, 10) / 10.0);
  tds = random(0, 1001);
  ntu = random(0, 3501);
  cur = random(-5, 6) + (random(0, 10) / 10.0);
  vol = random(0, 16) + (random(0, 10) / 10.0);

  /* Update pH, TDS, NTU, Current, Voltage */
  Blynk.virtualWrite(V0, pH);
  Blynk.virtualWrite(V1, tds);
  Blynk.virtualWrite(V2, ntu);
  Blynk.virtualWrite(V3, cur);
  Blynk.virtualWrite(V4, vol);
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
}
