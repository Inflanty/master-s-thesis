# Master's Thesis

## "Bezprzewodowy system sterowania z wykorzystaniem systemu czasu rzeczywistego FreeRTOS" 

Master's thesis to obtain the degree Master of Science.
The project is composed with a three parts:
* ANALYSIS
* AQUISITION and CONTROL
* PROCESS
![](doc/img/martersthesis.png)

## Main Board
### HW
![](doc/img/nrf32dk.png)

Main Booard is provided by nRF52832 (Nordic Semiconductor). The board is responsible for motor control, comunication with BLE server and advertising received value. Main Board will be equipped with ordinary user interface - buttons and LEDs.

### SW
Main Board SW Stack  
![](doc/img/layers.png)
On main board instalated FreeRTOS stack, all tasks are controlled by scheluder. Only small amount of interrupts are permitted - for control clarity. As we can see from the picture - there is small buffer between Application and lower layers. Mentioned buffer is responsible for taking informations from all controller task and streaming those infos via serial interface to J-Link (the Information will be stored and presented on desktop by tracealyzer).

#### Percepio Tracealyzer
![](doc/img/tracealyzer.png)

## Sensor Board
![](doc/img/thingy.jpg)

## Bibliography

* "Bluetooth Essentials for Programmers" - Albert S. Huang, Larry Rudolph | Massachusetts Institute of Technology

* "Getting Started with Bluetooth Low Energy: Tools and Techniques for Low-Power Networking" - Robert Davidson, Kevin Townsend, Chris Wang, Carles Cufí | ISBN 978-0-521-70375-8

* "Sensory i Systemy Pomiarowe" - Robert Czabanowski | ISBN 978-83-7493-559-3

* "Bluetooth Core Specification" - Bluetooth SIG Proprietary

* "Bluetooth 5.0 Specification" - Bluetooth SIG Proprietary
