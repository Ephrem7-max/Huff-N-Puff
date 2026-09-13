#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int micPin = A0;
const int fanPin = 9;
const int greenLed = 6;
const int redLed = 7;

const int SILENCE_THRESHOLD = 25;
const int MAX_SOUND_LEVEL = 200;
const int MIN_FAN_PWM = 80;

float smoothedAmplitude = 0;
int currentFanPwm = 0;

void setup() {
  Serial.begin(9600);
  pinMode(fanPin, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0); lcd.print("HUFF-N-PUFF");
  lcd.setCursor(0, 1); lcd.print("Earn Your Air");
  delay(2000);
  lcd.clear();
}

void loop() {
  unsigned long startMillis = millis();
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  while (millis() - startMillis < 50) {
    int sample = analogRead(micPin);
    if (sample < 1024) {
      if (sample > signalMax) signalMax = sample;
      if (sample < signalMin) signalMin = sample;
    }
  }

  int peakToPeak = signalMax - signalMin;

  // Exponential moving average smoothing to prevent erratic jumps
  smoothedAmplitude = (0.7 * smoothedAmplitude) + (0.3 * peakToPeak);

  int targetPwm = 0;
  if (smoothedAmplitude > SILENCE_THRESHOLD) {
    targetPwm = map((int)smoothedAmplitude, SILENCE_THRESHOLD, MAX_SOUND_LEVEL, MIN_FAN_PWM, 255);
    targetPwm = constrain(targetPwm, MIN_FAN_PWM, 255);
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
  } else {
    targetPwm = 0;
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
  }

  // Gradual acceleration/deceleration interpolation (easing)
  currentFanPwm = currentFanPwm + (int)((targetPwm - currentFanPwm) * 0.2);
  analogWrite(fanPin, currentFanPwm);

  int fanPercent = map(currentFanPwm, 0, 255, 0, 100);

  // Update LCD
  lcd.setCursor(0, 0);
  lcd.print("Air Blow: "); lcd.print((int)smoothedAmplitude); lcd.print(" ");
  lcd.setCursor(0, 1);
  if (smoothedAmplitude > SILENCE_THRESHOLD) {
    lcd.print("Fan: "); lcd.print(fanPercent); lcd.print("% ");
  } else {
    lcd.print("NO AIR FOR YOU ");
  }

  Serial.print("Smooth Amp: "); Serial.print(smoothedAmplitude);
  Serial.print("\tTarget PWM: "); Serial.print(targetPwm);
  Serial.print("\tActual PWM: "); Serial.println(currentFanPwm);
}
