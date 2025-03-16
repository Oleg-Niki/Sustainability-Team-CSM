// NANO E

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN_1 9
#define SS_PIN_1 2
#define SS_PIN_2 3
#define SS_PIN_3 4

MFRC522 rfid1(SS_PIN_1, RST_PIN_1);
MFRC522 rfid2(SS_PIN_2, RST_PIN_1);
MFRC522 rfid3(SS_PIN_3, RST_PIN_1);

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
  rfid1.PCD_Init();
  rfid2.PCD_Init();
  rfid3.PCD_Init();
}

void loop() {
  // Process RFID reader 1 (associated with E1)
  if (rfid1.PICC_IsNewCardPresent() && rfid1.PICC_ReadCardSerial()) {
    String uid = readUID(rfid1);
    uid.toLowerCase();  // Ensure UID is in lowercase
    if (uid == "53135a10" || uid == "a35abb10" || uid == "d3f74310" ||
        uid == "c3c55510" || uid == "d3325d10" || uid == "7312d927" ||
        uid == "63873029") {
      Serial.println("E1_RED");
    } else if (uid == "43864828" || uid == "93552512" || uid == "73463010" ||
               uid == "530e5c10" || uid == "73606210" || uid == "297ac54a" ||
               uid == "b3604510" || uid == "435e4410") {
      Serial.println("E1_GREEN");
    }
    rfid1.PICC_HaltA();
  }

  // Process RFID reader 2 (associated with E2)
  if (rfid2.PICC_IsNewCardPresent() && rfid2.PICC_ReadCardSerial()) {
    String uid = readUID(rfid2);
    uid.toLowerCase();
    if (uid == "53135a10" || uid == "a35abb10" || uid == "d3f74310" ||
        uid == "c3c55510" || uid == "d3325d10" || uid == "7312d927" ||
        uid == "63873029") {
      Serial.println("E2_RED");
    } else if (uid == "43864828" || uid == "93552512" || uid == "73463010" ||
               uid == "530e5c10" || uid == "73606210" || uid == "297ac54a" ||
               uid == "b3604510" || uid == "435e4410") {
      Serial.println("E2_GREEN");
    }
    rfid2.PICC_HaltA();
  }

  // Process RFID reader 3 (associated with F1)
  if (rfid3.PICC_IsNewCardPresent() && rfid3.PICC_ReadCardSerial()) {
    String uid = readUID(rfid3);
    uid.toLowerCase();
    if (uid == "53135a10" || uid == "a35abb10" || uid == "d3f74310" ||
        uid == "c3c55510" || uid == "d3325d10" || uid == "7312d927" ||
        uid == "63873029") {
      Serial.println("F1_RED");
    } else if (uid == "43864828" || uid == "93552512" || uid == "73463010" ||
               uid == "530e5c10" || uid == "73606210" || uid == "297ac54a" ||
               uid == "b3604510" || uid == "435e4410") {
      Serial.println("F1_GREEN");
    }
    rfid3.PICC_HaltA();
  }
}
