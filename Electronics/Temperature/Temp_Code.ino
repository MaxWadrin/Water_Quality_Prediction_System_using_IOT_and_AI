#include <max6675.h>

// Define the pins connected to the MAX6675 module
#define MAX6675_CLK 18
#define MAX6675_CS  5
#define MAX6675_SO  19

// Create a MAX6675 object
MAX6675 thermocouple(MAX6675_CLK, MAX6675_CS, MAX6675_SO);

void setup() {
  Serial.begin(115200);
  delay(500);
  
  // Initialize the MAX6675 module
  thermocouple.begin();
  
  // Wait for the MAX6675 module to stabilize
  delay(500);
}

void loop() {
  // Read the temperature from the MAX6675 thermocouple
  double celsius = thermocouple.readCelsius();
  double fahrenheit = thermocouple.readFahrenheit();
  
  // Print the temperature readings to the serial monitor
  Serial.print("Temperature (C): ");
  Serial.print(celsius);
  Serial.print("  Temperature (F): ");
  Serial.println(fahrenheit);
  
  // Wait for a brief moment before taking the next reading
  delay(1000);
}
