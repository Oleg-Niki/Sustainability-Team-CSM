const int buttonPins[] = {13, 12, 11, 10}; // Button pins (including START button on pin 10)
const int numButtons = 4;

void setup() {
    Serial.begin(9600); // Start serial communication
    for (int i = 0; i < numButtons; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP); // Set pins as input with pull-up resistors
    }
}

void loop() {
    for (int i = 0; i < numButtons; i++) {
        if (digitalRead(buttonPins[i]) == LOW) { // Button pressed (active LOW)
            switch (buttonPins[i]) {
                case 13:
                    Serial.println(1);
                    break;
                case 12:
                    Serial.println(2);
                    break;
                case 11:
                    Serial.println(3);
                    break;
                case 10:
                    Serial.println("START");
                    break;
            }
            delay(300); // Debounce delay
        }
    }
}
