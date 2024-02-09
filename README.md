# Posture detection using Machine Learning and Arduino

***
### Video
https://youtu.be/eCdCo_dnR4A

***

### Objective

The goal of this project is to design a posture detection system utilizing Arduino and Machine Learning techniques. The system aims to accurately identify and monitor different body postures in real-time.
***

### Scope and Deliverables
The project involves the creation of a comprehensive database by recording Inertial Measurement Unit (IMU) sensor data for specific postures such as lying on the back, lying on the side, and lying on the other side. This database serves as the training data for a Convolutional Neural Network (CNN) model. The trained model is then integrated into the Arduino Integrated Development Environment (IDE) using the Harvard TinyML library.
***

### Key Features

IMU Sensor Data Collection: Recording IMU sensor data for various body postures to build a robust database.
Machine Learning Model Training: Employing a CNN model to analyze and learn from the collected data, creating a posture detection model.
Arduino Integration: Implementing the trained model into the Arduino IDE, adapting the code from the Harvard TinyML IMU sensor example.
Real-time Posture Detection: Displaying the detected posture in real-time on the serial monitor of the Arduino.
Unknown Posture Handling: Providing a mechanism to identify and report when the system encounters an unknown posture.
***
### Technologies Used

Arduino Nano BLE
Convolutional Neural Network (CNN)
Machine Learning (TinyML)
***
### Benefits

Real-time posture monitoring for applications in health, fitness, or ergonomic studies.
Low-cost implementation using Arduino and IMU sensors.
Compact and portable design for versatile use.
***
### Target Audience

Individuals interested in health and fitness tracking.
Researchers and practitioners in ergonomic studies.
Enthusiasts in the field of TinyML and embedded systems.
***
### Constraints

Consideration of power consumption for prolonged use.
Optimization of the model for the limited resources of Arduino.
This project combines the power of machine learning with the versatility of Arduino to create a practical and affordable posture detection system with applications in various domains.
