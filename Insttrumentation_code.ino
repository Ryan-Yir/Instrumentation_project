#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//int counter = 0;
void printOnLCD();
void printSecondLine();
void calculateSpeed();
void printSpeed();
int shouldCount;
int var;
int PreviousPinState = digitalRead(8);
int currentState;
int motorSpeedRPS;
int motorSpeedRPM;



void printOnLCD(String text){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TS:");
  lcd.setCursor(4, 0);
  lcd.print(text);
}

void printSecondLine(String text){
  if (var == 1){
    lcd.setCursor(0, 1);
    lcd.print(text);
    delay(4000);
    lcd.clear();
  }
}

void printSpeed(int speed){
  if (var == 0){
    lcd.setCursor(0, 1);
    lcd.print("Speed: ");
    lcd.setCursor(8, 1);
    lcd.print(speed);
  }
}

void calculateSpeed(){
  if (shouldCount == 1){
    if (PreviousPinState == LOW){
    delay(1);
    currentState = digitalRead(8);
    if (currentState == HIGH && PreviousPinState == LOW){
      counter += 1;
      Serial.print('The value is: ');
      Serial.println(counter);
      }
    }
  }
}
 
/*if (PreviousPinState == LOW){
    delay(1);
    currentState = digitalRead(8);
    if (PreviousPinState == LOW && currentState == HIGH){
      counter += 1;
      Serial.println(counter);
      delay(1000);
      motorSpeedRPS = counter/2;
      motorSpeedRPM = motorSpeedRPS/ 60;
      Serial.print("The current motor speed is:");
      Serial.println(motorSpeedRPM);
      printSecondLine("Speed:");
      lcd.setCursor(8, 1);
      lcd.print(motorSpeedRPM);
      
    }
    }
*/

void setup() {
  // put your setup code here, to run once:
pinMode(8, INPUT);
pinMode(9, OUTPUT);
pinMode(10, INPUT);
pinMode(11, INPUT);

lcd.init();
lcd.backlight();

Serial.begin(9600);
Serial.print("The current value of the counter is:");
Serial.println(counter);

lcd.setCursor(0, 0);
lcd.print("Bienvenue");
delay(5000);
lcd.clear();

}



void loop() {
  // put your main code here, to run repeatedly:


  int comparator1 = digitalRead(10);
  int comparator2 = digitalRead(11);

  if (comparator1 == LOW && comparator2 == LOW){
    var = 1;
    //Serial.println("The temperature is below room temperature");
    printOnLCD(" In range.");
    digitalWrite(9, 0);
  } else if (comparator1 == HIGH && comparator2 == LOW){
    var = 1;
    //Serial.println("The temperature is between room temperature and body temperature");
    printOnLCD("Low temp");
    digitalWrite(9, 0);
  } else{
    shouldCount = 1;
    //Serial.println("The temperature is above body temperature");
    printOnLCD("Faily hot");
    printSecondLine("Turning On Fan");
    printSpeed(motorSpeedRPM);
    var = 0;
    digitalWrite(9, 1);

  //  calculateSpeed();
    delay(1000);
    shouldCount = 0;
    motorSpeedRPS = counter/2;
    motorSpeedRPM = motorSpeedRPS*60;
    printSpeed(motorSpeedRPM);
  
  
  }
  
delay(500);

}