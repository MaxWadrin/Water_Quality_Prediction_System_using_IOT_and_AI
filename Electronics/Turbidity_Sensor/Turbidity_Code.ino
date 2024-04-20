#define TurbiditySensorPin 13      // Define the pin to which the turbidity sensor Analog output is connected

const float MaxOperVolt = 5.0;     // Maximum operating voltage of the Arduino (in volts)
const float MaxVoltatNTUMax = 3.3; // Maximum voltage output of the turbidity sensor at maximum NTU value (in volts)
const int MaxADCout = 1024;        // Maximum output of the analog-to-digital converter (ADC)
const int avgCount = 30;           // Number of readings to average for stability
const int Decimal = 0;             // Decimal point of the turbidity output
const int AnalogReadDelay = 40;    // Read the analog value after this much milliseconds

float turbidityPerVolt;            // Ratio of turbidity change per volt

int analogBuffer[avgCount];        // Array to store raw sensor readings
int analogBufferTemp[avgCount];
int analogBufferIndex = 0, copyIndex = 0;  // Variables for indexing analogBuffer array
float temperature = 25.0;          // Default temperature for compensation

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

// Piecewise linear interpolation function for temperature compensation
float compensate_temperature(float turbidity, float temperature) {
    float voltage_percentage = interpolate_turbidity(turbidity);
    // Define temperature compensation points: (Temperature, Compensation Percentage)
    const float temp_compensation_points[][2] = {
        {10, 100},
        {20, 98},
        {30, 95},
        {40, 94},
        {50, 89}
    };
    for (int i = 0; i < sizeof(temp_compensation_points) / sizeof(temp_compensation_points[0]) - 1; i++) {
        float temp1 = temp_compensation_points[i][0];
        float temp2 = temp_compensation_points[i + 1][0];
        float comp_percentage1 = temp_compensation_points[i][1];
        float comp_percentage2 = temp_compensation_points[i + 1][1];
        if (temperature >= temp1 && temperature <= temp2) {
            return voltage_percentage * (comp_percentage1 + (comp_percentage2 - comp_percentage1) * (temperature - temp1) / (temp2 - temp1)) / 100.0;
        }
    }
    return voltage_percentage;
}

void setup() {
    Serial.begin(115200);
    pinMode(TurbiditySensorPin, INPUT);
}

void loop() {
    static unsigned long analogSampleTimepoint = millis();
    if (millis() - analogSampleTimepoint > AnalogReadDelay) {
        analogSampleTimepoint = millis();
        analogBuffer[analogBufferIndex] = analogRead(TurbiditySensorPin); // Read the analog value and store into the buffer
        analogBufferIndex++;
        if (analogBufferIndex == avgCount)
            analogBufferIndex = 0;
    }

    static unsigned long printTimepoint = millis();
    if (millis() - printTimepoint > 800) {
        printTimepoint = millis();
        for (copyIndex = 0; copyIndex < avgCount; copyIndex++)
            analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
        float averageVoltage = getMedianNum(analogBufferTemp, avgCount) * MaxOperVolt / MaxADCout; // Read the analog value more stable by the median filtering algorithm, and convert to voltage value
        float turbidity = interpolate_turbidity(averageVoltage);
        float compensated_turbidity = compensate_temperature(turbidity, temperature); // Temperature compensation
        Serial.print("Turbidity: ");
        Serial.print(compensated_turbidity, Decimal);
        Serial.println(" NTU");
    }
}

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
