// NANO C - Using hardware Serial on TX1 (TX) and RX0 (RX)

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN_1 9
#define SS_PIN_1 2
#define SS_PIN_2 3

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
  // Initialize hardware Serial on TX1 and RX0 (these are the Nano's default serial pins)
  Serial.begin(9600);
  SPI.begin();
  rfid1.PCD_Init();
  Serial.println("RFID1 connected");
  rfid2.PCD_Init();
  Serial.println("RFID2 connected");
}

void loop() {
  // Process RFID reader 1 (associated with C1)
  if (rfid1.PICC_IsNewCardPresent() && rfid1.PICC_ReadCardSerial()) {
    String uid = readUID(rfid1);
    uid.toLowerCase();  // Ensure the UID is in lowercase for consistent comparison

    // Check for red card UIDs
    if (uid == "53135a10" || uid == "a35abb10" || uid == "d3f74310" ||
        uid == "c3c55510" || uid == "d3325d10" || uid == "7312d927" ||
        uid == "63873029" || uid == "a3b96d29" || uid == "436d2d10") {
      Serial.println("C1_RED");
    }
    // Check for green card UIDs
    else if (uid == "43864828" || uid == "93552512" || uid == "73463010" ||
             uid == "530e5c10" || uid == "73606210" || uid == "297ac54a" ||
             uid == "b3604510" || uid == "435e4410" || uid == "73281e2a" ||
             uid == "7348ace4" || uid == "b3276010") {
      Serial.println("C1_GREEN");
    }
    else if (uid == "e3d168f7"){
      Serial.println("RESTART");
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
        uid == "63873029" || uid == "a3b96d29" || uid == "436d2d10") {
      Serial.println("C2_RED");
    }
    // Check for green card UIDs
    else if (uid == "43864828" || uid == "93552512" || uid == "73463010" ||
             uid == "530e5c10" || uid == "73606210" || uid == "297ac54a" ||
             uid == "b3604510" || uid == "435e4410" || uid == "73281e2a" ||
             uid == "7348ace4" || uid == "b3276010") {
      Serial.println("C2_GREEN");
    }
    else if (uid == "e3d168f7"){
      Serial.println("RESTART");
    }
    rfid2.PICC_HaltA();
  }
  
}
