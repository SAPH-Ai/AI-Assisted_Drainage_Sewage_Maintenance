#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// --- Sensors ---
#define PIN_GAS A0        // MQ135 Methane/Ammonia
#define PIN_TURBIDITY A1  // Water Quality
#define PIN_LDR A2        // Light Level
#define PIN_DHT 2         // Temp & Humidity

// --- Actuators ---
#define PIN_CHEM_PUMP 3   // NaOH/NaClO Spray
#define PIN_UV_LIGHT 4    // UV Sanitizer
#define PIN_HEADLIGHT 5   // White LED

// --- 6-Wheel Drive (2-Channel Logic for 6 Parallel Motors) ---
#define ENA 6   // Left Side Speed (Motors 1,2,3)
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 10
#define ENB 11  // Right Side Speed (Motors 4,5,6)

// --- Objects ---
LiquidCrystal_I2C lcd(0x27, 20, 4);
DHT dht(PIN_DHT, DHT11);

// --- Thresholds ---
const int GAS_ALERT = 500;       // >50% Flammable
const int WATER_CLEAN = 600;     // High analog val = Clean
const int DARKNESS = 300;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init(); lcd.backlight();

  // Config Outputs
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  
  pinMode(PIN_CHEM_PUMP, OUTPUT);
  pinMode(PIN_UV_LIGHT, OUTPUT);
  pinMode(PIN_HEADLIGHT, OUTPUT);

  lcd.setCursor(0,0); lcd.print("Sewage Bot Active");
  delay(1000); lcd.clear();
}

void loop() {
  // 1. Environmental Monitoring
  int gas = analogRead(PIN_GAS);
  int turb = analogRead(PIN_TURBIDITY);
  int light = analogRead(PIN_LDR);
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  updateDisplay(hum, temp, gas, turb);
  checkSafety(gas, turb, light);

  // 2. Navigation Command (Serial from Controller)
  if (Serial.available()) {
    char cmd = Serial.read();
    driveRobot(cmd);
  }
}

void checkSafety(int gas, int turb, int light) {
  // Gas Mitigation
  if (gas > GAS_ALERT) {
    digitalWrite(PIN_CHEM_PUMP, HIGH); // Spray chemical
  } else {
    digitalWrite(PIN_CHEM_PUMP, LOW);
  }

  // Water Sanitization (if dirty)
  if (turb < WATER_CLEAN) {
    digitalWrite(PIN_UV_LIGHT, HIGH); // Activate UV
  } else {
    digitalWrite(PIN_UV_LIGHT, LOW);
  }

  // Auto-Headlight
  if (light < DARKNESS) {
    digitalWrite(PIN_HEADLIGHT, HIGH);
  } else {
    digitalWrite(PIN_HEADLIGHT, LOW);
  }
}

void updateDisplay(float h, float t, int g, int w) {
  lcd.setCursor(0,0); 
  lcd.print("T:"); lcd.print((int)t); lcd.print("C H:"); lcd.print((int)h); lcd.print("%");
  
  lcd.setCursor(0,1);
  lcd.print("Gas: "); 
  if(g > GAS_ALERT) lcd.print("DANGER!"); 
  else lcd.print("Safe");

  lcd.setCursor(0,2);
  lcd.print("H2O Qual: "); lcd.print(w);
}

void driveRobot(char cmd) {
  switch(cmd) {
    case 'F': setMotors(150, 150); break;
    case 'B': setMotors(-150, -150); break;
    case 'L': setMotors(-130, 130); break;
    case 'R': setMotors(130, -130); break;
    case 'S': setMotors(0, 0); break;
  }
}

void setMotors(int left, int right) {
  // Left Side (3 Motors Parallel)
  if (left > 0) { digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); }
  else { digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); }
  analogWrite(ENA, abs(left));

  // Right Side (3 Motors Parallel)
  if (right > 0) { digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); }
  else { digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); }
  analogWrite(ENB, abs(right));
}