/* made by electronicchannel */
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
// You may need to change the address to 0x3F if 0x27 doesn't work
LiquidCrystal_I2C lcd(0x27, 16, 2);
String rfid = "";
bool id1 = false;
bool id2 = false;
bool id3 = false;
int successRead;

#define SDA_DIO 10
#define RESET_DIO 9

MFRC522 mfrc522(SDA_DIO, RESET_DIO); 

void setup()
{ 
  Serial.begin(9600);
  SPI.begin(); 
  lcd.init();
  mfrc522.PCD_Init();
  Serial.println("RFID CARD SETUP");
}

void loop()
{
  do{
    successRead = getID();
  }
  while (!successRead);
  if (rfid == "81 65 3D 2E")
  {
    id1 = !id1;
    if(id1 == true)
    {
      Serial.println("name");
      lcd.print("name");
      lcd.setCursor(0,1);
    }
    else if(id1 == false)
    {
      Serial.println("name");
      lcd.print("name");
      lcd.setCursor(0,1);
    }
    
  }
  if (rfid == "26 D7 53 73")
  {
    id2 = !id2;
   if(id2 == true)
    {
      Serial.println("Sarthak");
      lcd.print("Sarthak");
      lcd.setCursor(0,1);
    }
    else if(id2 == false)
    {
      Serial.println("Sarthak");
      lcd.print("Sarthak");
      lcd.setCursor(0,1);
    } 
  }  
    
    if (rfid == "04 82 3D 92 70 52 80")
  {
    id3 = !id3;
   if(id3 == true)
    {
      Serial.println("Arsh");
      lcd.print("Arsh");
      lcd.setCursor(0,1);
    }
    else if(id3 == false)
    {
      Serial.println("Arsh");
      lcd.print("Arsh");
      lcd.setCursor(0,1);
    } 
  }  
  rfid = "";
  delay(4000);
  lcd.clear();
  
}


int getID() {
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) { 
    return 0;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return 0;
  }
  

  for (int i = 0; i < mfrc522.uid.size; i++) 
  {
    rfid += mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ";
    rfid += String(mfrc522.uid.uidByte[i], HEX); 
  }
  rfid.trim();
  rfid.toUpperCase();
  
  mfrc522.PICC_HaltA();
  return 1;
}
/* made by electronicchannel */