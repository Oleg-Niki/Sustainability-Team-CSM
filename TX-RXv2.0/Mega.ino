#define LED_RED_1 51
#define LED_GREEN_1 53
#define LED_RED_2 47
#define LED_GREEN_2 49
#define LED_RED_3 43
#define LED_GREEN_3 45

#define LED_RED_4 35
#define LED_GREEN_4 37
#define LED_RED_5 39
#define LED_GREEN_5 41
#define LED_RED_6 35
#define LED_GREEN_6 37

void setup() {
  Serial.begin(9600);  // Communication with Nano 1
  Serial1.begin(9600); // Communication with Nano 2
  
  // LED pin setup
  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_GREEN_1, OUTPUT);
  pinMode(LED_RED_2, OUTPUT);
  pinMode(LED_GREEN_2, OUTPUT);
  pinMode(LED_RED_3, OUTPUT);
  pinMode(LED_GREEN_3, OUTPUT);
  pinMode(LED_RED_4, OUTPUT);
  pinMode(LED_GREEN_4, OUTPUT);
  pinMode(LED_RED_5, OUTPUT);
  pinMode(LED_GREEN_5, OUTPUT);
  pinMode(LED_RED_6, OUTPUT);
  pinMode(LED_GREEN_6, OUTPUT);

  // Set all LEDs off initially (HIGH for active-low)
  resetLEDs();
}

void loop() {
  // Check for commands from Nano 1 (Serial)
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    handleLEDCommand(command);  // Handle the incoming command
  }
  
  // Check for commands from Nano 2 (Serial1)
  if (Serial1.available() > 0) {
    String command = Serial1.readStringUntil('\n');
    command.trim();
    handleLEDCommand(command);  // Handle the incoming command
  }

  checkGroupStatus();  // Check LED groups status for blinking logic
}

void handleLEDCommand(String command) {
  // Handle Nano 1 commands
  if (command == "1_RED") {
    digitalWrite(LED_RED_1, LOW);
    digitalWrite(LED_GREEN_1, HIGH);
  } else if (command == "1_GREEN") {
    digitalWrite(LED_RED_1, HIGH);
    digitalWrite(LED_GREEN_1, LOW);
  } else if (command == "2_RED") {
    digitalWrite(LED_RED_2, LOW);
    digitalWrite(LED_GREEN_2, HIGH);
  } else if (command == "2_GREEN") {
    digitalWrite(LED_RED_2, HIGH);
    digitalWrite(LED_GREEN_2, LOW);
  } else if (command == "3_RED") {
    digitalWrite(LED_RED_3, LOW);
    digitalWrite(LED_GREEN_3, HIGH);
  } else if (command == "3_GREEN") {
    digitalWrite(LED_RED_3, HIGH);
    digitalWrite(LED_GREEN_3, LOW);
  
  // Handle Nano 2 commands
  } else if (command == "4_RED") {
    digitalWrite(LED_RED_4, LOW);
    digitalWrite(LED_GREEN_4, HIGH);
  } else if (command == "4_GREEN") {
    digitalWrite(LED_RED_4, HIGH);
    digitalWrite(LED_GREEN_4, LOW);
  } else if (command == "5_RED") {
    digitalWrite(LED_RED_5, LOW);
    digitalWrite(LED_GREEN_5, HIGH);
  } else if (command == "5_GREEN") {
    digitalWrite(LED_RED_5, HIGH);
    digitalWrite(LED_GREEN_5, LOW);
  } else if (command == "6_RED") {
    digitalWrite(LED_RED_6, LOW);
    digitalWrite(LED_GREEN_6, HIGH);
  } else if (command == "6_GREEN") {
    digitalWrite(LED_RED_6, HIGH);
    digitalWrite(LED_GREEN_6, LOW);
  }
}

void checkGroupStatus() {
  bool group1On = (digitalRead(LED_RED_1) == LOW || digitalRead(LED_GREEN_1) == LOW);
  bool group2On = (digitalRead(LED_RED_2) == LOW || digitalRead(LED_GREEN_2) == LOW);
  bool group3On = (digitalRead(LED_RED_3) == LOW || digitalRead(LED_GREEN_3) == LOW);
  bool group4On = (digitalRead(LED_RED_4) == LOW || digitalRead(LED_GREEN_4) == LOW);
  bool group5On = (digitalRead(LED_RED_5) == LOW || digitalRead(LED_GREEN_5) == LOW);
  bool group6On = (digitalRead(LED_RED_6) == LOW || digitalRead(LED_GREEN_6) == LOW);

  if (group1On && group2On && group3On && group4On && group5On && group6On) {
    bool allGreen = (digitalRead(LED_GREEN_1) == LOW && digitalRead(LED_GREEN_2) == LOW &&
                     digitalRead(LED_GREEN_3) == LOW && digitalRead(LED_GREEN_4) == LOW &&
                     digitalRead(LED_GREEN_5) == LOW && digitalRead(LED_GREEN_6) == LOW);

    if (allGreen) {
      blinkLEDs(LED_GREEN_1, LED_GREEN_2, LED_GREEN_3, LED_GREEN_4, LED_GREEN_5, LED_GREEN_6);
    } else {
      blinkLEDs(LED_RED_1, LED_RED_2, LED_RED_3, LED_RED_4, LED_RED_5, LED_RED_6);
    }
  }
}

void blinkLEDs(int led1, int led2, int led3, int led4, int led5, int led6) {
  for (int i = 0; i < 5; i++) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    delay(500);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    delay(500);
  }
  resetLEDs();
}

void resetLEDs() {
  digitalWrite(LED_RED_1, HIGH);
  digitalWrite(LED_GREEN_1, HIGH);
  digitalWrite(LED_RED_2, HIGH);
  digitalWrite(LED_GREEN_2, HIGH);
  digitalWrite(LED_RED_3, HIGH);
  digitalWrite(LED_GREEN_3, HIGH);
  digitalWrite(LED_RED_4, HIGH);
  digitalWrite(LED_GREEN_4, HIGH);
  digitalWrite(LED_RED_5, HIGH);
  digitalWrite(LED_GREEN_5, HIGH);
  digitalWrite(LED_RED_6, HIGH);
  digitalWrite(LED_GREEN_6, HIGH);
}
