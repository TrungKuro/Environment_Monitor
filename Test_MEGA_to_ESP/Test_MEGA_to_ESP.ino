/* ---------------------- Test với code "ESP_to_MEGA" ---------------------- */

// String text;

// void setup()
// {
//   Serial1.begin(115200); // Opens serial 1 port
//   pinMode(LED_BUILTIN, OUTPUT);
//   digitalWrite(LED_BUILTIN, HIGH);

//   Serial1.print("Allo");
// }

// void loop()
// {
//   while (Serial1.available())
//   {
//     text = Serial1.readString();
//     if (text == "OK")
//     {
//       Serial1.print("Allo");
//       digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
//     }
//   }
//   delay(1000);
// }

/* ----------------------- Test với ESP kết nối Blynk ---------------------- */

String text;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200); // Opens serial 1 port

  /* Wait for ESP's confirmation response */
  Serial.println("BEGIN"); // DEBUG
  while (1)
  {
    while (Serial1.available() == 0)
    {
    }
    Serial.println("GET..."); // DEBUG
    text = Serial1.readString();
    // Serial.print(text); // DEBUG
    int sig = text.indexOf("@");
    text = text.substring(sig, sig + 3);
    if (text == "@OK") // To know ESP had connected with Blynk!
    {
      Serial.println("YES"); // DEBUG
      Serial1.print("YES");  // For ESP know MEGA had ready!
      break;
    }
  }
  Serial.println("END"); // DEBUG
}

void loop()
{
  //
}