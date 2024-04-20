# Sensor Calibration and Amplification Guide
## Introduction
When interfacing analog sensors with microcontroller units (MCUs) such as Arduino, ESP32, Raspberry Pi, or STM32, it's essential to calibrate and amplify the sensor signals properly to ensure accurate readings. This README provides guidelines on calibrating and amplifying analog sensors for various MCUs.

## Operating Voltage of ADC Pins
Before calibration, it's crucial to determine the operating voltage of the analog-to-digital converter (ADC) input pins of the MCU. For example, Arduino operates at 5 volts, while ESP32 operates at 3.3 volts. To ensure accuracy, using a multimeter or digital storage oscilloscope (DSO) is recommended. For instance, in the case of an ESP32 Devkit V4, the ADC value may reach a maximum of 3.29 volts instead of 3.3 volts.

## ADC Resolution and Mapping
The ADC quantizes the sensor voltage levels into individual bits based on its resolution. For Arduino with a 10-bit ADC, the mapping is from 0 volts to 5 volts, corresponding to 0 to 1023 ADC values. Similarly, for ESP32 with a 12-bit ADC operating at 3.3 volts, the mapping is from 0 volts to 3.3 volts, corresponding to 0 to 4095 ADC values. Adjustments to the mapping may be necessary for accuracy, considering the actual operating voltage measured. For my case ADC vlaue of 4095 in ESP32 Devkit V4 is 3.29 volts.

![image](https://github.com/MaxWadrin/Water_Quality_Prediction_System_using_IOT_and_AI/assets/61119096/52108ac7-7a31-458d-9e11-d30f47a988f4)

Thats a signal mapped to 3 bit ADC


## Sensor Amplification
Directly connecting sensors to the ADC module may result in loss of information, especially for sensors with low output voltages. To mitigate this, sensors should be connected to low-noise amplifier modules to amplify the signal to a readable voltage range without introducing significant noise. Proper amplification ensures that the ADC can accurately assign bit values to minute changes in the signal, improving accuracy. Say a sensor outputs 0 to 3 milivolts. If we use a MCU with 12 Bit ADC operating at 3.3 Volts then each ADC value will correspond to 0.805 milivolts. The maximum output of the sensor will be around 4 ADC value. So from 4 ADC value to 4095 ADC value will remian un used. Moreover we would also loose the internal accuracy of the sensor. Sensors needs to be connected to low noise amplifier module to properly amplify the signal to readable voltage range without introducing much noise. Say 0 milivolts to 1 milivolts is properly amplified so that the output is 0 Volts to 3.3 Volts. Then the maximum output of the sensor will be at maximum value of the ADC. In other words we properly perform amplitude scaling on the signal so that the ADC can properly assign the bit values to very minute change in the signal. Increasing the ADC bit also imporves the accuracy.

## Stabilization Algorithm
For stable applications like water quality detection, stabilization algorithms can be employed. These algorithms average a certain number of ADC values (SCOUNT) before converting them into voltage readings. Modifying SCOUNT adjusts the sensitivity of the system. However, for highly sensitive applications like biomedical sensing, this algorithm is usually not used as it may reduce sensitivity. Adjustments to the stabilization algorithm can provide a smooth curve tailored to specific application requirements.

By following these guidelines and understanding the characteristics of your MCU and sensors, you can calibrate and amplify analog sensor signals effectively for your project needs.
