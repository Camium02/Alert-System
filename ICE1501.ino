#include "IRremote.h"
#include<LiquidCrystal.h>    //Include these 2 Libraries

/* Set up OUTPUT pins */
const int rs=12, en=11, d4=5, d5=4, d6=3, d7=2;  //Pins for the LCD
LiquidCrystal lcd(rs,en,d4,d5,d6,d7); 
int receiver = 13; // Signal Pin of IR receiver to Arduino Digital Pin 13
int speakerPin = 10; //Pin for the Passive Buzzer

/* Declare objects */
IRrecv irrecv(receiver);     // Create instance of 'irrecv'
decode_results results;      // Create instance of 'decode_results'

/* Set up for Buzzer */
char note= 'c';
int tempo = 300;

void playTone(int tone, int duration){
	for (long i = 0; i < duration * 1000L; i += tone * 2){
	digitalWrite(speakerPin, HIGH);
	delayMicroseconds(tone);
	digitalWrite(speakerPin, LOW);
	delayMicroseconds(tone);
  }
}


/* Function */
void translateIR() // Takes action based on IR code received

// Describing Remote IR codes 

{

  switch(results.value)

  {
  case 0xFFA25D: lcd.begin(16,2); lcd.print("Alert System"); break;
  case 0xFFE21D: lcd.print("I've Fallen"); playTone (note, 10 * tempo); break;
  case 0xFF629D: lcd.print("Happy :)"); break;
  case 0xFF22DD: lcd.print("Hello");  break;
  case 0xFF02FD: lcd.print("Good Bye");    break;
  case 0xFFC23D: lcd.print("Hungry");   break;
  case 0xFFE01F: lcd.print("Tired");    break;
  case 0xFFA857: lcd.print("Sad :(");    break;
  case 0xFF906F: lcd.print("Night");    break;
  case 0xFF9867: lcd.print("Love You <3");    break;
  case 0xFFB04F: lcd.print("Thirsty");    break;
  case 0xFF6897: lcd.print("0");    break;
  case 0xFF30CF: lcd.print("1");    break;
  case 0xFF18E7: lcd.print("2");    break;
  case 0xFF7A85: lcd.print("3");    break;
  case 0xFF10EF: lcd.print("4");    break;
  case 0xFF38C7: lcd.print("5");    break;
  case 0xFF5AA5: lcd.print("6");    break;
  case 0xFF42BD: lcd.print("7");    break;
  case 0xFF4AB5: lcd.print("8");    break;
  case 0xFF52AD: lcd.print("9");    break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default: 
    Serial.println(" other button : ");
    Serial.println(results.value);

  }// End Case

  delay(500); // Do not get immediate repeat


} //END translateIR


void setup() 
{
  lcd.begin(16,2);
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn();
  pinMode(speakerPin,OUTPUT);

}


void loop() 
{
  if (irrecv.decode(&results)) // Have we received an IR signal?

  {
    lcd.clear();
    translateIR(); 
    irrecv.resume(); // Receive the next value
  }  
}
