#define SensorPin A0          // Define the pin to which the pH meter Analog output is connected

const int MaxOperVolt = 5;    // Maximum operating voltage of the Arduino (in volts)
const int MaxVoltatpH14 = 4;  // Maximum voltage output of the pH amplifier at pH 14 (in volts)
const int MaxADCout = 1024;   // Maximum output of the analog-to-digital converter (ADC)
const int avgCount = 6;       // Number of readings to average for smoothing
const int Decimal = 2;        // Decimal point of the ph output

float phPerVolt;              // Ratio of pH change per volt

unsigned long int avgValue;   // Store the average value of the sensor feedback
float b;                      // Unused variable

int buf[10],temp;             // Array to store raw sensor readings, temporary variable

void setup() {
  pinMode(13,OUTPUT);         // Set pin 13 (LED) as an output
  Serial.begin(9600);         // Initialize serial communication at 9600 baud rate
  Serial.println("Ready");    // Print "Ready" message to the serial monitor

  phPerVolt = 14.0 / MaxVoltatpH14;  // Calculate the ratio of pH change per volt
}

void loop() {
  for(int i=0;i<10;i++) {     // Loop to take 10 sample readings from the sensor
    buf[i]=analogRead(SensorPin); // Read analog value from the sensor and store it in the buffer
    delay(10);                // Delay for stability
  }

  for(int i=0;i<9;i++) {      // Sorting the readings in ascending order
    for(int j=i+1;j<10;j++) {
      if(buf[i]>buf[j]) {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }

  avgValue=0;                 // Initialize average value
  for(int i=2;i<8;i++) {      // Taking the average of the middle 6 readings
    avgValue+=buf[i];
  }

  // Convert the analog reading to millivolts
  float millivolts = (float)avgValue * MaxOperVolt / MaxADCout / avgCount;

  // Convert millivolts to pH value using the linear relationship
  float pHValue = millivolts * phPerVolt;

  Serial.print("    pH:");    // Print the pH value to the serial monitor
  Serial.print(pHValue, Decimal);   // Print pH value with two decimal places
  Serial.println(" ");        // Print a newline character

  digitalWrite(13, HIGH);     // Turn on the LED on pin 13
  delay(800);                 // Delay for 800 milliseconds
  digitalWrite(13, LOW);      // Turn off the LED
}
