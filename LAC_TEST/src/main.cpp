#include <Arduino.h>

#define MOTOR_IN1 9
#define MOTOR_IN2 10
#define LAC_Feedback A0
const int positionFeedbackPin = A0;
int pos;                      // Actuator Position
float conNum = 0.143695;
int direction = 0; // 0 for stop, 1 for extending, -1 for retracting

float readPotentiometer(void) {
  int pos;
  pos = conNum * (analogRead(LAC_Feedback)); 
  return pos;
}
void setup() {
  Serial.begin(9600);
  Serial.println("Enter new position between 0 and 146mm: ");

  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(LAC_Feedback, INPUT);
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
}


void loop() {
  while (true) {
    if (Serial.available() > 0) {
      // If there is serial data available, read the desired position from the operator as a string
      String input = Serial.readStringUntil('\n');
      input.trim();
      
      // Check if the input is a valid integer
      if (input.length() > 0 && isDigit(input.charAt(0))) {
        int desiredPos = input.toInt();
        
        // Check if the desired position is within a valid range (0 to 146)
        if (desiredPos >= 0 && desiredPos <= 146) {
          // Calculate the direction based on the desired position
          if (desiredPos > pos) {
            direction = 1; // Extend
          } else if (desiredPos < pos) {
            direction = -1; // Retract
          } else {
            direction = 0; // Stop (already at the desired position)
          }
          
          // Move the actuator until it reaches the desired position
          while (pos != desiredPos && direction != 0) {
            // Check and update the position
            pos = readPotentiometer();
            Serial.print("position: ");
            Serial.print(pos);
            Serial.println(" mm");
  
            if (direction == 1) {
              digitalWrite(MOTOR_IN1, LOW); // extend
              digitalWrite(MOTOR_IN2, HIGH);
            } else {
              digitalWrite(MOTOR_IN1, HIGH); // retract
              digitalWrite(MOTOR_IN2, LOW);
            }
  
            delay(100);
          }
  
          // Stop the actuator when it reaches the desired position
          digitalWrite(MOTOR_IN1, LOW);
          digitalWrite(MOTOR_IN2, LOW);
        } else {
          // Invalid desired position
          Serial.println("Invalid position. Please enter a value between 0 and 146.");
          Serial.println("Enter new position ");
        }
      } else {
        // Invalid input format
        Serial.println("Invalid input format. Please enter a valid integer.");
      }
    }
  }
}
