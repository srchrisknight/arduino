#include <LiquidCrystal_I2C.h>

/*****************************************
   name: I2C LCD2004
   function: You should now see your I2C LCD2004 display "Hello,world!","IIC/I2C LCD2004"
   "20 cols, 4 rows","www.sunfounder.com"
 ********************************/
//Email:service@sunfounder.com
//Website:www.sunfounder.com

/********************************/
// include the library code
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define ONE_WIRE_BUS 8

#include <OneWire.h> 
#include <DallasTemperature.h>

OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
float currentTemp = 0.0;

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
const int relayPin = 7;
const int increaseButtonPin = 4;
const int decreaseButtonPin = 2;
int increaseButtonState = 0;
int decreaseButtonState = 0;
int desiredTemp = 134;
//int currentTemp = 134;
String desiredLine;
String currentLine;
long timeStamp = millis();
/*********************************************************/
void setup()
{
  Serial.begin(9600); 
  sensors.begin();
  
  pinMode(relayPin, OUTPUT);
  pinMode(decreaseButtonPin, INPUT);
  pinMode(increaseButtonPin, INPUT);

  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight


  lcd.setCursor ( 0, 0 );            // go to the top left corner
  lcd.print("Current: 134*:"); // write this string on the top row
  lcd.setCursor ( 0, 1 );            // go to the 2nd row
  lcd.print("Desired: 134*"); // pad string with spaces for centering
  //  lcd.setCursor ( 0, 2 );            // go to the third row
  //  lcd.print(""); // pad with spaces for centering
  //  lcd.setCursor ( 0, 3 );            // go to the fourth row
  //  lcd.print("             Running");
}
/*********************************************************/
void updateDesiredTemp(int incriment) {
  desiredTemp += incriment;
  lcd.setCursor ( 0, 1 );
  lcd.print(String("Desired: ") + String(desiredTemp) + "*     ");
  delay(200);
}

void updateCurrentTemp(){
 lcd.setCursor(0,0);
 lcd.print("Current: " + String(int(currentTemp)) +"*     "); 
}

void loop()
{
  
 if (abs(millis() - timeStamp) > 5000) {  
   sensors.requestTemperatures(); 
   currentTemp = sensors.getTempCByIndex(0) * 1.8 + 32;
   Serial.println(currentTemp); 
  
   if (currentTemp < desiredTemp) {
     lcd.setCursor ( 0, 3 );
     lcd.print ("             Running");
     digitalWrite(relayPin, HIGH);
   } else {
     lcd.setCursor ( 0, 3 );
     lcd.print ("         Not Running");
     digitalWrite(relayPin, LOW);
   }

  updateCurrentTemp();
  timeStamp = millis();
 }

  //increasebutton click
  increaseButtonState = digitalRead(increaseButtonPin);
  if (increaseButtonState == HIGH) {
    updateDesiredTemp(1);
  }

  //decreasebutton click
  decreaseButtonState = digitalRead(decreaseButtonPin);
  if (decreaseButtonState == HIGH) {
    updateDesiredTemp(-1);
  }

}
/************************************************************/

/************************************************************/
