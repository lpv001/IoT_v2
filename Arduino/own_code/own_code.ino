

unsigned long startTime = 0; // Stores the time when the button is pressed
bool buttonPressed = false;  // Flag to indicate button press state

void setup() {
  Serial.begin(115200);
  pinMode(0, INPUT_PULLUP);
  pinMode(D4, OUTPUT); 
  digitalWrite(D4, HIGH);
}

void loop() {
  int buttonState1 = digitalRead(0);
  int buttonState = 0;
  if(buttonState1 == 1){
    buttonState = 0;
  }else{
    buttonState = 1;
  }

  // Check for button state change (press or release)
  if (buttonState != buttonPressed) {
    if (buttonState == HIGH) {
      // Button pressed
      startTime = millis(); // Start timer on button press
      Serial.println(startTime);
      buttonPressed = true;
    } else {
      // Button released
      unsigned long holdTime = millis() - startTime;
      if (buttonPressed) { // Ensure button was truly pressed before release
        // Do something with the hold time (e.g., print to serial monitor)
        Serial.print("Button held for: ");
        Serial.println(holdTime);
        // Optionally control LED based on hold time
        if (holdTime > 1000) { // Adjust threshold for long press
          digitalWrite(D4,LOW); // Turn on LED for long press
        } else {
          digitalWrite(D4,HIGH); // Turn off LED for short press
        }
      }
      buttonPressed = false; // Reset button press flag
    }
  }
  
}
