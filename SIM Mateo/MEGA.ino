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
#define LED_RED_D1    33  // Board D pair 1 red LED
#define LED_GREEN_D1  32  // Board D pair 1 green LED
#define LED_RED_D2    35  // Board D pair 2 red LED
#define LED_GREEN_D2  34  // Board D pair 2 green LED
#define LED_RED_D3    31  // Board D pair 3 red LED
#define LED_GREEN_D3  30  // Board D pair 3 green LED

// Board E LED definitions:
#define LED_RED_E1    37  // Board E pair 1 red LED
#define LED_GREEN_E1  36  // Board E pair 1 green LED
#define LED_RED_E2    39  // Board E pair 2 red LED
#define LED_GREEN_E2  38  // Board E pair 2 green LED

// Board F LED definitions:
#define LED_RED_F1    43  // Board F pair 1 red LED
#define LED_GREEN_F1  40  // Board F pair 1 green LED

// *********************
// State Machine Setup and Global Variables
// *********************

enum SystemState { 
  STATE_IDLE,              // Not all groups are active
  STATE_WAITING_FOR_GREEN, // All groups active but not all green LEDs are lit yet
  STATE_BLINKING           // All green LEDs are lit; blink sequence active
};

SystemState currentState = STATE_IDLE;

// For periodic state checks:
unsigned long lastStateCheckTime = 0;
const unsigned long stateCheckInterval = 100; // milliseconds

// Variables for non-blocking blinking using millis()
unsigned long blinkPrevMillis = 0;
const unsigned long blinkInterval = 500;      // Blink every 500ms
int blinkCount = 0;
const int totalBlinks = 5;                    // Blink 5 times
bool blinkOn = false;                         // Current blinking phase

// Array of green LED pins for blinking (active-low: LOW = LED on)
int ledPins[10] = { LED_GREEN_A1, LED_GREEN_A2, 
                    LED_GREEN_C1, LED_GREEN_C2,
                    LED_GREEN_D1, LED_GREEN_D2, LED_GREEN_D3,
                    LED_GREEN_E1, LED_GREEN_E2, 
                    LED_GREEN_F1 };

// *********************
// Setup Function: Runs once at startup
// *********************
void setup() {
  // Initialize serial communications for four Nano boards:
  Serial.begin(9600);   // Nano A (USB/hardware Serial)
  Serial1.begin(9600);  // Nano C (Serial1)
  Serial2.begin(9600);  // Nano D (Serial2)
  Serial3.begin(9600);  // Nano E (Serial3)
  
  // Set up output pins for Board A LEDs:
  pinMode(LED_RED_A1, OUTPUT);
  pinMode(LED_GREEN_A1, OUTPUT);
  pinMode(LED_RED_A2, OUTPUT);
  pinMode(LED_GREEN_A2, OUTPUT);

  // Board C LEDs:
  pinMode(LED_RED_C1, OUTPUT);
  pinMode(LED_GREEN_C1, OUTPUT);
  pinMode(LED_RED_C2, OUTPUT);
  pinMode(LED_GREEN_C2, OUTPUT);

  // Board D LEDs:
  pinMode(LED_RED_D1, OUTPUT);
  pinMode(LED_GREEN_D1, OUTPUT);
  pinMode(LED_RED_D2, OUTPUT);
  pinMode(LED_GREEN_D2, OUTPUT);
  pinMode(LED_RED_D3, OUTPUT);
  pinMode(LED_GREEN_D3, OUTPUT);

  // Board E LEDs:
  pinMode(LED_RED_E1, OUTPUT);
  pinMode(LED_GREEN_E1, OUTPUT);
  pinMode(LED_RED_E2, OUTPUT);
  pinMode(LED_GREEN_E2, OUTPUT);

  // Board F LEDs:
  pinMode(LED_RED_F1, OUTPUT);
  pinMode(LED_GREEN_F1, OUTPUT);

  // Turn all LEDs off initially (active-low: HIGH means LED off)
  resetLEDs();
}

// *********************
// Main Loop: Runs continuously after setup()
// *********************
void loop() {
  // Always process incoming serial commands:
  processSerialCommands();
  
  unsigned long currentMillis = millis();
  
  // Periodically update the system state (non-blocking):
  if (currentMillis - lastStateCheckTime >= stateCheckInterval) {
    lastStateCheckTime = currentMillis;
    updateSystemState();
  }
  
  // If in the BLINKING state, update the blinking sequence non-blockingly:
  if (currentState == STATE_BLINKING) {
    updateBlinking(currentMillis);
  }
}

