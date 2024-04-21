const int desiredADCPin = A0; // Replace A0 with the desired ADC pin number

void setup() {
  pinMode(desiredADCPin, OUTPUT); // Set the desired ADC pin as an output
}

void loop() {
  digitalWrite(desiredADCPin, HIGH); // Set the desired ADC pin high
  delay(1000); // Wait for 1 second
}
