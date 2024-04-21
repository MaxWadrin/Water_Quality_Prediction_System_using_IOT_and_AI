# Temperature Sensor

https://robu.in/product/max6675-module-k-type-thermocouple-sensor-measure-1024-degrees-temperature/

## Theory

There are various ways of measuring temperature. I am using a K-Type thermocouple which measures temperature upto range -2 C to 800 C with a error of 1.5 C. MAX6675 is the IC that comes with a 12 BIT ADC by default. So we dont need any ADC calculation in the MCU. The data sheet of MAX6675 provides all details regarding the calbration. It works on the basis of Seebeck effect where a junction having a cold side and a hot side. This temperature difference forces the electron to move and thus a current is flown and thus we have a voltage of around 40uV per celcius change. The sensor is the hot junction side and the board on which the MAX6675 IC is mounted is the cold junction side. 

![image](https://github.com/MaxWadrin/Water_Quality_Prediction_System_using_IOT_and_AI/assets/61119096/b9c91f9c-a699-4a5a-93ce-0d5d44608a9a)


## Circuit

![image](https://github.com/MaxWadrin/Water_Quality_Prediction_System_using_IOT_and_AI/assets/61119096/553741c5-4a0f-4ea1-a8c2-f2f18d1258a2)

## Procedure

- Connect the probe using the screw terminal.
- Connect SO CS and SCK at 3 GPIO pins of the MCU
- - Install MAX6675 library in Arduino IDE before burnign the code
- Burn the Temp_Code
- Read the temperature on serial monitor

