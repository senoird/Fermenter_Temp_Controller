#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4);
#define ONE_WIRE_BUS 11
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int rb = 8; //Right Button
const int mb = 9; //Middle Button
const int lb = 10; //Left Button
int rbs = 0; // Right Button Count
int mbs = 0; // Middle Buton Count
int lbs = 0; // Left Button Count
const int r1 =  6; // Relay 1 Pump
const int r2 =  7; // Relay 2 for future use
int bt = 0; // Wort Temp
int sp = 80;  // Setpoint
bool c3 = false; // Pump Status
String ps =  "Off"; //Pump Status Variable for On/Off Text

void setup()
{
	sensors.begin();
	lcd.begin();
	lcd.backlight();
	lcd.setCursor(0,0);
  lcd.print("Setpoint: ");
  lcd.setCursor(15,0);
  lcd.print(sp);
  lcd.setCursor(0,1);
  lcd.print("Wort Temp: ");
  lcd.setCursor(15,1);
  lcd.print(bt);
  lcd.setCursor(0,2);
  lcd.print("Pump: ");
  lcd.setCursor(15,2);
  lcd.print(ps);
  lcd.setCursor(0,3);
  lcd.print("RButton + LButton -");
  pinMode(rb, INPUT_PULLUP);
  pinMode(mb, INPUT_PULLUP);
  pinMode(lb, INPUT_PULLUP);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
}

void loop()
{
  //Read Temp and Display Wort Temp
  sensors.requestTemperatures(); 
  bt = sensors.getTempFByIndex(0);
  lcd.setCursor(15,1);
  lcd.print(bt);
  
  //Read Buttons and Change Setpoint if Pushed
  rbs = digitalRead(rb);
  if (rbs == LOW) {
    delay(250);
    sp++;
    lcd.setCursor(15,0);
    lcd.print(sp);
  } 
  /*mbs = digitalRead(mb);
  if (mbs == LOW) {
    delay(500);
    c3 = !c3;
    if (c3 == 0){
      ps = "Off";
    }
    else if (c3 == 1){
      ps = "On ";
    }
    lcd.setCursor(15,2);
    lcd.print(ps);
  }
  */
  lbs = digitalRead(lb);
  if (lbs == LOW) {
    delay(250);
    sp--;
    lcd.setCursor(15,0);
    lcd.print(sp);
  }
  
  //Bring On or Shut Off Pump On Temp
  if (bt > (sp+1)){
    digitalWrite(r1,LOW);
    lcd.setCursor(15,2);
    lcd.print("On ");
  }
  else if (bt < (sp-1)){
    digitalWrite(r1,HIGH);
    lcd.setCursor(15,2);
    lcd.print("Off");    
  }

  
}
