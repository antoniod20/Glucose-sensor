#include <Keypad.h>

#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;
int pos=0; // LCD Connections
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
const byte rows=4;
const byte cols=3;

char key[rows][cols]={
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[rows]={1,2,3,4};
byte colPins[cols]={5,6,7};
Keypad keypad= Keypad(makeKeymap(key),rowPins,colPins,rows,cols);
char* password="1234";
int currentposition=0;



void setup()
{
displayscreen();
myservo.attach(9); //SERVO ATTACHED//
lcd.begin(16,2);
}

void loop()
{
if( currentposition==0)
{
displayscreen();
}
int l;
char code=keypad.getKey();
if(code!=NO_KEY)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("PASSWORD:");
lcd.setCursor(7,1);
lcd.print(" ");
lcd.setCursor(7,1);
for( l=0;l<=currentposition;++l)
{
lcd.print("*");
}

if (code==password[currentposition])
{
++currentposition;
if(currentposition==4)
{
unlockdoor();
currentposition=0;
}
}

else
{
incorrect();
currentposition=0;
}

  }

}

//*Open door*//

void unlockdoor()
{
delay(900);

lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(1,0);
lcd.print("Access Granted");
lcd.setCursor(4,1);
lcd.println("Opening");
lcd.setCursor(15,1);
lcd.println(" ");
lcd.setCursor(16,1);
lcd.println(" ");
lcd.setCursor(14,1);
lcd.println(" ");
lcd.setCursor(13,1);
lcd.println(" ");


for(pos = 180; pos>=0; pos-=5) // goes from 180 degrees to 0 degrees
{
myservo.write(pos); // tell servo to go to position in variable 'pos'
delay(15); // waits 15ms for the servo to reach the position
}
delay(3000);
  


for(pos = 0; pos <= 180; pos +=5) // goes from 0 degrees to 180 degrees
{ 
myservo.write(pos); // tell servo to go to position in variable 'pos'
delay(15);


currentposition=0;

lcd.clear();
displayscreen();

}
}

//*Wrong password*//

void incorrect()
{
delay(500);
lcd.clear();
lcd.setCursor(1,0);
lcd.print("Password");
lcd.setCursor(6,0);
lcd.print("Incorrect");
lcd.setCursor(15,1);
lcd.println(" ");
lcd.setCursor(4,1);
lcd.println("Try again");

lcd.setCursor(13,1);
lcd.println(" ");
Serial.println("Wrong code, access denied");
delay(3000);
lcd.clear();
displayscreen();
}
//*Creal Screen*//
void clearscreen()
{
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(0,1);
lcd.println(" ");
lcd.setCursor(0,2);
lcd.println(" ");
lcd.setCursor(0,3);
lcd.println(" ");
}

//*Initial Message*//
void displayscreen()
{

lcd.setCursor(0,0);
lcd.println("*Enter Password*");
lcd.setCursor(1 ,1);

lcd.println("To unlock door");
}
//*Arm Servo *//
void armservo()
{

for (pos=180;pos<=180;pos+=50)
{
myservo.write(pos);
delay(5);
}
delay(5000);

for(pos=180;pos>=0;pos-=50)
{
myservo.write(pos);
}

}
