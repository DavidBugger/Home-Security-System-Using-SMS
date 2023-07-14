#include <SoftwareSerial.h>

SoftwareSerial sim800l(10, 11);  // RX, TX

int pirOutput = 9;

void setup() {
  Serial.begin(9600);
  sim800l.begin(9600);

  pinMode(pirOutput, INPUT);
  digitalWrite(pirOutput, LOW);
}

void loop() {
  if (digitalRead(pirOutput) == HIGH) {
    Serial.println("Intruder detected!");

    delay(2000);  // Delay for stability

    sim800l.println("AT+CMGF=1");                      // Set SMS mode to text
    delay(100);
    sim800l.println("AT+CMGS=\"+2348107701730\"");     // Nigerian phone number with country code
    delay(100);
    sim800l.println("Intruder detected!");             // Message content
    delay(100);
    sim800l.write(0x1A);                               // End of message character
    delay(100);
  }

  delay(1000);  // Adjust delay as needed between PIR sensor readings
}
