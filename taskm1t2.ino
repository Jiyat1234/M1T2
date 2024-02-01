const int ledPin = 13;
const int pirPin = 7;
const int buttonPin = 3;

int ledState = LOW;
unsigned long lastDebounceTime = 0;
const int debounceDelay = 50;
const long ledDuration = 3000; // Adjust if needed
unsigned long motionStartTime = 0;

bool motionDetected = false; // Flag to track motion state

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pirPin), PIR_motionDetected, RISING);
  Serial.begin(9600);
}

void loop() {
  checkButton();
  updateLED();
}

void checkButton() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && millis() - lastDebounceTime > debounceDelay) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    Serial.println("Button pressed, LED toggled");
    lastDebounceTime = millis();
  }
}

void updateLED() {
  if (motionDetected) {
    digitalWrite(ledPin, HIGH); // Keep LED on while motion is detected
  } else {
    if (ledState == HIGH && millis() - motionStartTime >= ledDuration) {
      ledState = LOW;
      digitalWrite(ledPin, ledState);
      Serial.println("LED turned off");
    }
  }
}

void PIR_motionDetected() {
  digitalWrite(ledPin, HIGH);
  Serial.println("Motion detected!");
  motionStartTime = millis();
  motionDetected = true; // Set flag to indicate motion
}
