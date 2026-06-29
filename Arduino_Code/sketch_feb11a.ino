#include <Servo.h>

// Pin definitions
const int trigPin = 10;
const int echoPin = 11;
const int servoPin = 12;
const int redLED = 6;
const int greenLED = 7;
const int buzzer = 8;

// Variables
long duration;
int distance;
Servo myServo;

void setup() {
  // Ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // LED and Buzzer pins
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  // Serial communication
  Serial.begin(9600);
  
  // Attach servo
  myServo.attach(servoPin);
}

void loop() {
  // Rotate servo from 15 to 165 degrees
  for(int i=15; i<=165; i++) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    
    // Send data to Processing
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
    
    // Control LEDs and Buzzer
    indicator(distance);
  }
  
  // Rotate servo from 165 to 15 degrees
  for(int i=165; i>15; i--) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    
    // Send data to Processing
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
    
    // Control LEDs and Buzzer
    indicator(distance);
  }
}

// Function to calculate distance
int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  return distance;
}

// Function to control LED and Buzzer based on distance
void indicator(int dist) {
  if (dist < 20) {
    // Object is close (less than 20cm)
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(buzzer, HIGH);
  } else {
    // Object is far (more than 20cm)
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(buzzer, LOW);
  }
}