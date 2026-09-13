<img width="1280" height="640" alt="git (1)" src="https://github.com/user-attachments/assets/8920b256-2ba8-4988-b824-5351134eb4bd" />



# HUFF-N-PUFF 🎯


## Basic Details
### Team Name: CopyPaste


### Team Members
- Team Lead: Irene Sara Philippose - School Of Engineering,CUSAT 
- Member 2: Ephrem Shajan - School Of Engineering 

### Project Description
An Arduino-powered voice-reactive DC fan controller that dynamically adjusts a cooling fan's RPM based on acoustic volume captured by a KY-038 microphone sensor, translating spoken words into real-time mechanical airflow using an NPN transistor driver.

### The Problem (that doesn't exist)
Manual fan switches require far too much finger exertion, and sitting in silent rooms while working is an unacceptably mundane experience that lacks continuous, speech-activated cooling feedback.

### The Solution (that nobody asked for)
By continuously monitoring the ambient room noise and speech volume through an analog microphone module, this system uses peak-to-peak amplitude calculations to ramp up a DC axial fan whenever you speak, shouting your way into a personalized, voice-driven breeze.

## Technical Details
### Technologies/Components Used
For Software:
- C++ (Arduino IDE)
- Arduino Core Libraries
- Analog Input Processing & PWM Signal    Mapping Algorithms
- Arduino Serial Monitor for Calibration

For Hardware:
- Arduino Nano or Uno (CH340 Clone) with USB Cable
- KY-038 Sound / Microphone Sensor Module (Analog Out)
- Mini 5V or 12V DC Cooling Fan (Axial)
- 2N2222 NPN Transistor
- 1N4007 Flyback Diode
- 1k Ohm Resistor (1/4 Watt)
- Breadboard (400 or 830 tie-points) & Jumper Wires Pack

### Implementation
For Hardware:

# Schematic & Circuit
<img width="1536" height="658" alt="CircuitDiagram" src="https://github.com/user-attachments/assets/3ae0b23e-cfe8-49c5-bb4a-c9b0d3f014b8" />

The KY-038 sound sensor sends analog sound levels to the Arduino Nano through A0. The Nano displays the readings on the I2C LCD via A4/A5 and controls the fan through a 2N2222A transistor using D9. The fan is powered separately by a 3.7V battery, while red and green LEDs connected to D7 and D6 indicate fan OFF and ON status respectively. All components share a common ground.

<img width="2528" height="1686" alt="Schematic_diagram" src="https://github.com/user-attachments/assets/5d15a3f5-0252-459f-80a0-fe1ea5e9153b" />

The schematic illustrates the complete electrical connections of the sound-controlled fan system. The KY-038 sensor provides analog sound input to the Arduino Nano, which processes the signal and displays the sound level on the I2C LCD. Based on the sound intensity, the Nano controls the fan through a 2N2222A transistor driver, while the red and green LEDs indicate the fan’s OFF and ON states. The fan is powered by a separate 3.7V battery, with a common ground shared between the battery and Arduino.

# Build Photos
![Components](Add photo of your components here)
Components Used
Arduino Nano
KY-038 sound sensor module
16×2 LCD with I2C module
12V DC brushless fan
3.7V battery/power source
2N2222A NPN transistor
Red LED
Green LED
220Ω resistors
Breadboard
Jumper wires
USB cable for Arduino power and programming

<img width="1280" height="610" alt="WhenFANisOFF" src="https://github.com/user-attachments/assets/275e944a-13b7-4f6a-b6c2-ee06ae1c978c" />
Build Steps
1.Prepare the components and Gather the Arduino Nano, KY-038 sound sensor, I2C LCD, 2N2222A transistor, fan, battery, LEDs, resistors, breadboard, and jumper wires.
2.Connect the Arduino Nano to the laptop through USB. The USB powers the Arduino, sensor, LCD, and LEDs.
3.Connect Arduino GND to the breadboard ground rail. Connect the sensor GND, LCD GND, transistor emitter, battery negative, and LED cathodes to this common ground.
4.Connect KY-038 VCC to 5V, GND to GND, and AO to Arduino A0. Leave DO disconnected.
5.Connect LCD VCC to 5V, GND to GND, SDA to A4, and SCL to A5.
6.Connect the fan’s positive wire to the 3.7V battery positive terminal. Connect the fan’s negative wire to the collector of the 2N2222A transistor. Connect the emitter to battery negative.
7.Connect Arduino D9 to the transistor base through a 220Ω resistor. Ensure the battery negative and Arduino GND are common.
8.Connect the green LED to D6 through a 220Ω resistor and the red LED to D7 through a 220Ω resistor. Connect their cathodes to GND.
9.Program the Arduino to read sound intensity, display it on the LCD, vary the fan speed using PWM, and control the LEDs according to sound detection.
10.Power the Arduino through USB and connect the 3.7V battery to the fan. When sound is detected, the green LED turns on and the fan runs. During quiet conditions, the red LED turns on and the fan stops.
11.Observe the sensor values in the Serial Monitor and adjust the sound threshold in the code for reliable operation.

<img width="1280" height="568" alt="WhenFANturnsOn" src="https://github.com/user-attachments/assets/929db2c8-286b-46d0-af6b-7f2b128c75f1" />

*Explain the final build*

### Project Demo
# Video
https://drive.google.com/file/d/1am_AOcJioeIADStrS_jLeS763Ll0K5Xj/view?usp=sharing
*Explain what the video demonstrates*



## Team Contributions
- IRENE: Schematics, Circuit and Integration
- EPHREM: Coding and Error handling


---
Made with ❤️ at TinkerHub Useless Projects 

![Static Badge](https://img.shields.io/badge/TinkerHub-24?color=%23000000&link=https%3A%2F%2Fwww.tinkerhub.org%2F)
![Static Badge](https://img.shields.io/badge/UselessProjects--26-26?link=https%3A%2F%2Ftinkerhub.org%2Fevents%2F1M8ORET9A1%2Fuseless-projects-3.0)



