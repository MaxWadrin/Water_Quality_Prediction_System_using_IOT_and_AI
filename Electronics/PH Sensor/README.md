# PH Sensor 

![image](https://github.com/MaxWadrin/Water_Quality_Prediction_System_using_IOT_and_AI/assets/61119096/5859d1da-d609-455d-8970-9753ee243a47)

https://robu.in/product/analog-ph-sensor-kit/?gad_source=1&gclid=CjwKCAjwz42xBhB9EiwA48pT78LejV66Ygd9VnVqsLG8AcrK48_14jYucqlse65glDpCayCzuBN_9hoCQIMQAvD_BwE

## Theory 

### PH Electrode

A glass electrode pH sensor functions based on the principle of ion-selective glass membrane potential. Comprising a specialized glass membrane and a reference electrode, the sensor operates by exploiting the selective permeability of the glass membrane to hydrogen ions (H⁺) present in the solution being measured. As hydrogen ions interact with the glass surface, an ion exchange occurs, leading to the generation of a potential difference across the membrane. This potential difference is proportional to the pH of the solution, with higher concentrations of hydrogen ions resulting in higher potentials, indicative of lower pH values (more acidic solutions), and vice versa. This electrical potential is measured by a sensitive electronic circuit in comparison to a stable reference voltage provided by the reference electrode. Calibration of the sensor is essential to relate the measured potential difference to the pH of the solution accurately. 

### Circuit

![image](https://github.com/MaxWadrin/Water_Quality_Prediction_System_using_IOT_and_AI/assets/61119096/4010c5e4-ce45-4996-b648-3d449f58de68)

The analog out is connected to the ADC pin of Arduino / ESP32 / RasberiPI / STM32 based on the microcontroller you are using.

### Calbiration Code

The amplifier module runs on a 5V supply. The process of converting voltage readings from a pH probe into pH values involves calibration and amplification techniques. pH values are linearly related to voltage, often represented by 

y=mx+b, where 

y is the pH value, 
x is the voltage, 
m is the slope of the line (typically determined through calibration, such as with buffer solutions at known pH values), and 
b is the y-intercept. 

Calibration involves using buffer solutions at specific pH values, such as pH 4 and pH 9, to establish the slope of the linear equation. In the process of converting voltage readings from a pH probe into pH values, calibration and amplification techniques play crucial roles. Ideally, a properly calibrated pH probe outputs 0 millivolts when the pH of the solution being measured is precisely 7. However, variations in the probe's zero point may cause this value to shift slightly, typically by around 7 pH units plus or minus some value, depending on the specific probe and its calibration. This can be found in the datasheet of the probe. Which indicates that 0PH means a negative voltage. Thus a amplifier OpAmp raises the voltage to the mid point of the ADC, say if 2.5 volts for Arduino operating at 5V and 1.75 volts for ESP32 operating at 3.3 Volts. The middle point factor can cange based on the maximum operating point of the ADC pin if you use a multimeter. Thus anything below mid point volt to 0 volt is acidic and anything above mid point volt to maximum operating volt is alkaline. 

Some amplifier module comes with a potentiometer. Here before connecting the probe you can short the positive and negative of the probe input. This gives a 0 Volt input to the amplifier. Then you can adjust the potentiometer to check if the amplifier putput at 0 volts is right at the mid point voltage of the MCU.

Once the amplifier is calibrated, its time to calibrate the probe. Make a buffer solution of PH 14. How to make the solution is out of the scope of this project. Record the maximum amplified voltage output by the sensor and put it in the code. Remember the maximum recorded voltage might have some error depending on the temperature and electrode. Refer the data sheet for calibration. The code finds a linear relationship where we have a 0 PH at 0 Volts and 14 Ph at the recorded voltage. 

Thus it maps the output of the sensor with the proper pH value. 

# Procedure

- Burn the [ADC_High] code to put the desired ADC pin high. Take a multimeter in voltage reading mode and put the positive at the pin and negative at GND. Measure the voltage and record it as [MaxOperVolt]
- Burn the [ADC_Value] code and check the if the ADC is working.
- Keep the circuit live and connect the module.
- (Optional) if your amplifier module as potentiometer then connect the positive and negative of the probe input. Adjust the pot so that the output stabalizes to the mid point ADC.
- Connect the probe to the amplifier
- Create the buffer solution of pH14, dip the probe and record the voltage output from the amplifier module. you can use the ADC method or a simple multimeter for extra accuracy. Record the voltage as [MaxVoltatpH14]
- Burn the [pH_Code] to view the pH reading.
