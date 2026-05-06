/**
 * Scanner 1-Wire (Dallas) pour cartes Arduino et compatible.
 */

/* Dépendances */
#include <OneWire.h>

/** Broche pour le bus 1-Wire */
const byte ONEWIRE_BUS_PIN = 7;

/** L'object OneWire pour communiquer via le protocole 1-Wire sur la broche spécifiée */
OneWire ds(ONEWIRE_BUS_PIN);

/** Fonction setup() */
void setup(void) {
  
  /* Initialise le port série */
  Serial.begin(115200);
  Serial.println(F("~~ Scanner 1-Wire ~~"));
}

/** Fonction loop() */
void loop(void) {
  byte address[8];
  
  /* Cherche un module 1-Wire sur le bus */
  if (!ds.search(address)) {
    Serial.println(F("End of Scan."));
    ds.reset_search();
    for(;;);
  }
  
  /* Module 1-Wire découvert ! */
  Serial.print(F("Found "));
  for(byte i = 0; i < 8; ++i) {
    if (address[i] < 0x10) Serial.write('0');
    Serial.print(address[i], HEX);
    Serial.write(' ');
  }

  /* Vérifie si l'adresse est valide */
  if (OneWire::crc8(address, 7) != address[7]) {
      Serial.print(F("(CRC invalid)"));
      
  }
  
  
  /* Fin de ligne */
  Serial.println();

 
}
