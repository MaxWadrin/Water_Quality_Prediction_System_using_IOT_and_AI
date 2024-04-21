#include <max6675.h>

// Define the pins connected to the MAX6675 module
#define MAX6675_CLK 18
#define MAX6675_CS  5
#define MAX6675_SO  19

#define SensorPin 13          // Define the pin to which the pH meter Analog output is connected
#define TdsSensorPin 12       // Define the pin to which the TDS sensor Analog output is connected
#define PHSensorPin 15       // Define the pin to which the pH sensor Analog output is connected

const int MaxOperVolt = 5;    // Maximum operating voltage of the Arduino (in volts)
const int MaxADCout = 1024;   // Maximum output of the analog-to-digital converter (ADC)
const int avgCount = 6;       // Number of readings to average for smoothing
const int Decimal = 2;        // Decimal point of the output
const int MaxVoltatpH14 = 4;


const int AnalogReadDelay = 40;   // Read the analog value after this much milliseconds

float phPerVolt = 14.0 / MaxVoltatpH14;  // Calculate the ratio of pH change per volt
float tdsPerVolt;             // Ratio of TDS change per volt


float temperature = 25.0;        // Default temperature for compensation

// Create a MAX6675 object
MAX6675 thermocouple(MAX6675_CLK, MAX6675_CS, MAX6675_SO);

// Function to calculate median value
int getMedianNum(int bArray[], int iFilterLen) {
    int bTab[iFilterLen];
    for (byte i = 0; i < iFilterLen; i++)
        bTab[i] = bArray[i];
    int i, j, bTemp;
    for (j = 0; j < iFilterLen - 1; j++) {
        for (i = 0; i < iFilterLen - j - 1; i++) {
            if (bTab[i] > bTab[i + 1]) {
                bTemp = bTab[i];
                bTab[i] = bTab[i + 1];
                bTab[i + 1] = bTemp;
            }
        }
    }
    if ((iFilterLen & 1) > 0)
        bTemp = bTab[(iFilterLen - 1) / 2];
    else
        bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
    return bTemp;
}

// Function to read pH value
float read_ph() {
    int buf[avgCount]; // Buffer to store analog readings
    unsigned long int avgValue = 0; // Variable to store the sum of the middle 6 readings

    // Loop to take sample readings from the sensor
    for (int i = 0; i < avgCount; i++) {
        buf[i] = analogRead(SensorPin); // Read analog value from the sensor and store it in the buffer
        delay(AnalogReadDelay); // Delay for stability
    }

    // Calculate the median of the readings
    avgValue = getMedianNum(buf, avgCount);

    // Convert the analog reading to millivolts
    float millivolts = (float)avgValue * MaxOperVolt / MaxADCout / avgCount;

    // Convert millivolts to pH value using the linear relationship
    float pHValue = millivolts * phPerVolt;

    Serial.print("pH: "); // Print the pH value to the serial monitor
    Serial.println(pHValue, Decimal); // Print pH value with specified decimal places

    return pHValue;
}

// Function to read temperature
void read_temp() {
    // Read the temperature from the MAX6675 thermocouple
    double temperature = thermocouple.readCelsius();
  
    // Print the temperature readings to the serial monitor
    Serial.print("Temperature (C): ");
    Serial.println(temperature);

    // Wait for a brief moment before taking the next reading
    delay(AnalogReadDelay);
}

// Function to read TDS value
void TDS_read() {
    int buf[avgCount]; // Buffer to store analog readings
    unsigned long int avgValue = 0; // Variable to store the sum of the middle 6 readings

    // Loop to take sample readings from the sensor
    for (int i = 0; i < avgCount; i++) {
        buf[i] = analogRead(TdsSensorPin); // Read analog value from the sensor and store it in the buffer
        delay(AnalogReadDelay); // Delay for stability
    }

    // Calculate the median of the readings
    avgValue = getMedianNum(buf, avgCount);

    // Convert the analog reading to millivolts
    float millivolts = (float)avgValue * MaxOperVolt / MaxADCout / avgCount;

    // Convert millivolts to TDS value using the linear relationship
    float tdsValue = millivolts * tdsPerVolt;

    Serial.print("TDS Value: ");
    Serial.println(tdsValue, Decimal); // Print TDS value to the serial monitor
}

// Function to read turbidity value
void read_turbidity() {
    int buf[avgCount]; // Buffer to store analog readings
    unsigned long int avgValue = 0; // Variable to store the sum of the middle 6 readings

    // Loop to take sample readings from the sensor
    for (int i = 0; i < avgCount; i++) {
        buf[i] = analogRead(SensorPin); // Read analog value from the sensor and store it in the buffer
        delay(AnalogReadDelay); // Delay for stability
    }

    // Calculate the median of the readings
    avgValue = getMedianNum(buf, avgCount);

    // Convert the analog reading to millivolts
    float millivolts = (float)avgValue * MaxOperVolt / MaxADCout / avgCount;

    // Calculate turbidity based on the average voltage
    float turbidity = interpolate_turbidity(millivolts);

    // Compensate for temperature
    float compensated_turbidity = compensate_temperature(turbidity, temperature);

    // Print turbidity value to serial monitor
    Serial.print("Turbidity: ");
    Serial.println(compensated_turbidity, Decimal);
}

// Turbidity calibration based on voltage percentage
const float calibration_points[][2] = {
    {0, 100},      // 0 NTU corresponds to 100% voltage
    {500, 80.5},   // 500 NTU corresponds to 80.5% voltage
    {1000, 64.5},  // 1000 NTU corresponds to 64.5% voltage
    {2000, 45.2},  // 2000 NTU corresponds to 45.2% voltage
    {4000, 22.3}   // 4000 NTU corresponds to 22.3% voltage
};

// Piecewise linear interpolation function for voltage to NTU conversion
float interpolate_turbidity(float voltage) {
    for (int i = 0; i < sizeof(calibration_points) / sizeof(calibration_points[0]) - 1; i++) {
        float turbidity1 = calibration_points[i][0];
        float turbidity2 = calibration_points[i + 1][0];
        float voltage1 = calibration_points[i][1];
        float voltage2 = calibration_points[i + 1][1];
        if (voltage >= voltage1 && voltage <= voltage2) {
            return turbidity1 + (turbidity2 - turbidity1) * (voltage - voltage1) / (voltage2 - voltage1);
        }
    }
    return 0; // Default to 0 NTU if voltage is outside the range
}

// Function for temperature compensation
float compensate_temperature(float turbidity, float temperature) {
    // You can implement temperature compensation here
    // For demonstration, let's assume no compensation
    return turbidity;
}

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(MAX6675_CLK, OUTPUT);
  pinMode(MAX6675_CS, OUTPUT);
  pinMode(MAX6675_SO, INPUT);

  digitalWrite(MAX6675_CS, HIGH); // Set CS pin high to start with

  pinMode(TdsSensorPin, INPUT);
  pinMode(PHSensorPin, INPUT);
  

  // Wait for the MAX6675 module to stabilize
  delay(500);
}

void loop() {
    // Read pH value
    read_ph();

    // Read temperature
    read_temp();

    // Read TDS value
    TDS_read();

    // Read turbidity value
    read_turbidity();
}
