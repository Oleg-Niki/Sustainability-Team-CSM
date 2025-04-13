// *********************
// Define LED pins for each board and pair
// *********************

// Board A LED definitions:
#define LED_RED_A1   23  // Board A pair 1 red LED
#define LED_GREEN_A1 22  // Board A pair 1 green LED
#define LED_RED_A2   25  // Board A pair 2 red LED
#define LED_GREEN_A2 24  // Board A pair 2 green LED

// Board C LED definitions:
#define LED_RED_C1    27  // Board C pair 1 red LED
#define LED_GREEN_C1  26  // Board C pair 1 green LED
#define LED_RED_C2    29  // Board C pair 2 red LED
#define LED_GREEN_C2  28  // Board C pair 2 green LED

// Board D LED definitions:
#define LED_RED_D2    31  // Board D pair 1 red LED
#define LED_GREEN_D2  30  // Board D pair 1 green LED
#define LED_RED_D3    33  // Board D pair 2 red LED
#define LED_GREEN_D3  32  // Board D pair 2 green LED
#define LED_RED_D1    35  // Board D pair 3 red LED
#define LED_GREEN_D1  34  // Board D pair 3 green LED

// Board E LED definitions:
#define LED_RED_E1    37  // Board E pair 1 red LED
#define LED_GREEN_E1  36  // Board E pair 1 green LED
#define LED_RED_E2    39  // Board E pair 2 red LED
#define LED_GREEN_E2  38  // Board E pair 2 green LED

// Board F LED definitions:
#define LED_RED_F1    43  // Board F pair 1 red LED
#define LED_GREEN_F1  40  // Board F pair 1 green LED

// *********************
// Setup function: called once at startup
// *********************
void setup() {
  // Initialize serial communications for four Nano boards:
  Serial.begin(9600);   // Nano A (USB/hardware Serial)
  Serial1.begin(9600);  // Nano C (Serial1)
  Serial2.begin(9600);  // Nano D (Serial2)
  Serial3.begin(9600);  // Nano E (Serial3)

  // Builtin LED light: initialize the built-in LED as an output and turn it off.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);  

  // Set up output pins for Board A LEDs:
  pinMode(LED_RED_A1, OUTPUT);
  pinMode(LED_GREEN_A1, OUTPUT);
  pinMode(LED_RED_A2, OUTPUT);
  pinMode(LED_GREEN_A2, OUTPUT);

  // Set up output pins for Board C LEDs:
  pinMode(LED_RED_C1, OUTPUT);
  pinMode(LED_GREEN_C1, OUTPUT);
  pinMode(LED_RED_C2, OUTPUT);
  pinMode(LED_GREEN_C2, OUTPUT);

  // Set up output pins for Board D LEDs:
  pinMode(LED_RED_D1, OUTPUT);
  pinMode(LED_GREEN_D1, OUTPUT);
  pinMode(LED_RED_D2, OUTPUT);
  pinMode(LED_GREEN_D2, OUTPUT);
  pinMode(LED_RED_D3, OUTPUT);
  pinMode(LED_GREEN_D3, OUTPUT);

  // Set up output pins for Board E LEDs:
  pinMode(LED_RED_E1, OUTPUT);
  pinMode(LED_GREEN_E1, OUTPUT);
  pinMode(LED_RED_E2, OUTPUT);
  pinMode(LED_GREEN_E2, OUTPUT);

  // Set up output pins for Board F LEDs:
  pinMode(LED_RED_F1, OUTPUT);
  pinMode(LED_GREEN_F1, OUTPUT);

  // Turn all LEDs off initially (active-low: HIGH means off)
  resetLEDs();
}

// *********************
// Loop function: runs continuously after setup()
// *********************
void loop() {
  // Check for commands from Nano A via Serial:
  if (Serial.available() > 0) {  
    String command = Serial.readStringUntil('\n');
    command.trim();
    Serial.print("From Nano A: ");
    Serial.println(command);
    handleLEDCommand(command);
  }
  
  // Check for commands from Nano C via Serial1:
  if (Serial1.available() > 0) {  
    String command = Serial1.readStringUntil('\n');
    command.trim();
    Serial.print("From Nano C: ");
    Serial.println(command);
    handleLEDCommand(command);
  }
  
  // Check for commands from Nano D via Serial2:
  if (Serial2.available() > 0) {  
    String command = Serial2.readStringUntil('\n');
    command.trim();
    Serial.print("From Nano D: ");
    Serial.println(command);
    handleLEDCommand(command);
  }
  
  // Check for commands from Nano E via Serial3:
  if (Serial3.available() > 0) {  
    String command = Serial3.readStringUntil('\n');
    command.trim();
    Serial.print("From Nano E: ");
    Serial.println(command);
    handleLEDCommand(command);
  }

  // Check the status of each LED group for blinking logic:
  checkGroupStatus();  
}

