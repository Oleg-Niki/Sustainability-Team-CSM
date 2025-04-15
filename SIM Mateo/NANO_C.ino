// NANO C - Using hardware Serial on TX1 (TX) and RX0 (RX)

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN_1 9
#define SS_PIN_1 2
#define SS_PIN_2 3
#define SS_PIN_3 4
#define SS_PIN_4 5

MFRC522 rfid1(SS_PIN_1, RST_PIN_1);
MFRC522 rfid2(SS_PIN_2, RST_PIN_1);
MFRC522 rfid3(SS_PIN_3, RST_PIN_1);
MFRC522 rfid4(SS_PIN_4, RST_PIN_1);

String readUID(MFRC522 &rfid) {
  String uidString = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uidString += String(rfid.uid.uidByte[i], HEX);
  }
  return uidString;
}

void setup() {
  // Initialize hardware Serial on TX1 and RX0 (these are the Nano's default serial pins)
  Serial.begin(9600);
  SPI.begin();
  rfid1.PCD_Init();
  rfid2.PCD_Init();
  rfid3.PCD_Init();
  rfid4.PCD_Init();
}

void loop() {
  // Process RFID reader 1 (associated with C1)
  if (rfid1.PICC_IsNewCardPresent() && rfid1.PICC_ReadCardSerial()) {
    String uid = readUID(rfid1);
    uid.toLowerCase();  // Ensure the UID is in lowercase for consistent comparison

    // Check for red card UIDs
    if (uid == "53135a10" || uid == "a35abb10" || uid == "d3f74310" ||
        uid == "c3c55510" || uid == "d3325d10" || uid == "7312d927" ||
        uid == "63873029") {
      Serial.println("C1_RED");
    }
    // Check for green card UIDs
    else if (uid == "43864828" || uid == "93552512" || uid == "73463010" ||
             uid == "530e5c10" || uid == "73606210" || uid == "297ac54a" ||
             uid == "b3604510" || uid == "435e4410") {
      Serial.println("C1_GREEN");
    }
    rfid1.PICC_HaltA();
  }

  // Process RFID reader 2 (associated with C2)
  if (rfid2.PICC_IsNewCardPresent() && rfid2.PICC_ReadCardSerial()) {
    String uid = readUID(rfid2);
    uid.toLowerCase();  // Ensure the UID is in lowercase for consistent comparison

    // Check for red card UIDs
    if (uid == "53135a10" || uid == "a35abb10" || uid == "d3f74310" ||
        uid == "c3c55510" || uid == "d3325d10" || uid == "7312d927" ||
        uid == "63873029") {
      Serial.println("C2_RED");
    }
    // Check for green card UIDs
    else if (uid == "43864828" || uid == "93552512" || uid == "73463010" ||
             uid == "530e5c10" || uid == "73606210" || uid == "297ac54a" ||
             uid == "b3604510" || uid == "435e4410") {
      Serial.println("C2_GREEN");
    }
    rfid2.PICC_HaltA();
  }
  // Process RFID reader 3 (associated with A1)
  if (rfid3.PICC_IsNewCardPresent() && rfid3.PICC_ReadCardSerial()) {
    String uid = readUID(rfid3);
    uid.toLowerCase();  // Ensure the UID is in lowercase for consistent comparison

    // Check for red card UIDs
    if (uid == "53135a10" || uid == "a35abb10" || uid == "d3f74310" ||
        uid == "c3c55510" || uid == "d3325d10" || uid == "7312d927" ||
        uid == "63873029") {
      Serial.println("A1_RED");
    }
    // Check for green card UIDs
    else if (uid == "43864828" || uid == "93552512" || uid == "73463010" ||
             uid == "530e5c10" || uid == "73606210" || uid == "297ac54a" ||
             uid == "b3604510" || uid == "435e4410") {
      Serial.println("A1_GREEN");
    }
    rfid3.PICC_HaltA();
  }
  // Process RFID reader 4 (associated with A2)
  if (rfid4.PICC_IsNewCardPresent() && rfid4.PICC_ReadCardSerial()) {
    String uid = readUID(rfid4);
    uid.toLowerCase();  // Ensure the UID is in lowercase for consistent comparison

    // Check for red card UIDs
    if (uid == "53135a10" || uid == "a35abb10" || uid == "d3f74310" ||
        uid == "c3c55510" || uid == "d3325d10" || uid == "7312d927" ||
        uid == "63873029") {
      Serial.println("A2_RED");
    }
    // Check for green card UIDs
    else if (uid == "43864828" || uid == "93552512" || uid == "73463010" ||
             uid == "530e5c10" || uid == "73606210" || uid == "297ac54a" ||
             uid == "b3604510" || uid == "435e4410") {
      Serial.println("A2_GREEN");
    }
    rfid4.PICC_HaltA();
  }
}
