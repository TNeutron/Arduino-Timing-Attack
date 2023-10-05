#include <Arduino.h>

const char *in_memory_password = "957664";
const int led_pin = 13;

void setup()
{
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
}

int check_unsafely(char *input)
{
  int i;

  for (i = 0; i < 6; i++)
    if (input[i] != in_memory_password[i])
      return 0;
  return 1;
}

int check_safely(char *input)
{
  int i;
  bool result = true;
  for (int i = 0; i < 6; i++) {
    if(input[i] != in_memory_password[i]) result = false;
  }
  return result;
}

void loop()
{
  char buf[32];
  int r;

  Serial.setTimeout(10);
  while (!Serial.available())
    delay(10);
  r = Serial.readBytes(buf, 31);
  buf[r] = 0;

  digitalWrite(led_pin, HIGH);
  r = check_unsafely(buf);
  digitalWrite(led_pin, LOW);

  if (r)
    Serial.println("Password Matched");
  else
    Serial.println("Wrong password");
}