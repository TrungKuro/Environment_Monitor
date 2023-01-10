String text;

void setup()
{
  Serial.begin(115200); // Opens serial port
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop()
{
  while(Serial.available())
  {
    text = Serial.readString();
    if(text == "Allo")
    {
      Serial.print("OK");
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
  }
  delay(1000);
}
