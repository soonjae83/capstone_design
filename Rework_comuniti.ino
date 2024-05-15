#include <AccelStepper.h>

#define LEFT_LIMIT_SWITCH_1 22
#define RIGHT_LIMIT_SWITCH_1 24
#define LEFT_LIMIT_SWITCH_2 34
#define RIGHT_LIMIT_SWITCH_2 36

AccelStepper stepper1(1, 2, 5);
AccelStepper stepper2(1, 3, 6);

enum MotorState { IDLE, MOVING_LEFT, MOVING_RIGHT };
MotorState state1 = IDLE, state2 = IDLE;

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
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    handleCommand(command);
  }

  processMotor(stepper1, state1, RIGHT_LIMIT_SWITCH_1, LEFT_LIMIT_SWITCH_1, "First");
  processMotor(stepper2, state2, LEFT_LIMIT_SWITCH_2, RIGHT_LIMIT_SWITCH_2, "Second");
}

void handleCommand(String command) {
  if (command == "FirstCome") state1 = MOVING_LEFT;
  else if (command == "FirstGo") state1 = MOVING_RIGHT;
  else if (command == "SecondCome") state2 = MOVING_RIGHT;
  else if (command == "SecondGo") state2 = MOVING_LEFT;
}

void processMotor(AccelStepper& stepper, MotorState& state, int leftLimitSwitch, int rightLimitSwitch, String motorLabel) {
  if (state == MOVING_LEFT) {
    stepper.setSpeed(100);
    stepper.runSpeed();
    if (digitalRead(leftLimitSwitch) == HIGH) {
      stepper.setSpeed(0);
      stepper.runSpeed();
      state = IDLE;
      Serial.println(motorLabel + "ComeC");  // Specific completion message
    }
  } else if (state == MOVING_RIGHT) {
    stepper.setSpeed(-100);
    stepper.runSpeed();
    if (digitalRead(rightLimitSwitch) == HIGH) {
      stepper.setSpeed(0);
      stepper.runSpeed();
      state = IDLE;
      Serial.println(motorLabel + "GoC");  // Specific completion message
    }
  }
}
