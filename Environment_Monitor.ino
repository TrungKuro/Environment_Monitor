#include "Sensor_Environment.h"
#include "Pin_Connect.h"

/* ------------------------------------------------------------------------- */

float temperature = 25; // Giả định nhiệt độ dung dịch đo luôn lý tưởng là 25 độ C

float current = 0.0; // Đo dòng điện của nguồn
float voltage = 0.0; // Đo điện áp của nguồn

LiquidCrystal_I2C lcd(0x27, 20, 4);
// SoftwareSerial mySerial(2, 3); // RX, TX

// #define TIME_UPDATE 1000U // Đơn vị (ms)
// static unsigned long timepoint = millis();

String text;
int signal;

/* ----------------------------- Cảm biến độ pH ---------------------------- */

float voltage_pH;
float phValue = 0.0;

DFRobot_PH ph;

/* --------------------- Cảm biến tổng chất rắn hòa tan -------------------- */

float tdsValue = 0.0;

GravityTDS gravityTds;

/* ---------------------- Cảm biến đo độ đục của nước ---------------------- */

float voltage_NTU;
float ntuValue = 0.0;

/* ------------------------------------------------------------------------- */

void setup()
{
  DEBUG_BEGIN(115200);
  // mySerial.begin(115200);
  Serial1.begin(115200);

  /* Wait for ESP's confirmation response */
  DEBUG_PRINTLN("BEGIN");
  while (1)
  {
    while (Serial1.available() == 0)
    {
    }
    DEBUG_PRINTLN("GET INFO...");
    text = Serial1.readString();
    // DEBUG_PRINT(text);
    signal = text.indexOf("@");
    text = text.substring(signal, signal + 3);
    if (text == "@OK") // To know ESP had connected with Blynk!
    {
      DEBUG_PRINTLN("YES");
      Serial1.print("YES"); // For ESP know MEGA had ready!
      break;
    }
  }
  DEBUG_PRINTLN("END");

  /* Khởi tạo pH */
  ph.begin();

  /* Khởi tạo TDS */
  gravityTds.setPin(SIG_TCR);
  gravityTds.setAref(5.0);      // Reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(1024); // 1024 for 10bit ADC; 4096 for 12bit ADC
  gravityTds.begin();

  /* Khởi tạo LCD */
  lcd.init();
  lcd.clear();
  lcd.backlight();

  /* Tạo form mẫu sẵn trước */
  lcd.setCursor(0, 0); // Cột 1, Dòng 1
  lcd.print(" Vol 00.0V Cur 0.0A ");
  lcd.setCursor(0, 1); // Cột 1, Dòng 2
  lcd.print(" [pH]        = 00.0 ");
  lcd.setCursor(0, 2); // Cột 1, Dòng 3
  lcd.print(" [TDS (ppm)] = 0000 ");
  lcd.setCursor(0, 3); // Cột 1, Dòng 4
  lcd.print(" [NTU]       = 0000 ");
}

/* ------------------------------------------------------------------------- */

void loop()
{
  /* Tần suất cập nhập các giá trị */
  // if (millis() - timepoint >= TIME_UPDATE)
  // {
  //   timepoint = millis();

  //   //
  // }

  /* Đợi ESP gửi lệnh để đọc giá trị các cảm biến rồi gửi về ESP */
  DEBUG_PRINTLN("START");
  while (Serial1.available() == 0)
  {
  }
  DEBUG_PRINTLN("GET INFO...");
  text = Serial1.readString();
  signal = text.indexOf("@");
  text = text.substring(signal, signal + 5);
  if (text == "@READ")
  {
    /* Đo độ pH */
    voltage_pH = analogRead(SIG_PH) / 1024.0 * 5000;
    phValue = ph.readPH(voltage_pH, temperature);

    /* Đo độ ppm */
    gravityTds.setTemperature(temperature);
    gravityTds.update();
    tdsValue = gravityTds.getTdsValue();

    /* Đo độ NTU */
    voltage_NTU = analogRead(SIG_DDN) * (5.0 / 1024.0);
    ntuValue = convert_vol_to_NTU(voltage_NTU);

    /* Đo dòng điện DC (A) */
    current = ACS712_5A(SIG_CURRENT);

    /* Đo điện áp DC (V) */
    voltage = vol_divider_res(SIG_VOLTAGE);

    /* Cho hiển thị các thông số này lên màn hình LCD */
    display_LCD(&lcd, phValue, tdsValue, ntuValue, current, voltage);

    /* Gửi dữ liệu qua ESP */
    // reportToESP(&mySerial, phValue, tdsValue, ntuValue, current, voltage);
    reportToESP(&Serial1, phValue, tdsValue, ntuValue, current, voltage);

    DEBUG_PRINTLN("DONE");
  }
}