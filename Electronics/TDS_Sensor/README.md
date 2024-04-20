# TDS

## Theory

TDS (Total Dissolved Solids) indicates how many milligrams of soluble solids are dissolved in one liter of water. 
In general, the higher the TDS value, the more soluble solids are dissolved in water, and the less clean the water is. 
Therefore, the TDS value can be used as one reference point for reflecting the cleanliness of water.
It measures the electrical conductivity of the water. When solids are dissolved in water, it dissociates into positive and negative ions.
Upon dipping the TDS sensor, the ions conduct electricity from the cathode to the anode thus completing the circuit and having some conductance. At distilled water since there is not dissolved solids, the TDS meter should output zero.

## Circuit

![image](https://github.com/MaxWadrin/Water_Quality_Prediction_System_using_IOT_and_AI/assets/61119096/c462b873-c375-42f5-a352-7e9cf57d434b)

The analog output of the TDS is connected to the ADC pin of the MCU.

## Procedure

- Record the temperature reading from the [Temperature_Sensor] and record the ambient temperature.
- Make the necessary connections.
- Burn the [TDS_Code] using arduino IDE. Include the ambient temperature for compensation.
- Measure the TDS of water.
