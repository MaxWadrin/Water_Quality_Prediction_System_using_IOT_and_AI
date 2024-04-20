# Turbidity Sensor

## Theory

The turbidity sensor detects water quality by measuring the levels of turbidity, or the opaqueness. Unlike TDS sensor it uses light to detect suspended particles in water by measuring the light transmittance and scattering rate, which changes with the amount of total suspended solids (TSS) in water. As the TSS increases, the liquid turbidity level increases. Turbidity sensors are used to measure water quality in rivers and streams, wastewater and effluent measurements, control instrumentation for settling ponds, sediment transport research and laboratory measurements. The senror involved a light transmitter and a reciever. In clear water all light is passed through the sensor, thus the voltage output is maximum and turbididty is minimum. As cloudyness increases the recieved voltage drops as light keeps on scattering. The unit measuring turbidity is NTU, also it is known as JTU (Jackson Turbidity Unit), 1JTU = 1NTU = 1 mg/L

## Circuit 

![image](https://github.com/MaxWadrin/Water_Quality_Prediction_System_using_IOT_and_AI/assets/61119096/db9662aa-2ab0-42b0-b885-f88fb283e8f8)

## Calibration

We have to map the turbidity values depending on the calibration curve provided in the datasheet.

![image](https://github.com/MaxWadrin/Water_Quality_Prediction_System_using_IOT_and_AI/assets/61119096/15c45051-9e7f-4445-b625-79555f236890)

Here 0% means 0 Volts in ADC and 100% means maximum volts in ADC. 

![image](https://github.com/MaxWadrin/Water_Quality_Prediction_System_using_IOT_and_AI/assets/61119096/5f29ab8d-9c55-47cb-95b0-4aab7a30ed54)

Even based on temperature the turbidity varies. We create two piece wise linear function

- Voltage to NTU piece wise linear function
- Temperature compensation linear function

## Procedure

- Record the temperature reading from the [Temperature_Sensor] and record the ambient temperature.
- Make the necessary connections.
- Burn the [Turbidity_Code] using arduino IDE. Include the ambient temperature for compensation.
- Measure the Turbidity of water.
