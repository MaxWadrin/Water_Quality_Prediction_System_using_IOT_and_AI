# PH Sensor 

![image](https://github.com/MaxWadrin/Water_Quality_Prediction_System_using_IOT_and_AI/assets/61119096/5859d1da-d609-455d-8970-9753ee243a47)

## PH Electrode

A glass electrode pH sensor functions based on the principle of ion-selective glass membrane potential. Comprising a specialized glass membrane and a reference electrode, the sensor operates by exploiting the selective permeability of the glass membrane to hydrogen ions (H⁺) present in the solution being measured. As hydrogen ions interact with the glass surface, an ion exchange occurs, leading to the generation of a potential difference across the membrane. This potential difference is proportional to the pH of the solution, with higher concentrations of hydrogen ions resulting in higher potentials, indicative of lower pH values (more acidic solutions), and vice versa. This electrical potential is measured by a sensitive electronic circuit in comparison to a stable reference voltage provided by the reference electrode. Calibration of the sensor is essential to relate the measured potential difference to the pH of the solution accurately. 

# Circuit

![image](https://github.com/MaxWadrin/Water_Quality_Prediction_System_using_IOT_and_AI/assets/61119096/4010c5e4-ce45-4996-b648-3d449f58de68)

The analog out is connected to the ADC pin of Arduino / ESP32 / RasberiPI / STM32 based on the microcontroller you are using.

## Calbiration

The amplifier module runs on a 5V supply. The process of converting voltage readings from a pH probe into pH values involves calibration and amplification techniques. pH values are linearly related to voltage, often represented by 

y=mx+b, where 

y is the pH value, 
x is the voltage, 
m is the slope of the line (typically determined through calibration, such as with buffer solutions at known pH values), and 
b is the y-intercept. 

Calibration involves using buffer solutions at specific pH values, such as pH 4 and pH 9, to establish the slope of the linear equation. In the process of converting voltage readings from a pH probe into pH values, calibration and amplification techniques play crucial roles. Ideally, a properly calibrated pH probe outputs 0 millivolts when the pH of the solution being measured is precisely 7. However, variations in the probe's zero point may cause this value to shift slightly, typically by around 7 pH units plus or minus some value, depending on the specific probe and its calibration. This can be found in the datasheet of the probe.

## Code

<#define SensorPin A0          // Define the pin to which the pH meter Analog output is connected

const int MaxOperVolt = 5;    // Maximum operating voltage of the Arduino (in volts)
const int MaxVoltatpH14 = 4;  // Maximum voltage output of the pH amplifier at pH 14 (in volts)
const int MaxADCout = 1024;   // Maximum output of the analog-to-digital converter (ADC)
const int avgCount = 6;       // Number of readings to average for smoothing
const int Decimal = 2;        // Decimal point of the ph output

float phPerVolt;              // Ratio of pH change per volt>
