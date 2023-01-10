/* ------------------------------------------------------------------------- */
/*                                   CONFIG                                  */
/* ------------------------------------------------------------------------- */

#define BLYNK_TEMPLATE_ID "TMPLwUaGg59B"
#define BLYNK_DEVICE_NAME "ESP Gateway"
#define BLYNK_AUTH_TOKEN "d-h5xU15_p8at43vrqFbIUHBMM3bmsQE"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

/* ------------------------------------------------------------------------- */
/*                                  VARIABLE                                 */
/* ------------------------------------------------------------------------- */

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Test-ESP";
char pass[] = "123456789";

BlynkTimer timer;

double pH = 0.0;
int tds = 0;
int ntu = 0;
double cur = 0.0;
double vol = 0.0;

String text;
int sig1, sig2, sig3, sig4;

/* ------------------------------------------------------------------------- */
/*                                  FUNCTION                                 */
/* ------------------------------------------------------------------------- */

/* This function is called every time the device is connected to the Blynk.Cloud */
BLYNK_CONNECTED()
{
  Serial.println("@OK");

  /* Wait for MEGA's confirmation response */
  while (1)
  {
    while (Serial.available() == 0)
    {
    }
    text = Serial.readString();
    if (text == "YES") // For ESP know MEGA had ready!
    {
      break;
    }
  }
  // Serial.println("GO..."); // DEBUG
}

/* This function sends Arduino's uptime every second to Virtual Pin */
void myTimerEvent()
{
  /* Dữ liệu ngẫu nhiên, để test ESP với Blynk */
  // pH = random(0, 15) + (random(0, 10) / 10.0);
  // tds = random(0, 1001);
  // ntu = random(0, 3501);
  // cur = random(-5, 6) + (random(0, 10) / 10.0);
  // vol = random(0, 16) + (random(0, 10) / 10.0);

  /* ESP gửi lệnh để yêu cầu MEGA đọc các cảm biến và gửi về ESP */
  Serial.println("@READ");

  /* Đợi data từ MEGA gửi về để xử lý */
  while (Serial.available() == 0)
  {
  }
  text = Serial.readString();
  // Serial.println(text); // DEBUG

  /* Chỉ nhận chuỗi bắt đầu bằng kí tự '#' */
  if (text[0] == '#')
  {
    sig1 = text.indexOf(":");
    sig2 = text.indexOf(":", sig1 + 1);
    sig3 = text.indexOf(":", sig2 + 1);
    sig4 = text.indexOf(":", sig3 + 1);

    /* Test xử lý tách chuỗi */
    // Serial.print("pH : ");
    // Serial.println(text.substring(1, sig1));
    // Serial.print("TDS: ");
    // Serial.println(text.substring(sig1 + 1, sig2));
    // Serial.print("NTU: ");
    // Serial.println(text.substring(sig2 + 1, sig3));
    // Serial.print("Cur: ");
    // Serial.println(text.substring(sig3 + 1, sig4));
    // Serial.print("Vol: ");
    // Serial.println(text.substring(sig4 + 1));

    /* Xử lý tách chuỗi */
    pH = text.substring(1, sig1).toDouble();
    tds = text.substring(sig1 + 1, sig2).toInt();
    ntu = text.substring(sig2 + 1, sig3).toInt();
    cur = text.substring(sig3 + 1, sig4).toDouble();
    vol = text.substring(sig4 + 1).toDouble();

    /* Update pH, TDS, NTU, Current, Voltage to Server Blynk */
    Blynk.virtualWrite(V0, pH);
    Blynk.virtualWrite(V1, tds);
    Blynk.virtualWrite(V2, ntu);
    Blynk.virtualWrite(V3, cur);
    Blynk.virtualWrite(V4, vol);
  }
}

/* ------------------------------------------------------------------------- */
/*                                    MAIN                                   */
/* ------------------------------------------------------------------------- */

void setup()
{
  /* Debug console */
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

  /* Setup a function to be called every second */
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
}