// *********************
// Function: handleLEDCommand()
// Description: Processes incoming command strings to control the LED states.
// *********************
void handleLEDCommand(String command) {
// Check for reset command from the website
// if (command == "RESET_LEDS") {
//   resetLEDs();
//   Serial.println("LEDs reset");
//   return; // Exit the function after resetting the LEDs
// }
  // --- Board A Commands ---
if (command == "A1_RED") { 
  digitalWrite(LED_RED_A1, LOW);
  digitalWrite(LED_GREEN_A1, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("RED");
} else if (command == "A1_GREEN") {
  digitalWrite(LED_RED_A1, HIGH);
  digitalWrite(LED_GREEN_A1, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("GREEN");
} else if (command == "A2_RED") {
  digitalWrite(LED_RED_A2, LOW);
  digitalWrite(LED_GREEN_A2, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("RED");
} else if (command == "A2_GREEN") {
  digitalWrite(LED_RED_A2, HIGH);
  digitalWrite(LED_GREEN_A2, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("GREEN");
}
// --- Board C Commands ---
else if (command == "C1_RED") { 
  digitalWrite(LED_RED_C1, LOW);
  digitalWrite(LED_GREEN_C1, HIGH);
  Serial.println("RED");
} else if (command == "C1_GREEN") {
  digitalWrite(LED_RED_C1, HIGH);
  digitalWrite(LED_GREEN_C1, LOW);
  Serial.println("GREEN");
} else if (command == "C2_RED") {
  digitalWrite(LED_RED_C2, LOW);
  digitalWrite(LED_GREEN_C2, HIGH);
  Serial.println("RED");
} else if (command == "C2_GREEN") {
  digitalWrite(LED_RED_C2, HIGH);
  digitalWrite(LED_GREEN_C2, LOW);
  Serial.println("GREEN");
}
// --- Board D Commands ---
else if (command == "D1_RED") {
  digitalWrite(LED_RED_D1, LOW);
  digitalWrite(LED_GREEN_D1, HIGH);
  Serial.println("RED");
} else if (command == "D1_GREEN") {
  digitalWrite(LED_RED_D1, HIGH);
  digitalWrite(LED_GREEN_D1, LOW);
  Serial.println("GREEN");
} else if (command == "D2_RED") {
  digitalWrite(LED_RED_D2, LOW);
  digitalWrite(LED_GREEN_D2, HIGH);
  Serial.println("RED");
} else if (command == "D2_GREEN") {
  digitalWrite(LED_RED_D2, HIGH);
  digitalWrite(LED_GREEN_D2, LOW);
  Serial.println("GREEN");
} else if (command == "D3_RED") {
  digitalWrite(LED_RED_D3, LOW);
  digitalWrite(LED_GREEN_D3, HIGH);
  Serial.println("RED");
} else if (command == "D3_GREEN") {
  digitalWrite(LED_RED_D3, HIGH);
  digitalWrite(LED_GREEN_D3, LOW);
  Serial.println("GREEN");
}
// --- Board E Commands ---
else if (command == "E1_RED") {
  digitalWrite(LED_RED_E1, LOW);
  digitalWrite(LED_GREEN_E1, HIGH);
  Serial.println("RED");
} else if (command == "E1_GREEN") {
  digitalWrite(LED_RED_E1, HIGH);
  digitalWrite(LED_GREEN_E1, LOW);
  Serial.println("GREEN");
} else if (command == "E2_RED") {
  digitalWrite(LED_RED_E2, LOW);
  digitalWrite(LED_GREEN_E2, HIGH);
  Serial.println("RED");
} else if (command == "E2_GREEN") {
  digitalWrite(LED_RED_E2, HIGH);
  digitalWrite(LED_GREEN_E2, LOW);
  Serial.println("GREEN");
}
// --- Board F Commands ---
else if (command == "F1_RED") {
  digitalWrite(LED_RED_F1, LOW);
  digitalWrite(LED_GREEN_F1, HIGH);
  Serial.println("RED");
} else if (command == "F1_GREEN") {
  digitalWrite(LED_RED_F1, HIGH);
  digitalWrite(LED_GREEN_F1, LOW);
  Serial.println("GREEN");
}

}

// *********************
// Function: checkGroupStatus()
// Description: Checks the status of each LED pair across all boards and blinks accordingly.
// *********************
void checkGroupStatus() {
  bool groupA1On = (digitalRead(LED_RED_A1) == LOW || digitalRead(LED_GREEN_A1) == LOW);
  bool groupA2On = (digitalRead(LED_RED_A2) == LOW || digitalRead(LED_GREEN_A2) == LOW);
  bool groupC1On = (digitalRead(LED_RED_C1) == LOW || digitalRead(LED_GREEN_C1) == LOW);
  bool groupC2On = (digitalRead(LED_RED_C2) == LOW || digitalRead(LED_GREEN_C2) == LOW);
  bool groupD1On = (digitalRead(LED_RED_D1) == LOW || digitalRead(LED_GREEN_D1) == LOW);
  bool groupD2On = (digitalRead(LED_RED_D2) == LOW || digitalRead(LED_GREEN_D2) == LOW);
  bool groupD3On = (digitalRead(LED_RED_D3) == LOW || digitalRead(LED_GREEN_D3) == LOW);
  bool groupE1On = (digitalRead(LED_RED_E1) == LOW || digitalRead(LED_GREEN_E1) == LOW);
  bool groupE2On = (digitalRead(LED_RED_E2) == LOW || digitalRead(LED_GREEN_E2) == LOW);
  bool groupF1On = (digitalRead(LED_RED_F1) == LOW || digitalRead(LED_GREEN_F1) == LOW);

  if (groupA1On && groupA2On && groupC1On && groupC2On &&
      groupD1On && groupD2On && groupD3On &&
      groupE1On && groupE2On &&
      groupF1On) {

    bool allGreen = (digitalRead(LED_GREEN_A1) == LOW && digitalRead(LED_GREEN_A2) == LOW &&
                     digitalRead(LED_GREEN_C1) == LOW && digitalRead(LED_GREEN_C2) == LOW &&
                     digitalRead(LED_GREEN_D1) == LOW && digitalRead(LED_GREEN_D2) == LOW && digitalRead(LED_GREEN_D3) == LOW &&
                     digitalRead(LED_GREEN_E1) == LOW && digitalRead(LED_GREEN_E2) == LOW &&
                     digitalRead(LED_GREEN_F1) == LOW);

    if (allGreen) {
      blinkLEDs(LED_GREEN_A1, LED_GREEN_A2,
                LED_GREEN_C1, LED_GREEN_C2,
                LED_GREEN_D1, LED_GREEN_D2, LED_GREEN_D3,
                LED_GREEN_E1, LED_GREEN_E2,
                LED_GREEN_F1);
    } else {
      blinkLEDs(LED_RED_A1, LED_RED_A2,
                LED_RED_C1, LED_RED_C2,
                LED_RED_D1, LED_RED_D2, LED_RED_D3,
                LED_RED_E1, LED_RED_E2,
                LED_RED_F1);
    }
  }
}

// *********************
// Function: blinkLEDs()
// Description: Blinks 10 LED pins five times.
// *********************
void blinkLEDs(int led1, int led2, int led3, int led4, int led5, int led6,
               int led7, int led8, int led9, int led10) {
  for (int i = 0; i < 5; i++) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
    digitalWrite(led9, LOW);
    digitalWrite(led10, LOW);
    delay(500);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    digitalWrite(led7, HIGH);
    digitalWrite(led8, HIGH);
    digitalWrite(led9, HIGH);
    digitalWrite(led10, HIGH);
    delay(500);
  }
  resetLEDs();
}

// *********************
// Function: resetLEDs()
// Description: Turns off all LEDs (active-low: HIGH means off)
// *********************
void resetLEDs() {
  digitalWrite(LED_RED_A1, HIGH);
  digitalWrite(LED_GREEN_A1, HIGH);
  digitalWrite(LED_RED_A2, HIGH);
  digitalWrite(LED_GREEN_A2, HIGH);
  digitalWrite(LED_RED_C1, HIGH);
  digitalWrite(LED_GREEN_C1, HIGH);
  digitalWrite(LED_RED_C2, HIGH);
  digitalWrite(LED_GREEN_C2, HIGH);
  digitalWrite(LED_RED_D1, HIGH);
  digitalWrite(LED_GREEN_D1, HIGH);
  digitalWrite(LED_RED_D2, HIGH);
  digitalWrite(LED_GREEN_D2, HIGH);
  digitalWrite(LED_RED_D3, HIGH);
  digitalWrite(LED_GREEN_D3, HIGH);
  digitalWrite(LED_RED_E1, HIGH);
  digitalWrite(LED_GREEN_E1, HIGH);
  digitalWrite(LED_RED_E2, HIGH);
  digitalWrite(LED_GREEN_E2, HIGH);
  digitalWrite(LED_RED_F1, HIGH);
  digitalWrite(LED_GREEN_F1, HIGH);
}
