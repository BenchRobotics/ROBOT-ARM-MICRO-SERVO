#include <Servo.h>

// Declare the servo objects for each physical component of the robotic arm
Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo gripperServo;

// Default starting angles for all standard 180-degree servos
int defaultBasePos = 90;
int defaultShoulderPos = 90;
int defaultElbowPos = 0;
int defaultGripperPos = 20;

// Variables to keep track of the current angles of the servos
int currentBasePos = 90;
int currentShoulderPos = 90;
int currentElbowPos = 0;
int currentGripperPos = 20;

void setup() {
  // Connect the servos to their respective digital pins on the Arduino board
  baseServo.attach(3);
  shoulderServo.attach(2);
  elbowServo.attach(4);
  gripperServo.attach(5);

  // Command the arm to move into its default starting posture
  baseServo.write(defaultBasePos);
  shoulderServo.write(defaultShoulderPos);
  elbowServo.write(defaultElbowPos);
  gripperServo.write(defaultGripperPos);

  // Wait 1 second to give the physical motors time to reach their starting positions
  delay(1000);
}

// Function to smoothly move a servo from its current angle to a new target angle
void moveServoSmoothly(Servo& targetServo, int startPos, int endPos) {
  if (startPos < endPos) {
    // If moving forward, increase the angle step-by-step
    for (int pos = startPos; pos <= endPos; pos++) {
      targetServo.write(pos);
      delay(15); // Wait 15 milliseconds between each degree to slow down the movement
    }
  } else {
    // If moving backward, decrease the angle step-by-step
    for (int pos = startPos; pos >= endPos; pos--) {
      targetServo.write(pos);
      delay(15);
    }
  }
}

// Shortcut function to close the gripper claw
void closeGripper() {
  gripperServo.write(0);
}

// Shortcut function to open the gripper claw
void openGripper() {
  gripperServo.write(90);
}

// Main sequence: The robot picks up an object and places it on a slide
void pickAndPlaceTask() {

  openGripper();

  // Lower the shoulder down towards the object
  moveServoSmoothly(shoulderServo, currentShoulderPos, 145);
  currentShoulderPos = 145;

  delay(500);

  closeGripper();

  delay(500);

  // Lift the object by raising the shoulder back up
  moveServoSmoothly(shoulderServo, currentShoulderPos, defaultShoulderPos);
  currentShoulderPos = defaultShoulderPos;

  delay(500);

  // Rotate the standard base servo smoothly to a new fixed angle (e.g., 45 degrees)
  moveServoSmoothly(baseServo, currentBasePos, 45);
  currentBasePos = 45;

  delay(1000);

  // Extend the elbow out towards the slide
  moveServoSmoothly(elbowServo, currentElbowPos, 50);
  currentElbowPos = 50;

  delay(1000);

  // Lower the shoulder to align the object directly over the slide
  moveServoSmoothly(shoulderServo, currentShoulderPos, 130);
  currentShoulderPos = 130;

  delay(1000);

  openGripper();

  delay(200);

  // Retract the elbow up and out of the way
  moveServoSmoothly(elbowServo, currentElbowPos, 90);
  currentElbowPos = 90;

  // Return the shoulder to its original starting position
  moveServoSmoothly(shoulderServo, currentShoulderPos, defaultShoulderPos);
  currentShoulderPos = defaultShoulderPos;

  // Return the base back to its center starting position
  moveServoSmoothly(baseServo, currentBasePos, defaultBasePos);
  currentBasePos = defaultBasePos;

  // Extremely long delay to freeze the program and prevent the loop from repeating
  delay(1000000000);
}

void loop() {
  // Execute the main sequence
  pickAndPlaceTask();
}