#include <Servo.h>

// --- Motor Driver Pins (L298N) ---
#define IN1 22   // Left Front Forward
#define IN2 23   // Left Front Backward
#define IN3 24   // Right Front Forward
#define IN4 25   // Right Front Backward
#define ENA 8    // Left Speed (PWM)
#define ENB 9    // Right Speed (PWM)

// --- Robotic Arm Servos ---
Servo armBase;      // D2
Servo armShoulder;  // D3
Servo armElbow;     // D4
Servo wristRot;     // D5
Servo wristBend;    // D6
Servo gripper;      // D7

// --- Cleaning & Sensors ---
#define PUMP_PIN 10     // Water Jet Nozzle
#define TRIG_PIN 11     // Ultrasonic Trig
#define ECHO_PIN 12     // Ultrasonic Echo
#define LED_HEADLIGHT 13

// --- Settings ---
#define SPEED_FAST 180
#define SPEED_SLOW 120
#define OBSTACLE_DIST 30

void setup() {
  Serial.begin(9600); // Bluetooth/USB Command Link

  // Motors
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);

  // Tools
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_HEADLIGHT, OUTPUT);

  // Arm
  armBase.attach(2);
  armShoulder.attach(3);
  armElbow.attach(4);
  wristRot.attach(5);
  wristBend.attach(6);
  gripper.attach(7);

  stowArm(); // Reset arm to safe position
  digitalWrite(PUMP_PIN, LOW);
}

void loop() {
  // 1. Autonomous Obstacle Check
  long dist = readDistance();
  if (dist > 0 && dist < OBSTACLE_DIST) {
    stopMoving();
    // Use water jet if blockage is detected close
    digitalWrite(PUMP_PIN, HIGH);
    delay(2000); 
    digitalWrite(PUMP_PIN, LOW);
  }

  // 2. Remote Command Processing (from AI/Manual)
  if (Serial.available()) {
    char cmd = Serial.read();
    executeCommand(cmd);
  }
}

void executeCommand(char cmd) {
  switch (cmd) {
    // Movement
    case 'F': move(SPEED_FAST, SPEED_FAST); break;
    case 'B': move(-SPEED_FAST, -SPEED_FAST); break;
    case 'L': move(-SPEED_SLOW, SPEED_SLOW); break;
    case 'R': move(SPEED_SLOW, -SPEED_SLOW); break;
    case 'S': stopMoving(); break;

    // Arm Operations
    case 'G': grabSequence(); break; // Pickup trash
    case 'D': dropSequence(); break; // Drop trash
    case 'H': digitalWrite(LED_HEADLIGHT, !digitalRead(LED_HEADLIGHT)); break;
  }
}

void move(int left, int right) {
  if (left > 0) { digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); }
  else { digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); }
  analogWrite(ENA, abs(left));

  if (right > 0) { digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); }
  else { digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); }
  analogWrite(ENB, abs(right));
}

void stopMoving() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); analogWrite(ENB, 0);
}

long readDistance() {
  digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  return pulseIn(ECHO_PIN, HIGH) * 0.034 / 2;
}

void stowArm() {
  armBase.write(90); armShoulder.write(30); armElbow.write(30);
  wristRot.write(90); wristBend.write(90); gripper.write(90);
}

void grabSequence() {
  gripper.write(160); // Open
  armShoulder.write(120); armElbow.write(140); // Reach down
  delay(1000);
  gripper.write(40); // Close
  delay(500);
  stowArm(); // Lift
}

void dropSequence() {
  armBase.write(180); // Rotate to bin
  delay(500);
  gripper.write(160); // Drop
  delay(500);
  stowArm();
}