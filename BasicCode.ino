#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD (Address 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int micPin = A0; // KY-038 Analog Output
const int fanPin = 9; // PWM pin to 2N2222A base via 220Ω resistor
const int greenLed = 6; // Green LED (Running)
const int redLed = 7; // Red LED (Silence)

// Calibration Constants (Adjust via Serial Monitor)
const int SILENCE_THRESHOLD = 25; // Below this = no air
const int MAX_SOUND_LEVEL = 200; // Sound level that maxes out fan
const int MIN_FAN_PWM = 80; // Minimum PWM to overcome 3.7V motor stall

void setup() {
  Serial.begin(9600);
  pinMode(fanPin, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  lcd.init();
  lcd.backlight();
  
  // Startup Screen
  lcd.setCursor(0, 0);
  lcd.print("HUFF-N-PUFF");
  lcd.setCursor(0, 1);
  lcd.print("Earn Your Air");
  delay(2000);
  lcd.clear();
}

void loop() {
  unsigned long startMillis = millis();
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // 50ms sampling window for sound amplitude
  while (millis() - startMillis < 50) {
    int sample = analogRead(micPin);
    if (sample < 1024) {
      if (sample > signalMax) signalMax = sample;
      if (sample < signalMin) signalMin = sample;
    }
  }

  int peakToPeak = signalMax - signalMin;
  int fanPwm = 0;
  int fanPercent = 0;

  if (peakToPeak > SILENCE_THRESHOLD) {
    // Map sound to PWM range
    fanPwm = map(peakToPeak, SILENCE_THRESHOLD, MAX_SOUND_LEVEL, MIN_FAN_PWM, 255);
    fanPwm = constrain(fanPwm, MIN_FAN_PWM, 255);
    fanPercent = map(fanPwm, 0, 255, 0, 100);

    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
  } else {
    fanPwm = 0;
    fanPercent = 0;
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
  }

  analogWrite(fanPin, fanPwm);

  // Update LCD
  lcd.setCursor(0, 0);
  lcd.print("Noise: ");
  lcd.print(peakToPeak);
  lcd.print(" "); // Clear trailing chars

  lcd.setCursor(0, 1);
  if (peakToPeak > SILENCE_THRESHOLD) {
    lcd.print("Fan: ");
    lcd.print(fanPercent);
    lcd.print("% ");
  } else {
    lcd.print("NO AIR FOR YOU ");
  }

  // Serial Monitor Output
  Serial.print("Amplitude: "); Serial.print(peakToPeak);
  Serial.print("\tPWM: "); Serial.print(fanPwm);
  Serial.print("\tFan %: "); Serial.println(fanPercent);
}