# 4-DOF MG90 Robotic Arm - Beginner's Guide

Welcome! If you are assembling your first robotic arm, you are in exactly the right place. This repository contains the code and instructions to get your 4-axis robot arm up and moving. 

This guide will walk you through wiring the electronics, setting up your software, and understanding how the code controls the physical movements of the arm. 

## What You Will Need
* **1x Microcontroller:** Arduino Uno, Nano, or Mega.
* **4x Standard MG90 Servos:** For the Base, Shoulder, Elbow, and Gripper. These are positional servos that move between 0 and 180 degrees.
* **Jumper Wires & Breadboard:** For making connections.
* **External 5V Power Supply (Highly Recommended):** 4 servos drawing power at the same time can pull more current than the Arduino can safely supply. Using a separate 5V battery pack or power module for the servos is the best way to prevent your Arduino from resetting or overheating!

---

## Section 1: Wiring Setup

Servos typically have three wires. Their colors might vary slightly depending on the manufacturer, but they generally follow this rule:
* **Red Wire:** Power (VCC / 5V)
* **Brown or Black Wire:** Ground (GND)
* **Yellow or Orange Wire:** Signal / Data

### Connecting to the Arduino
Here is exactly where you need to plug in the **Signal (Yellow/Orange)** wires based on our code:

| Arm Component | Servo Type | Arduino Digital Pin |
| :--- | :--- | :--- |
| **Shoulder (First Arm)** | Standard (180 deg) | **Pin 2** |
| **Base** | Standard (180 deg) | **Pin 3** |
| **Elbow (Second Arm)** | Standard (180 deg) | **Pin 4** |
| **Gripper (Claw)** | Standard (180 deg) | **Pin 5** |

### Powering the Servos
1. Connect all the **Brown/Black** servo wires to the **GND** row on your breadboard.
2. Connect all the **Red** servo wires to the **5V / Power** row on your breadboard.
3. **Important:** Connect the GND of your external power supply to the GND of the Arduino. They must share a common ground to communicate properly!

---

## Section 2: Library Installation

To make the Arduino talk to the servos, we use a "Library." Think of a library as a dictionary that translates our commands into electrical pulses the servos understand.

For this project, we use the standard `Servo.h` library. 
**The best part? It comes pre-installed with the Arduino IDE!** You don't need to download anything extra. As long as you have `#include <Servo.h>` at the very top of your code, the Arduino software knows exactly what to do. 

---

## Section 3: Code Breakdown

If you look at the `.ino` file, you might see a lot of text, but the logic is broken down into simple, easy-to-understand chunks. Here is how the code works:

### 1. The Setup (`void setup()`)
This is the initialization phase. When you turn the Arduino on, it runs this code exactly once.
* It tells the Arduino which pins are connected to which servos.
* It commands the entire arm to move to a safe, default "starting posture" (e.g., base centered at 90 degrees) so it doesn't flail around unpredictably.
* It pauses for 1 second (`delay(1000);`) to let the physical motors settle.

### 2. Smooth Movement (`moveServoSmoothly` function)
Normally, if you tell a servo to go from 0 to 90 degrees, it snaps there instantly. This sudden jerking can break your 3D-printed/acrylic parts or cause the robot to tip over. 
To fix this, we created a custom smooth movement function:
* Instead of jumping straight to the end position, it takes tiny 1-degree steps.
* It pauses for 15 milliseconds (`delay(15)`) between each step.
* This creates a smooth, sweeping, robotic motion for all joints, including the base.

### 3. Gripper Controls (`openGripper` & `closeGripper`)
These are simple shortcut functions. Instead of remembering the exact angles every time, we just write `closeGripper();` to clamp down (0 degrees) or `openGripper();` to let go (90 degrees).

### 4. The Main Routine (`pickAndPlaceTask()`)
This is the choreography! It combines all the basic movements into a single, automated task. 
Here is the step-by-step logic of what the arm does:
1. Opens the claw.
2. Lowers the shoulder toward the target object.
3. Closes the claw to grab the object.
4. Lifts the shoulder back up.
5. **Rotates the base:** Smoothly sweeps the base servo from its center position (90 degrees) to a new angle (45 degrees) to face the drop-off point.
6. Extends the elbow outward.
7. Lowers the shoulder to align the object directly over the slide.
8. Opens the claw to drop the object.
9. Retracts the elbow and shoulder, then smoothly rotates the base back to the center 90-degree starting position.
10. Pauses for a very long time so the loop doesn't immediately repeat.

---

## Section 4: Uploading and Running

1. Connect your Arduino to your computer via USB.
2. Open the `.ino` file in the Arduino IDE.
3. Go to **Tools > Board** and select your Arduino (e.g., Arduino Uno).
4. Go to **Tools > Port** and select the port your Arduino is connected to.
5. Click the **Upload** button (the right-pointing arrow at the top left).
6. Turn on your external power supply for the servos.
7. Watch your robot come to life!

### Quick Troubleshooting
* **The arm is twitching or the Arduino resets:** You need more power! Standard USB power is not enough for 4 servos under load. Switch to a dedicated 5V power supply.
* **A joint is moving backward:** Double-check your servo attachments to the physical plastic joints. You may need to unscrew the servo horn, rotate it, and screw it back in, or swap the start and end values in your `moveServoSmoothly` commands.
