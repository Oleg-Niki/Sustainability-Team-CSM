
//RELAYS ON BOARD A and C
#define RELAY_A_R1 46 //Let's pretend it is Board A and name for relay = RELAY_A_R1 where A-name of the board and R1-Red LED number 1
#define RELAY_A_G1 48 //Let's pretend it is Board A and name for relay = RELAY_A_G1 where A-name of the board and G1-Green LED number 1
#define RELAY_A_R2 50
#define RELAY_A_G2 52
#define RELAY_C_G1 47
#define RELAY_C_R1 49
#define RELAY_C_G2 51
#define RELAY_C_R2 53


//RELAYS ON BOARD D
#define RELAY_D_R1 45
#define RELAY_D_G1 43
#define RELAY_D_G2 41
#define RELAY_D_R2 39


//INPUT PINS
#define RFID1_D_G 2 //RFID1_D_G means that rfid reader number 1 is located on board D and it manages green LED
#define RFID1_D_R 3 //RFID1_D_R means that rfid reader number 1 is located on board D and it manages red LED
#define RFID2_D_G 4
#define RFID2_D_R 5
#define RFID3_D_G 6
#define RFID3_D_R 7

#define RFID1_A_G 8
#define RFID1_A_R 9
#define RFID2_A_G 10
#define RFID2_A_R 11
#define RFID1_C_G 12
#define RFID1_C_R 13
#define RFID2_C_G 22
#define RFID2_C_R 24




void setup() 
{
  //start serial connection
  Serial.begin(9600);
  //configure pins as an input and enable the internal pull-up resistor
  
// INPUT PINS FOR BOARD D
  pinMode(RFID1_D_G, INPUT_PULLUP);
  pinMode(RFID1_D_R, INPUT_PULLUP);
  pinMode(RFID2_D_G, INPUT_PULLUP);
  pinMode(RFID2_D_R, INPUT_PULLUP);
  pinMode(RFID3_D_G, INPUT_PULLUP);
  pinMode(RFID3_D_R, INPUT_PULLUP);
// INPUT PINS FOR BOARD A and C
  pinMode(RFID1_A_G, INPUT_PULLUP);
  pinMode(RFID1_A_R, INPUT_PULLUP);
  pinMode(RFID2_A_G, INPUT_PULLUP);
  pinMode(RFID2_A_G, INPUT_PULLUP);
  pinMode(RFID1_C_G, INPUT_PULLUP);
  pinMode(RFID1_C_G, INPUT_PULLUP);
  pinMode(RFID2_C_G, INPUT_PULLUP);
  pinMode(RFID2_C_G, INPUT_PULLUP);

//OUTPINS FOR BOARD D
  pinMode(RELAY_D_G1, OUTPUT);
  pinMode(RELAY_D_R1, OUTPUT);
  pinMode(RELAY_D_G2, OUTPUT);
  pinMode(RELAY_D_R2, OUTPUT);
//OUTPINS FOR BOARD A and C
  pinMode(RELAY_A_R1, OUTPUT);
  pinMode(RELAY_A_G1, OUTPUT);
  pinMode(RELAY_A_R2, OUTPUT);
  pinMode(RELAY_A_G2, OUTPUT);
  pinMode(RELAY_C_G1, OUTPUT);
  pinMode(RELAY_C_R1, OUTPUT);
  pinMode(RELAY_C_G2, OUTPUT);
  pinMode(RELAY_C_R2, OUTPUT);

 //--------TEST ALL RELAYS/LEDs ON-OFF--------
  digitalWrite(RELAY_A_R1, HIGH);
  delay(200);
  digitalWrite(RELAY_A_G1, HIGH);
  delay(600);
  digitalWrite(RELAY_A_R1, LOW);
  delay(200);
  digitalWrite(RELAY_A_G1, LOW);
  delay(200);
  digitalWrite(RELAY_A_R2, HIGH);
  delay(200);
  digitalWrite(RELAY_A_G2, HIGH);
  delay(200);
  digitalWrite(RELAY_A_R2, LOW);
  delay(200);
  digitalWrite(RELAY_A_G2, LOW);
  delay(500);


 
  digitalWrite(RELAY_D_G2, HIGH);
  delay(200);
  digitalWrite(RELAY_D_R2, HIGH);
  delay(200);
  digitalWrite(RELAY_C_G1, HIGH);
  delay(200);
  digitalWrite(RELAY_C_R1, HIGH);
  delay(200);
  digitalWrite(RELAY_C_G2, HIGH);
  delay(200);
  digitalWrite(RELAY_C_R2, HIGH);
  delay(200);
  digitalWrite(RELAY_D_G1, HIGH);
  delay(200);
  digitalWrite(RELAY_D_R1, HIGH);

  // digitalWrite(4, LOW);
  // digitalWrite(5, LOW);
  // digitalWrite(6, HIGH);
  // digitalWrite(7, HIGH);
  // digitalWrite(8, HIGH);
  // digitalWrite(9, HIGH);

}

