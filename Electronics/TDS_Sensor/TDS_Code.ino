#define TdsSensorPin 13          // Define the pin to which the TDS sensor Analog output is connected

const float MaxOperVolt = 5.0;   // Maximum operating voltage of the Arduino (in volts)
const float MaxVoltatTDSMax = 3.3;  // Maximum voltage output of the TDS sensor at maximum TDS value (in volts)
const int MaxADCout = 1024;      // Maximum output of the analog-to-digital converter (ADC)
const int avgCount = 30;         // Number of readings to average for stability
const int Decimal = 0;           // Decimal point of the TDS output
const int AnalogReadDelay = 40;   // Read the analog value after this much milliseconds

float tdsPerVolt;                // Ratio of TDS change per volt

int analogBuffer[avgCount];      // Array to store raw sensor readings
int analogBufferTemp[avgCount];
int analogBufferIndex = 0, copyIndex = 0;  // Variables for indexing analogBuffer array
float temperature = 25.0;        // Default temperature for compensation

void setup()
{
    Serial.begin(115200);
    pinMode(TdsSensorPin, INPUT);
}

void loop()
{
    static unsigned long analogSampleTimepoint = millis();
    if (millis() - analogSampleTimepoint > AnalogReadDelay)     // Every 40 milliseconds, read the analog value from the ADC
    {
        analogSampleTimepoint = millis();
        analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);    // Read the analog value and store into the buffer
        analogBufferIndex++;
        if (analogBufferIndex == avgCount)
            analogBufferIndex = 0;
    }

    static unsigned long printTimepoint = millis();
    if (millis() - printTimepoint > 800U)
    {
        printTimepoint = millis();
        for (copyIndex = 0; copyIndex < avgCount; copyIndex++)
            analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
        float averageVoltage = getMedianNum(analogBufferTemp, avgCount) * (float)MaxOperVolt / MaxADCout; // Read the analog value more stable by the median filtering algorithm, and convert to voltage value
        float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);    // Temperature compensation formula: fFinalResult(25^C) = fFinalResult(current) / (1.0 + 0.02 * (fTP - 25.0));
        float compensationVolatge = averageVoltage / compensationCoefficient;  // Temperature compensation
        float tdsValue = (133.42 * compensationVolatge * compensationVolatge * compensationVolatge - 255.86 * compensationVolatge * compensationVolatge + 857.39 * compensationVolatge) * 0.5; // Convert voltage value to TDS value

        Serial.print("TDS Value: ");
        Serial.print(tdsValue, Decimal);
        Serial.println(" ppm");
    }
}

int getMedianNum(int bArray[], int iFilterLen)
{
    int bTab[iFilterLen];
    for (byte i = 0; i < iFilterLen; i++)
        bTab[i] = bArray[i];
    int i, j, bTemp;
    for (j = 0; j < iFilterLen - 1; j++)
    {
        for (i = 0; i < iFilterLen - j - 1; i++)
        {
            if (bTab[i] > bTab[i + 1])
            {
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
