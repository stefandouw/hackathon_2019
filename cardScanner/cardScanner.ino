#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

String currentCard = "";
String roomName = "GW302";
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

String getName(String cardNumber){
  if (cardNumber == "67134201254"){
    return "Stefan";
  } else if (cardNumber == "179220191254"){
    return "Daan";
  } else {
    return "Unregistered user";
  }
}

String getCurrentCardNumber(){
  String card;
  mfrc522.PICC_ReadCardSerial();
  for (int i = 0; i < mfrc522.uid.size; i++){
    card += mfrc522.uid.uidByte[i];
  }
  return card;
}

void loop() {
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if (!mfrc522.PICC_IsNewCardPresent()) {
		return;
	} else {
	  if (currentCard == ""){
	    currentCard = getCurrentCardNumber();
      Serial.println(roomName + " is now booked by: " + getName(currentCard));
      Serial.println("------------------------------------------");
      delay(2000);
  	} else if (currentCard != getCurrentCardNumber()){
      Serial.println("Sorry " + getName(getCurrentCardNumber()) + ", " + roomName + " is already booked by: " + getName(currentCard));
      Serial.println("------------------------------------------");
      delay(2000);
  	} else if (currentCard == getCurrentCardNumber()){
      Serial.println(roomName + " is now no longer booked by: " + getName(currentCard));
      Serial.println("------------------------------------------");
      currentCard = "";
      delay(2000);
  	}
	}
}