void loop() {

int RFID1_A_R_status = digitalRead(RFID1_A_R);
int RFID1_A_G_status = digitalRead(RFID1_A_G);
int RFID2_A_R_status = digitalRead(RFID2_A_G);
int RFID2_A_G_status = digitalRead(RFID2_A_R);
int RFID1_C_G_status = digitalRead(RFID1_C_G);
int RFID1_C_R_status = digitalRead(RFID1_C_R);
int RFID2_C_G_status = digitalRead(RFID2_C_G);
int RFID2_C_R_status = digitalRead(RFID2_C_R);

int RFID1_D_G_status = digitalRead(RFID1_D_G);
int RFID1_D_R_status = digitalRead(RFID1_D_R);
int RFID2_D_G_status = digitalRead(RFID2_D_G);
int RFID2_D_R_status = digitalRead(RFID2_D_R);
int RFID3_D_G_status = digitalRead(RFID3_D_G);
int RFID3_D_R_status = digitalRead(RFID3_D_R);


  //-------------------------------RED ON RFID 1 BOARD A and C
  if (RFID1_A_G_status == HIGH)
  {
    Serial.print("RFID1_R pin 8: ");
    Serial.println(RFID1_A_R);
    digitalWrite(RELAY_A_R1, HIGH);
  }
   else if (RFID1_A_G_status == LOW)
  {
        digitalWrite(RELAY_A_R1, LOW); 
  } 
  //------------------------------GREEN on RFID 1 BOARD A and C
  if (RFID1_A_R_status == HIGH)
  {
    Serial.print("RFID_A_1 pin 9: ");
    Serial.println(RFID1_A_R);
    digitalWrite(RELAY_A_G1, HIGH);
  }
  else if (RFID1_A_R_status == LOW)
  {
    digitalWrite(RELAY_A_G1, LOW); 
  } 


  //-------------------------------RED ON RFID 2 BOARD A and C
  if (RFID2_A_R_status == HIGH)
  {
    Serial.print("RFID2_R pin 10: ");
    Serial.println(RFID2_A_R);
    digitalWrite(RELAY_A_R2, HIGH);
  }
   else if (RFID2_A_R_status == LOW)
  {
    digitalWrite(RELAY_A_R2, LOW); 
  } 
   //------------------------------GREEN on RFID 3 (RFID1_C_G) BOARD A and C
  if (RFID1_C_G_status == HIGH)
  {
    Serial.print("RFID1_C_G_status");
    Serial.println(RFID1_C_G);
    digitalWrite(RELAY_C_G1, LOW);
  }
  else if (RFID1_C_G_status == LOW)
  {
    digitalWrite(RELAY_C_G1, HIGH); 
  } 

//-------------------------------RED ON RFID 3 (RFID1_C_R) BOARD A and C
  if (RFID1_A_R_status == HIGH)
  {
    Serial.print("RFID1_A_R_status");
    Serial.println(RFID1_A_R_status);
    digitalWrite(RELAY_C_R1, LOW);
  }
   else if (RFID1_A_R_status == LOW)
  {
        digitalWrite(RELAY_C_R1, HIGH); 
  } 

  
   //-------------------------------RED ON RFID 3 BOARD D
  if (RFID3_D_G_status == HIGH)
  {
    Serial.print("RFID3_D_G_status: ");
    Serial.println(RFID3_D_G_status);
    digitalWrite(RELAY_D_R2, LOW);
  }
   else if (RFID3_D_G_status == LOW)
  {
    digitalWrite(RELAY_D_R2, HIGH); 
  } 
  
   //-------------------------------GREEN ON RFID 1 BOARD D
  if (RFID3_D_R_status == HIGH)
  {
    Serial.print("RFID3_D_R_status: ");
    Serial.println(RFID3_D_R_status);
    digitalWrite(RELAY_D_G2, LOW);
  }
   else if (RFID3_D_G_status == LOW)
  {
    digitalWrite(RELAY_D_G2, HIGH); 
  } 
  //-------------------------------RED ON RFID 1 BOARD D
 if (RFID1_D_G_status == HIGH)
 {
  Serial.print("RFID1_D_G_status: ");
    Serial.println(RFID1_D_G_status);
    digitalWrite(RELAY_D_G1, LOW);
 }
  else if (RFID1_D_G_status == LOW)
  {
    digitalWrite(RELAY_D_G1, HIGH); 
  } 
  //-------------------------------GREEN ON RFID 1 BOARD D
  if (RFID1_D_R_status == HIGH)
 {
  Serial.print("RFID1_D_R_status: ");
    Serial.println(RFID1_D_R_status);
    digitalWrite(RELAY_D_R1, LOW);
 }
  else if (RFID1_D_R_status == LOW)
  {
    digitalWrite(RELAY_D_R1, HIGH); 
  }   

}