// *********************
// Serial Command Processing
// *********************
void processSerialCommands() {
  if (Serial.available() > 0) {  
    String command = Serial.readStringUntil('\n');
    command.trim();
    Serial.print("From Nano A: ");
    Serial.println(command);
    handleLEDCommand(command);
  }
  
  if (Serial1.available() > 0) {  
    String command = Serial1.readStringUntil('\n');
    command.trim();
    Serial.print("From Nano C: ");
    Serial.println(command);
    handleLEDCommand(command);
  }
  
  if (Serial2.available() > 0) {  
    String command = Serial2.readStringUntil('\n');
    command.trim();
    Serial.print("From Nano D: ");
    Serial.println(command);
    handleLEDCommand(command);
  }
  
  if (Serial3.available() > 0) {  
    String command = Serial3.readStringUntil('\n');
    command.trim();
    Serial.print("From Nano E: ");
    Serial.println(command);
    handleLEDCommand(command);
  }
}

// *********************
// Process Incoming LED Commands
// *********************
void handleLEDCommand(String command) {
  // Remove any extra whitespace from the command.
  command.trim();
  
  // Check for the RESET command first.
  if (command == "RESET") {
    Serial.println("Resetting LEDs and system state...");
    resetLEDs();             // Turn all LEDs off.
    currentState = STATE_IDLE; // Reset the system state.
    blinkCount = 0;            // Reset blink counter.
    blinkOn = false;           // Reset blinking phase.
    return;                  // Exit without processing further.
  }
  // --- Board A Commands ---
  if (command == "A1_RED") { 
    digitalWrite(LED_RED_A1, LOW);
    digitalWrite(LED_GREEN_A1, HIGH);
    Serial.println("A1_RED");
  } else if (command == "A1_GREEN") {
    digitalWrite(LED_RED_A1, HIGH);
    digitalWrite(LED_GREEN_A1, LOW);
    Serial.println("A1_GREEN");
  } else if (command == "A2_RED") {
    digitalWrite(LED_RED_A2, LOW);
    digitalWrite(LED_GREEN_A2, HIGH);
    Serial.println("A2_RED");
  } else if (command == "A2_GREEN") {
    digitalWrite(LED_RED_A2, HIGH);
    digitalWrite(LED_GREEN_A2, LOW);
    Serial.println("A2_GREEN");
  }
  // --- Board C Commands ---
  else if (command == "C1_RED") { 
    digitalWrite(LED_RED_C1, LOW);
    digitalWrite(LED_GREEN_C1, HIGH);
    Serial.println("C1_RED");
  } else if (command == "C1_GREEN") {
    digitalWrite(LED_RED_C1, HIGH);
    digitalWrite(LED_GREEN_C1, LOW);
    Serial.println("C1_GREEN");
  } else if (command == "C2_RED") {
    digitalWrite(LED_RED_C2, LOW);
    digitalWrite(LED_GREEN_C2, HIGH);
    Serial.println("C2_RED");
  } else if (command == "C2_GREEN") {
    digitalWrite(LED_RED_C2, HIGH);
    digitalWrite(LED_GREEN_C2, LOW);
    Serial.println("C2_GREEN");
  }
  // --- Board D Commands ---
  else if (command == "D1_RED") {
    digitalWrite(LED_RED_D1, LOW);
    digitalWrite(LED_GREEN_D1, HIGH);
    Serial.println("D1_RED");
  } else if (command == "D1_GREEN") {
    digitalWrite(LED_RED_D1, HIGH);
    digitalWrite(LED_GREEN_D1, LOW);
    Serial.println("D1_GREEN");
  } else if (command == "D2_RED") {
    digitalWrite(LED_RED_D2, LOW);
    digitalWrite(LED_GREEN_D2, HIGH);
    Serial.println("D2_RED");
  } else if (command == "D2_GREEN") {
    digitalWrite(LED_RED_D2, HIGH);
    digitalWrite(LED_GREEN_D2, LOW);
    Serial.println("D2_GREEN");
  } else if (command == "D3_RED") {
    digitalWrite(LED_RED_D3, LOW);
    digitalWrite(LED_GREEN_D3, HIGH);
    Serial.println("D3_RED");
  } else if (command == "D3_GREEN") {
    digitalWrite(LED_RED_D3, HIGH);
    digitalWrite(LED_GREEN_D3, LOW);
    Serial.println("D3_GREEN");
  }
  // --- Board E Commands ---
  else if (command == "E1_RED") {
    digitalWrite(LED_RED_E1, LOW);
    digitalWrite(LED_GREEN_E1, HIGH);
    Serial.println("E1_RED");
  } else if (command == "E1_GREEN") {
    digitalWrite(LED_RED_E1, HIGH);
    digitalWrite(LED_GREEN_E1, LOW);
    Serial.println("E1_GREEN");
  } else if (command == "E2_RED") {
    digitalWrite(LED_RED_E2, LOW);
    digitalWrite(LED_GREEN_E2, HIGH);
    Serial.println("E2_RED");
  } else if (command == "E2_GREEN") {
    digitalWrite(LED_RED_E2, HIGH);
    digitalWrite(LED_GREEN_E2, LOW);
    Serial.println("E2_GREEN");
  }
  // --- Board F Commands ---
  else if (command == "F1_RED") {
    digitalWrite(LED_RED_F1, LOW);
    digitalWrite(LED_GREEN_F1, HIGH);
    Serial.println("F1_RED");
  } else if (command == "F1_GREEN") {
    digitalWrite(LED_RED_F1, HIGH);
    digitalWrite(LED_GREEN_F1, LOW);
    Serial.println("F1_GREEN");
  }
}

