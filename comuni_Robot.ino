#include <AccelStepper.h>

#define LEFT_LIMIT_SWITCH1 22
#define RIGHT_LIMIT_SWITCH1 24

#define LEFT_LIMIT_SWITCH2 34
#define RIGHT_LIMIT_SWITCH2 36

AccelStepper stepper1(1, 2, 5);
AccelStepper stepper2(1, 3, 6);

bool movingToLeft1 = true;
bool movingToLeft2 = true;

void setup() {
  pinMode(LEFT_LIMIT_SWITCH1, INPUT_PULLUP);
  pinMode(RIGHT_LIMIT_SWITCH1, INPUT_PULLUP);
  pinMode(LEFT_LIMIT_SWITCH2, INPUT_PULLUP);
  pinMode(RIGHT_LIMIT_SWITCH2, INPUT_PULLUP);

  Serial.begin(115200);
 
  stepper1.setMaxSpeed(1000);
  stepper1.setAcceleration(500);

  stepper2.setMaxSpeed(1000);
  stepper2.setAcceleration(500);

  Serial.println("Setup all stepper!");
}

void loop() {
  String command = Serial.readStringUntil('\n');

  if (command == "FirstCome") {
    Serial.println("Stepper1 started!");

    while(true) {
      if (movingToLeft1) {
        stepper1.setSpeed(100);
        stepper1.runSpeed();

        if (digitalRead(LEFT_LIMIT_SWITCH1) == HIGH) {
          stepper1.setSpeed(0);
          stepper1.runSpeed();
          Serial.println("FirstComeC");

          Serial.println("Waiting for the Reverse command...");
          while (true) {
            if (Serial.available() > 0 && Serial.readStringUntil('\n') == "stop1") {
              Serial.println("Stepper1 stopped.");
              return;
            }
            
            if (Serial.available() > 0) {
              if (Serial.readStringUntil('\n') == "FirstGo") {
                Serial.println("Received Reverse command.");
                movingToLeft1 = false;
                break;
              }
            }
          } 
        }
      } else {
        stepper1.setSpeed(-100);
        stepper1.runSpeed();

        if (digitalRead(RIGHT_LIMIT_SWITCH1) == HIGH) {
          stepper1.setSpeed(0);
          stepper1.runSpeed();
          Serial.println("FirstGoC");

          Serial.println("Waiting for the Reverse command...");

          while (true) {
            if (Serial.available() > 0 && Serial.readStringUntil('\n') == "stop1") {
              Serial.println("Stepper1 stopped.");
              return;
            }
            
            if (Serial.available() > 0) {
              if (Serial.readStringUntil('\n') == "FirstCome") {
                Serial.println("Received Reverse command.");
                movingToLeft1 = true;
                break;
              }
            }
          } 
        }
      }    
      if (Serial.available() > 0 && Serial.readStringUntil('\n') == "exit1") {
         Serial.println("Stepper1 exit.");
         return;
      } 
    }
  }
  
  if (command == "SecondCome") {
    Serial.println("Stepper2 started!");
  
    while (true) {
      // 스테퍼2가 왼쪽으로 이동 중일 때
      if (movingToLeft2) {
        stepper2.setSpeed(100);
        stepper2.runSpeed();
  
        // 왼쪽 리미트 스위치를 확인
        if (digitalRead(LEFT_LIMIT_SWITCH2) == HIGH) {
          stepper2.setSpeed(0);
          stepper2.runSpeed();
          Serial.println("Complete");
  
          Serial.println("Waiting for the R2 command...");
          while (true) {
            // "stop2" 명령을 받으면 스테퍼2를 멈추고 함수를 종료
            if (Serial.available() > 0 && Serial.readStringUntil('\n') == "stop2") {
              Serial.println("Stepper2 stopped.");
              return;
            }
            // "R2" 신호를 기다림
            if (Serial.available() > 0) {
              if (Serial.readStringUntil('\n') == "SecondGo") {
                Serial.println("Received R2 command.");
                movingToLeft2 = false;
                break;
              }
            }
          }
        }
      } else { // 스테퍼2가 오른쪽으로 이동 중일 때
        stepper2.setSpeed(-100);
        stepper2.runSpeed();
  
        // 오른쪽 리미트 스위치를 확인
        if (digitalRead(RIGHT_LIMIT_SWITCH2) == HIGH) {
          stepper2.setSpeed(0);
          stepper2.runSpeed();
          Serial.println("SecondGoC");

          Serial.println("Waiting for the R2 command...");
          while (true) {
            // "stop2" 명령을 받으면 스테퍼2를 멈추고 함수를 종료
            if (Serial.available() > 0 && Serial.readStringUntil('\n') == "stop2") {
              Serial.println("Stepper2 stopped.");
              return;
            }
            // "R2" 신호를 기다림
            if (Serial.available() > 0) {
              if (Serial.readStringUntil('\n') == "SecondCome") {
                Serial.println("Received Reverse command.");
                movingToLeft2 = true;
                Serial.println("SecondCome");
                break;
              }
            }
          }
        }
      }
      if (Serial.available() > 0 && Serial.readStringUntil('\n') == "exit2") {
         Serial.println("Stepper2 stopped.");
         return;
      }
    }
  }
}
