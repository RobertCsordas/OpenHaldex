#include <Arduino.h>

const int enPin = 13;
const int dirPin = 12;
const int stepPin = 11;
const int adcPin = A0;
const int releasePin = 10;

const int N_STEPS = 19 * 4;

int currPos = 0;
int dir = 0;

void resetPos(){
  digitalWrite(enPin, HIGH);
  currPos = 0;
  delay(50);
  digitalWrite(enPin, LOW);
}

void setDir(int newDir){
  if (newDir == 1){
    digitalWrite(dirPin, LOW);
  } else {
    digitalWrite(dirPin, HIGH);
  }

  dir = newDir;
}

bool checkRelease(){
  if (digitalRead(releasePin) == LOW){
    resetPos();
    while (digitalRead(releasePin) == LOW){
      delay(1);
    }
    return true;
  } else {
    return false;
  }
}

void step(){
  const int nextPos = currPos + dir;
  if (nextPos < 0 || nextPos >= N_STEPS){
    return;
  }

  digitalWrite(stepPin, HIGH);
  delay(4);
  digitalWrite(stepPin, LOW);
  delay(4);

  currPos = nextPos;
}

void setup() {
  Serial.begin(115200);

  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, HIGH);

  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(releasePin, INPUT_PULLUP);

  digitalWrite(dirPin, LOW);
  digitalWrite(stepPin, LOW);

  resetPos();
}

void loop() {
  while (true){
    const int target = (long)analogRead(adcPin) * N_STEPS / 1024;

    if (checkRelease()){
      continue;
    }

    if (abs(target - currPos) <= 1){
      continue;
    }

    if (target == 0){
      resetPos();
      continue;
    }

    if (target > currPos){
      setDir(1);
    } else {
      setDir(-1);
    }

    for (int i=0; (i<10) && (currPos != target); (++i)){
      if (checkRelease()){
        break;
      }
      step();
    }
  }
}
