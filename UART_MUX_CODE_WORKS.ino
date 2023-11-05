#include <SoftwareSerial.h>

SoftwareSerial mySerial(0, 1); // RX, TX

// Define SN74LV4052A control pins A, B, and INH
#define CONTROL_A 2
#define CONTROL_B 3
#define INH 4

unsigned long previousMillis = 0;
const long interval = 1000; // Send "Hello, Dalmast" every 1000 milliseconds (1 second)

void setup() {
  mySerial.begin(9600);  // Set the baud rate to 9600

  pinMode(CONTROL_A, OUTPUT);
  pinMode(CONTROL_B, OUTPUT);
  pinMode(INH, OUTPUT);

  digitalWrite(INH, LOW); // Ensure INH is always low
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Save the last time a message was sent
    previousMillis = currentMillis;

    select_channel();

    // Send "Hello, Dalmast"
    mySerial.println("Hello, Dalmast");
  }

  // Add any additional code or tasks you need to perform in the loop
}

void select_channel() {
  digitalWrite(CONTROL_B, LOW); // B=High, A=Low for Channel 2
  digitalWrite(CONTROL_A, LOW);
  digitalWrite(INH, LOW);
}
