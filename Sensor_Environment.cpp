#include "Sensor_Environment.h"

#define SAMPLES_CUR 100 // Số lần lấy mẫu mỗi lần đo Dòng điện
#define SAMPLES_VOL 100 // Số lần lấy mẫu mỗi lần đo Điện áp

/* ---------------------- Hàm chuyển Điện áp sang NTU ---------------------- */

float convert_vol_to_NTU(float vol)
{
  /*
  ** [y], đơn vị độ đục nước (NTU)
  ** [x], đơn vị điện áp (V)
  **
  ** y = -1120.4*(x^2) + 5742.3*(x) - 4352.9
  */
  float value = (-1120.4 * vol * vol) + (5742.3 * vol) - 4352.9;
  return value;
}

/* ---------------------- Hàm đọc dòng điện từ ACS712 ---------------------- */

float ACS712_5A(byte pin)
{
  /*
  ** Với mode 5A : average = average + (.0264 * analogRead(A0) -13.51);
  ** Với mode 20A: average = average + (.049 * analogRead(A0) -25);
  ** Với mode 30A: average = average + (.742 * analogRead(A0) -37.8);
  **
  ** Trên các bo mạch dựa trên ATmega (UNO, Nano, Mini, Mega)
  ** Mất khoảng 100 micro giây (0,0001 giây) để đọc một đầu vào Analog
  ** Vì vậy tốc độ đọc tối đa là khoảng 10.000 lần một giây.
  **
  ** Hàm này cho lấy mẫu 'SAMPLES_CUR' lần, mỗi lần khoảng 0.5ms
  */
  float average = 0.0;
  for (int i = 0; i < SAMPLES_CUR; i++)
  {
    /* For the 5A mode */
    average = average + (.0264 * analogRead(pin) - 13.51);
    delayMicroseconds(500);
  }
  return average / SAMPLES_CUR;
}

/* ----------------------------- Hàm đo điện áp ---------------------------- */

float vol_divider_res(byte pin)
{
  /*
  ** Dùng nguyên lý trở phân áp, với tỉ lệ 1/3
  ** Khi nguồn vào Max là 15V (IN) thì nguồn ra là 5V (OUT)
  **
  ** IN - 0   OUT - 0
  ** ------ = ------- ==> IN = 3 * OUT
  ** 15 - 0    5 - 0
  **
  ** Với nguồn ra 5V, phù hợp cho các bo mạch đọc được
  ** Công thức dưới đây, đại lượng 'vol' cũng chính là 'OUT'
  **
  ** analog   vol
  ** ------ = --- ==> vol = 5 * analog / 1024
  **  1024     5
  **
  ** Hàm này cho lấy mẫu 'SAMPLES_VOL' lần, mỗi lần khoảng 0.5ms
  */
  float average = 0.0;
  for (int i = 0; i < SAMPLES_VOL; i++)
  {
    average = average + (analogRead(pin) * (15.0 / 1024.0));
    delayMicroseconds(500);
  }
  return average / SAMPLES_VOL;
}

/* ------------------- Hàm hiển thị các thông tin lên LCD ------------------ */

/* Các giá trị sẽ hiển thị...
** "pH: 00.0"
** "TDS: 0000ppm"
** "NTU: 0000"
** "Vol: 00.0V"
** "Cur: 0.0A"
**
** Sắp xếp để hiển thị lên màn hình LCD...
**    01234567890123456789
**   ----------------------
** 0 | Vol 00.0V Cur 0.0A |
** 1 | [pH]        = 00.0 |
** 2 | [TDS (ppm)] = 0000 |
** 3 | [NTU]       = 0000 |
**   ----------------------
*/
void display_LCD(LiquidCrystal_I2C *lcdPtr, float pH, float tds, float ntu, float cur, float vol)
{
  /* Cột 6, Dòng 1 */
  lcdPtr->setCursor(5, 0);
  lcdPtr->print(F("     "));
  lcdPtr->setCursor(5, 0);
  lcdPtr->print(vol, 1);
  lcdPtr->print("V");

  /* Cột 16, Dòng 1 */
  lcdPtr->setCursor(15, 0);
  lcdPtr->print(F("     "));
  lcdPtr->setCursor(15, 0);
  lcdPtr->print(cur, 1);
  lcdPtr->print("A");

  /* Cột 16, Dòng 2 */
  lcdPtr->setCursor(15, 1);
  lcdPtr->print(F("     "));
  lcdPtr->setCursor(15, 1);
  lcdPtr->print(pH, 1);

  /* Cột 16, Dòng 3 */
  lcdPtr->setCursor(15, 2);
  lcdPtr->print(F("     "));
  lcdPtr->setCursor(15, 2);
  lcdPtr->print(tds, 0);

  /* Cột 16, Dòng 4 */
  lcdPtr->setCursor(15, 3);
  lcdPtr->print(F("     "));
  lcdPtr->setCursor(15, 3);
  lcdPtr->print(ntu, 0);
}

/* ---------------- Cho Uno gửi dữ liệu các cảm biến lên ESP --------------- */

// void reportToESP(SoftwareSerial *dataPtr, float pH, float tds, float ntu, float cur, float vol)
void reportToESP(HardwareSerial *dataPtr, float pH, float tds, float ntu, float cur, float vol)
{
  String data = "";

  data += ("#" + String(pH, 1));
  data += (":" + String(tds, 0));
  data += (":" + String(ntu, 0));
  data += (":" + String(cur, 1));
  data += (":" + String(vol, 1));

  dataPtr->print(data);
}