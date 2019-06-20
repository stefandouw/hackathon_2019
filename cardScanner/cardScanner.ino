#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#include <FreeDefaultFonts.h>
#include <MCUFRIEND_kbv.h>
#include <TFT_HX8357GLUE.h>
#include <UTFTGLUE.h>

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

String currentCard = "";
String roomName = "GW302";
String state = "This room is available to book";
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
MCUFRIEND_kbv tft;
uint16_t ID;

void setup() {
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
  
  tft.reset();
  ID = tft.readID();
  tft.begin();
  tft.fillScreen(0xffff);
  tft.setTextColor(0x0000);
  tft.setTextSize(2);
  tft.setRotation(3);
}

void renderScreen(){
  tft.fillScreen(0xffff);
  tft.setCursor(0,0);
  tft.println(state);
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
//  Serial.println("Debug: card number: " + card);
  return card;
}

void loop() {
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if (!mfrc522.PICC_IsNewCardPresent()) {
		return;
	} else {
	  if (currentCard == ""){
	    currentCard = getCurrentCardNumber();
      state = roomName + " is now booked by: " + getName(currentCard);
      renderScreen();
      delay(2000);
  	} else if (currentCard != getCurrentCardNumber()){
      state = "Sorry " + getName(getCurrentCardNumber()) + ", " + roomName + " is already booked by: " + getName(currentCard);
      renderScreen();
      delay(2000);
  	} else if (currentCard == getCurrentCardNumber()){
      state = roomName + " is now no longer booked by: " + getName(currentCard);
      renderScreen();
      currentCard = "";
      delay(2000);
  	}
	}
}
