/*
   ----------------------------------------------------------------------------------------------
   Ejemplo de lectura basado en la librería MFRC522. Ver https://github.com/miguelbalboa/rfid
   ----------------------------------------------------------------------------------------------

   Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

// Init array that will store new NUID
byte nuidPICC[4];




void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));

  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
  Serial.println(F(" Start."));

}

void loop() {

  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;
  
  showMifareType();

  if (!checkTypeMifare()) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;    
  }

  if ( isEqualUid(rfid.uid) ) {
    Serial.println(F("Card read previously."));
  } else {
    Serial.println(F("A new card has been detected."));
    storeUid(rfid.uid);
    showCardInfo(rfid.uid);

    if (compareUid()) {
      Serial.println(F("Welcome user"));
    }
  }
  
  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}



