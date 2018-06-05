# master-s-thesis
Master's thesis to obtain the degree Master of Science.
The project is composed with a three parts:
* ANALYSIS
* AQUISITION and CONTROL
* PROCESS
![](doc/img/mastersthesis.png)

## Main Board
### HW
![](doc/img/nrf32dk.png)

Main Booard is provided by nRF52832 (Nordic Semiconductor). The board is responsible for motor control, comunication with BLE server and advertising received value. Main Board will be equipped with ordinary user interface - buttons and LEDs.

### SW
Above Main Board SW Stack  
![](doc/img/layers.png)
On main board instalated FreeRTOS stack, all tasks are controlled by scheluder. Only small amount of interrupts are permitted - for control clarity. As we can see from the picture - there is small buffer between Application and lower layers. Mentioned buffer is responsible for taking informations from all controller task and streaming those infos via serial interface to J-Link (the Information will be stored and presented on desktop by tracealyzer).

#### Percepio Tracealyzer
![](doc/img/tracealyzer.png)

## Sensor Board
![](doc/img/thingy.jpg)