// *********************
// Check if all LED groups (pairs) have been set (either LED active)
// *********************
bool checkGroupsActive() {
  bool groupA1 = (digitalRead(LED_RED_A1) == LOW || digitalRead(LED_GREEN_A1) == LOW);
  bool groupA2 = (digitalRead(LED_RED_A2) == LOW || digitalRead(LED_GREEN_A2) == LOW);
  bool groupC1 = (digitalRead(LED_RED_C1) == LOW || digitalRead(LED_GREEN_C1) == LOW);
  bool groupC2 = (digitalRead(LED_RED_C2) == LOW || digitalRead(LED_GREEN_C2) == LOW);
  bool groupD1 = (digitalRead(LED_RED_D1) == LOW || digitalRead(LED_GREEN_D1) == LOW);
  bool groupD2 = (digitalRead(LED_RED_D2) == LOW || digitalRead(LED_GREEN_D2) == LOW);
  bool groupD3 = (digitalRead(LED_RED_D3) == LOW || digitalRead(LED_GREEN_D3) == LOW);
  bool groupE1 = (digitalRead(LED_RED_E1) == LOW || digitalRead(LED_GREEN_E1) == LOW);
  bool groupE2 = (digitalRead(LED_RED_E2) == LOW || digitalRead(LED_GREEN_E2) == LOW);
  bool groupF1 = (digitalRead(LED_RED_F1) == LOW || digitalRead(LED_GREEN_F1) == LOW);
  return (groupA1 && groupA2 && groupC1 && groupC2 &&
          groupD1 && groupD2 && groupD3 &&
          groupE1 && groupE2 && groupF1);
}

// *********************
// Check if all green LEDs are lit (active-low: LOW means ON)
// *********************
bool checkAllGreen() {
  return (digitalRead(LED_GREEN_A1) == LOW &&
          digitalRead(LED_GREEN_A2) == LOW &&
          digitalRead(LED_GREEN_C1) == LOW &&
          digitalRead(LED_GREEN_C2) == LOW &&
          digitalRead(LED_GREEN_D1) == LOW &&
          digitalRead(LED_GREEN_D2) == LOW &&
          digitalRead(LED_GREEN_D3) == LOW &&
          digitalRead(LED_GREEN_E1) == LOW &&
          digitalRead(LED_GREEN_E2) == LOW &&
          digitalRead(LED_GREEN_F1) == LOW);
}

// *********************
// Update the system state (non-blocking)
// *********************
void updateSystemState() {
  if (checkGroupsActive()) {
    if (checkAllGreen()) {
      // All groups active and all green LEDs lit; start blinking sequence.
      currentState = STATE_BLINKING;
      blinkCount = 0;
      blinkPrevMillis = millis();
      blinkOn = false;
    } else {
      // Wait in this state until all green LEDs become active.
      currentState = STATE_WAITING_FOR_GREEN;
    }
  } else {
    // Not all groups have been set by incoming commands.
    currentState = STATE_IDLE;
  }
}

// *********************
// Update blinking sequence without blocking using millis()
// *********************
void updateBlinking(unsigned long currentMillis) {
  if (currentMillis - blinkPrevMillis >= blinkInterval) {
    blinkPrevMillis = currentMillis;
    blinkOn = !blinkOn; // Toggle LED state

    // Update all green LED pins accordingly.
    for (int i = 0; i < 10; i++) {
      digitalWrite(ledPins[i], blinkOn ? LOW : HIGH);
    }

    // Count blink cycles when turning the LEDs on.
    if (blinkOn) {
      blinkCount++;
    }
    if (blinkCount >= totalBlinks) {
      // End the blinking sequence and reset LEDs.
      resetLEDs();
      currentState = STATE_IDLE;
    }
  }
}

// *********************
// Reset all LED pins to off (active-low: HIGH means off)
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