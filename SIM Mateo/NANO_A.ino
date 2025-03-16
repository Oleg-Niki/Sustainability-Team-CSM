// NANO A

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN_1 9
#define SS_PIN_1 2
#define SS_PIN_2 3
#define NR_OF_READERS 2

// Array of chip select pins.
uint8_t ssPins[] = {SS_PIN_1, SS_PIN_2};

// Create two RFID reader objects.
MFRC522 rfid1(SS_PIN_1, RST_PIN_1);
MFRC522 rfid2(SS_PIN_2, RST_PIN_1);

String readUID(MFRC522 &rfid) {
  String uidString = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uidString += String(rfid.uid.uidByte[i], HEX);
  }
  return uidString;
}

void setup() {
  Serial.begin(9600);
  SPI.begin();
  
  // Set chip select pins as outputs and deselect both readers.
  pinMode(SS_PIN_1, OUTPUT);
  pinMode(SS_PIN_2, OUTPUT);
  digitalWrite(SS_PIN_1, HIGH);
  digitalWrite(SS_PIN_2, HIGH);

  // Initialize RFID modules.
  rfid1.PCD_Init();
  Serial.println("RFID1 connected");
  rfid2.PCD_Init();
  Serial.println("RFID2 connected");
}

void loop() {
  // Process each RFID reader using the same SPI bus.
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    // Deselect all readers.
    for (uint8_t i = 0; i < NR_OF_READERS; i++) {
      digitalWrite(ssPins[i], HIGH);
    }
    // Activate the current reader.
    digitalWrite(ssPins[reader], LOW);
    delay(5); // Allow chip select to settle

    // Process the active reader.
    if (reader == 0) {
      // Process RFID reader 1 (A1)
      if (rfid1.PICC_IsNewCardPresent() && rfid1.PICC_ReadCardSerial()) {
        String uid = readUID(rfid1);
        uid.toLowerCase();  // Convert UID to lowercase for consistency

        // Check for red card UIDs:
        if (uid == "53135a10" || uid == "a35abb10" || uid == "d3f74310" ||
            uid == "c3c55510" || uid == "d3325d10" || uid == "7312d927" ||
            uid == "63873029") {
          Serial.println("A1_RED");
        }
        // Check for green card UIDs:
        else if (uid == "43864828" || uid == "93552512" || uid == "73463010" ||
                 uid == "530e5c10" || uid == "73606210" || uid == "297ac54a" ||
                 uid == "b3604510" || uid == "435e4410") {
          Serial.println("A1_GREEN");
        }
        rfid1.PICC_HaltA();
      }
    } else if (reader == 1) {
      // Process RFID reader 2 (A2)
      if (rfid2.PICC_IsNewCardPresent() && rfid2.PICC_ReadCardSerial()) {
        String uid = readUID(rfid2);
        uid.toLowerCase();  // Convert UID to lowercase for consistency

        // Check for red card UIDs:
        if (uid == "53135a10" || uid == "a35abb10" || uid == "d3f74310" ||
            uid == "c3c55510" || uid == "d3325d10" || uid == "7312d927" ||
            uid == "63873029") {
          Serial.println("A2_RED");
        }
        // Check for green card UIDs:
        else if (uid == "43864828" || uid == "93552512" || uid == "73463010" ||
                 uid == "530e5c10" || uid == "73606210" || uid == "297ac54a" ||
                 uid == "b3604510" || uid == "435e4410") {
          Serial.println("A2_GREEN");
        }
        rfid2.PICC_HaltA();
      }
    }
    // Deactivate the current reader.
    digitalWrite(ssPins[reader], HIGH);
  }
}
