#define _LCD_TYPE 1
#include <LCD_1602_RUS_ALL.h>

//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
//#include <WString.h>

const unsigned int MAX_MESSAGE_LENGTH = 17;
const unsigned int DELAY_SERIAL_MS = 100;


LCD_1602_RUS lcd(0x27,MAX_MESSAGE_LENGTH,2);

void display_print(String str1,String str2){
  lcd.clear();
  lcd.setCursor(0,0); // set cursor to 1 symbol of 1 line
  lcd.print(str1);

  lcd.setCursor(0,1); // set cursor to 1 symbol of 2 line
  lcd.print(str2); 
}

void setup() 
{
  String up_str = "Канал:";
  String down_str = "НЕВIДОМИЙ";
  lcd.init();
  lcd.backlight();

  display_print(up_str,down_str);

  Serial.begin(9600);
}

void loop() {
 //Check to see if anything is available in the serial receive buffer
 while (Serial.available() > 0)
 {
   //Create a place to hold the incoming message
   static char message[MAX_MESSAGE_LENGTH];
   static unsigned int message_pos = 0;

   //Read the next available byte in the serial receive buffer
   char inByte = Serial.read();

   //Message coming in (check not terminating character) and guard for over message size
   if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
   {
     //Add the incoming byte to our message
     message[message_pos] = inByte;
     message_pos++;
   }
   //Full message received...
   else
   {
     //Add null character to string
     message[message_pos] = '\0';

     //Print the message (or do other things)     
     display_print("Канал:",message);
     delay(DELAY_SERIAL_MS);
     Serial.println(message);

     //Reset for the next message
     message_pos = 0;
   }
 }
}
