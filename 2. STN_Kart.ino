

#include <OneWire.h>



/* Broche du bus 1-Wire */
const byte BROCHE_ONEWIRE = 7;
OneWire ds(BROCHE_ONEWIRE);

/* Adresses des capteurs de température */
const byte SENSOR_ADDRESS_1[] = { 0x28, 0x0c, 0x81, 0x77, 0x91, 0x0C, 0x02, 0x39 };
const byte SENSOR_ADDRESS_2[] = { 0x28, 0xB1, 0xE3, 0x77, 0x91, 0x12, 0x02, 0xD6 };
const byte SENSOR_ADDRESS_3[] = { 0x28, 0xFF, 0x51, 0x0D, 0xB0, 0x17, 0x05, 0x8C };
const byte SENSOR_ADDRESS_4[] = { 0x28, 0x9F, 0x31, 0x46, 0x92, 0x12, 0x02, 0x8D };
const byte SENSOR_ADDRESS_5[] = { 0x28, 0x69, 0x0E, 0x46, 0x92, 0x11, 0x02, 0xF3 };
const byte SENSOR_ADDRESS_6[] = { 0x28, 0x4D, 0xBC, 0x77, 0x91, 0x16, 0x02, 0x18 };
const byte SENSOR_ADDRESS_7[] = { 0x28, 0x3D, 0xA2, 0x46, 0x92, 0x12, 0x02, 0x46 };
const byte SENSOR_ADDRESS_8[] = { 0x28, 0x04, 0xE2, 0x67, 0x33, 0x14, 0x01, 0x3E };
const byte SENSOR_ADDRESS_9[] = { 0x28, 0xE2, 0xFA, 0x77, 0x91, 0x12, 0x02, 0x2E };

int i = 0;
/**
 * Fonction de lecture de la température via un capteur DS18B20.
 */
float getTemperature(const byte addr[]) {
  byte data[9];
  // data[] : Données lues depuis le scratchpad
  // addr[] : Adresse du module 1-Wire détecté
  
  /* Reset le bus 1-Wire et sélectionne le capteur */
  ds.reset();
  ds.select(addr);
  
  /* Lance une prise de mesure de température et attend la fin de la mesure */
  ds.write(0x44, 1);
  delay(800);
  
  /* Reset le bus 1-Wire, sélectionne le capteur et envoie une demande de lecture du scratchpad */
  ds.reset();
  ds.select(addr);
  ds.write(0xBE);
 
 /* Lecture du scratchpad */
  for (byte i = 0; i < 9; i++) {
    data[i] = ds.read();
  }
   
  /* Calcul de la température en degré Celsius */
  return (int16_t) ((data[1] << 8) | data[0]) * 0.0625; 
}
 


void setup() {
  // put your setup code here, to run once:
    
  Serial.begin(9600);

    Serial.println("CLEARSHEET");
    Serial.println("LABEL,Date,Time,Timer,Counter,millis,Temp1,Temp2,Temp3,Temp4,Temp5,Temp6,Temp7,Temp8,Temp9");

}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  
  float tension1 = getTemperature(SENSOR_ADDRESS_1);
  float tension2 = getTemperature(SENSOR_ADDRESS_2);
  float tension3 = getTemperature(SENSOR_ADDRESS_3);
  float tension4 = getTemperature(SENSOR_ADDRESS_4);
  float tension5 = getTemperature(SENSOR_ADDRESS_5);
  float tension6 = getTemperature(SENSOR_ADDRESS_6);
  float tension7 = getTemperature(SENSOR_ADDRESS_7);
  float tension8 = getTemperature(SENSOR_ADDRESS_8);
  float tension9 = getTemperature(SENSOR_ADDRESS_9);

  
  
  

 Serial.println( (String) "DATA,DATE,TIME,TIMER," + i++ + "," + millis() + "," + tension1 + "," + tension2 + "," + tension3 + "," + tension4 + "," + tension5 + "," + tension6 + ","  + tension7 + ","+ tension8 + "," + tension9 + "," + ",AUTOSCROLL_20" );
   

  delay(5000);

 }
