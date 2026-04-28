#include <Servo.h>

Servo panServo;
Servo tiltServo;

const int launcherPin = 9;

void setup() {
  Serial.begin(115200);
  panServo.attach(5);
  tiltServo.attach(6);
  pinMode(launcherPin, OUTPUT);
}

float parseValue(String msg, String key) {
  int start = msg.indexOf(key + "=");
  if (start < 0) return 0;
  start += key.length() + 1;
  int end = msg.indexOf(';', start);
  if (end < 0) end = msg.length();
  return msg.substring(start, end).toFloat();
}

void loop() {
  if (!Serial.available()) return;

  String line = Serial.readStringUntil('\n');

  float pan = parseValue(line, "PAN");
  float tilt = parseValue(line, "TILT");
  int pwm = (int)parseValue(line, "PWM");
  int dwell = (int)parseValue(line, "DWELL");

  panServo.write(constrain((int)(90 + pan), 45, 135));
  tiltServo.write(constrain((int)(90 + tilt), 45, 135));
  analogWrite(launcherPin, constrain(pwm, 0, 255));

  delay(constrain(dwell, 50, 500));
  analogWrite(launcherPin, 0);
}
