


byte userPICC[4] = {46, 29, 154, 48};

/*
 * Control del Uid con el de usuarios
 */
boolean compareUid() {
  for (byte i = 0; i < 4; i++)
    if (nuidPICC[i] != userPICC[i])
      return false;
  return true;
}


/*
 * Control del Uid con el almacenado en nuidPICC
 */
boolean isEqualUid(MFRC522::Uid buffer) {
  for (byte i = 0; i < 4; i++)
    if (buffer.uidByte[i] != nuidPICC[i])
      return false;
  return true;
}


/*
 * Gurdamos Uid leido en nuidPICC
 */
void storeUid(MFRC522::Uid buffer) {
  for (byte i = 0; i < 4; i++)
    nuidPICC[i] = buffer.uidByte[i];
}

/*
 * Tipo de tarjeta
 */
boolean checkTypeMifare() {
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K)
    return false;

  return true;
}

/*
 * Información de la tarjeta
 */
void showCardInfo(MFRC522::Uid buffer) {
  Serial.println(F("The NUID tag is:"));
  Serial.print(F("In hex: "));
  printHex(buffer.uidByte, buffer.size);
  Serial.println();
  Serial.print(F("In dec: "));
  printDec(buffer.uidByte, buffer.size);
  Serial.println();
}

/*
 * Información del tipo de tarjeta
 */
void showMifareType() {
  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));
}


/*
 * Vuelca un byte array como hex al puerto de serie
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/*
 * Vuelca un byte array como dec al puerto de serie
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}

