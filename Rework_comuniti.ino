#include <AccelStepper.h>

#define LEFT_LIMIT_SWITCH_1 22
#define RIGHT_LIMIT_SWITCH_1 24

#define LEFT_LIMIT_SWITCH_2 34
#define RIGHT_LIMIT_SWITCH_2 36

AccelStepper stepper1(1, 2, 5);
AccelStepper stepper2(1, 3, 6);

bool movingToLeft1 = true;
bool movingToLeft2 = true;

void setup() {
  pinMode(LEFT_LIMIT_SWITCH_1, INPUT_PULLUP);
  pinMode(RIGHT_LIMIT_SWITCH_1, INPUT_PULLUP);
  pinMode(LEFT_LIMIT_SWITCH_2, INPUT_PULLUP);
  pinMode(RIGHT_LIMIT_SWITCH_2, INPUT_PULLUP);
  
  Serial.begin(115200);

  stepper1.setMaxSpeed(200);
  stepper1.setAcceleration(200);
  stepper2.setMaxSpeed(200);
  stepper2.setAcceleration(200);

}

void loop() {
  // 사용자로부터 명령어를 입력받음
  String command = Serial.readStringUntil('\n');
  
  // 스텝모터 1 시작
  if (command == "FirstCome") {
    while (true) {
      // 왼쪽으로 이동
      if (movingToLeft1) {
        stepper1.setSpeed(100);
        stepper1.runSpeed();
        
        // 왼쪽 리밋스위치에 닿으면 멈춤
        if (digitalRead(RIGHT_LIMIT_SWITCH_1) == HIGH) {
          stepper1.setSpeed(0);
          stepper1.runSpeed();
          Serial.println("FirstComeC");
          
          while (true) {
            if (Serial.available() > 0) {
              String newCommand = Serial.readStringUntil('\n');
              if (newCommand == "FirstGo") {
                movingToLeft1 = false; // 이동 방향 변경
                break;
              }
              else if (newCommand == "FirstCome") {
                movingToLeft1 = true; // 이동 방향 유지
                break;
              }
            }
          }
        }
      } 
      // 오른쪽으로 이동
      else {
        stepper1.setSpeed(-100);
        stepper1.runSpeed();
        
        // 오른쪽 리밋스위치에 닿으면 멈춤
        if (digitalRead(LEFT_LIMIT_SWITCH_1) == HIGH) {
          stepper1.setSpeed(0);
          stepper1.runSpeed();
          Serial.println("FirstGoC");
          
          while (true) {
            if (Serial.available() > 0) {
              String newCommand = Serial.readStringUntil('\n');
              if (newCommand == "FirstCome") {
                movingToLeft1 = true; // 이동 방향 변경
                break;
              }
              else if (newCommand == "FirstGo") {
                movingToLeft1 = false; // 이동 방향 유지
                break;
              }
            }
          }
        }
      }
      
      // stop 명령어를 받으면 로봇을 멈춤
      if (Serial.available() > 0) {
        String stopCommand = Serial.readStringUntil('\n');
        if (stopCommand == "Ostop") {
          break; // loop() 함수 종료
        }
      }
    }
  }
  // 스텝모터 2 시작
  if (command == "SecondCome") {
    while (true) {
      // 왼쪽으로 이동
      if (movingToLeft2) {
        stepper2.setSpeed(100);
        stepper2.runSpeed();
        
        // 왼쪽 리밋스위치에 닿으면 멈춤
        if (digitalRead(LEFT_LIMIT_SWITCH_2) == HIGH) {
          stepper2.setSpeed(0);
          stepper2.runSpeed();
          Serial.println("SecondComeC");
          
          while (true) {
            if (Serial.available() > 0) {
              String newCommand = Serial.readStringUntil('\n');
              if (newCommand == "SecondGo") {
                movingToLeft2 = false; // 이동 방향 변경
                break;
              }
              else if (newCommand == "SecondCome") {
                movingToLeft2 = true; // 이동 방향 유지
                break;
              }
            }
          } break;
        }
      } 
      // 오른쪽으로 이동
      else {
        stepper2.setSpeed(-100);
        stepper2.runSpeed();
        
        // 오른쪽 리밋스위치에 닿으면 멈춤
        if (digitalRead(RIGHT_LIMIT_SWITCH_2) == HIGH) {
          stepper2.setSpeed(0);
          stepper2.runSpeed();
          Serial.println("SecondGoC");
          
          while (true) {
            if (Serial.available() > 0) {
              String newCommand = Serial.readStringUntil('\n');
              if (newCommand == "SecondCome") {
                movingToLeft2 = true; // 이동 방향 변경
                break;
              }
              else if (newCommand == "SecondGo") {
                movingToLeft2 = false; // 이동 방향 유지
                break;
              }
            }
          }
        }
      }
      
      // stop 명령어를 받으면 로봇을 멈춤
      if (Serial.available() > 0) {
        String stopCommand = Serial.readStringUntil('\n');
        if (stopCommand == "Sstop") {
          break; // loop() 함수 종료
        }
      } break;
    }
  }
}
