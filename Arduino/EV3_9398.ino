/*
 LEGO Mindstorms EV3 - bluetooth - arduino - LEGO Technic Power Function - #9398
 ANdrey Stepanov, 2014
 */
#include <PowerFunctions.h>

int led = 13;
 
#include <SoftwareSerial.h>
#include <stdio.h>


int IR_pin = 5; // LEGO PF IR channel

PowerFunctions pf(IR_pin, 0);

// движение вперед
boolean forward = true;

// к 10 и 11 пину подключаем bluetooth
SoftwareSerial mySerial(10, 11); // RX, TX 

void setup()  
{
  pinMode(led, OUTPUT); 
  
  // Открываем Bluetooth соединение, пины 10 и 11
  mySerial.begin(38400);
  // Немного ждем
  delay(100);
 
  Serial.begin(9600);
  delay(200);
  Serial.println ("start");
  
}

void loop() 
{
  
  String inStringB = "";
  String inStringT = "";
  String inStringA = "";
  int i=0;
  
  while (mySerial.available()) // если что-то пришло по блютузу
    {
    char inChar = mySerial.read();
    if (inChar == ';') { // начало того, что нам нужно начинается с точки с запятой
      digitalWrite(led, HIGH);
      delay(1);
      // далее идут пять цифр - закодированы команды      
      inChar = mySerial.read(); 
      if (isDigit(inChar)) inStringB += (char)inChar; 
      delay(1);
      inChar = mySerial.read(); 
      if (isDigit(inChar)) inStringA += (char)inChar; 
      delay(1);
      inChar = mySerial.read(); 
      if (isDigit(inChar)) inStringA += (char)inChar; 
      delay(1);
      inChar = mySerial.read(); 
      if (isDigit(inChar)) inStringT += (char)inChar; 
      delay(1);
      inChar = mySerial.read(); 
      if (isDigit(inChar)) inStringT += (char)inChar; 
      delay(1);      
          
      i++; // помечаем, что что-то получили
      digitalWrite(led, LOW);
      break;      
      }   
    delay(1);  
    }
  
 // выводим полученное в порт для проверки
 if (i > 0) {
    
    int button = inStringB.toInt();
    int turn = inStringT.toInt();
    int acceleration = inStringA.toInt();
    
    int i=0;
    
    Serial.print ("Button: ");
    Serial.println (button);
    Serial.print ("Turn: ");
    Serial.println (turn);
    Serial.print ("Acceleration: ");
    Serial.println (acceleration);
    Serial.println (" ");
    
    if (button > 0) forward = !forward;
    
    switch (turn) {
    case 1:
      step(RED, PWM_REV7);
      break;
    case 2:
      step(RED, PWM_REV6);
      break;
    case 3:
      step(RED, PWM_REV5);
      break;
    case 4:
      step(RED, PWM_REV4);
      break;
    case 5:
      step(RED, PWM_REV3);
      break;
    case 6:
      step(RED, PWM_REV2);
      break;
    case 7:
      step(RED, PWM_REV1);
      break;
    case 8:
      step(RED, PWM_FLT);
      break;
    case 9:
      step(RED, PWM_FWD1);
      break;
    case 10:
      step(RED, PWM_FWD2);
      break;
    case 11:
      step(RED, PWM_FWD3);
      break;
    case 12:
      step(RED, PWM_FWD4);
      break;
    case 13:
      step(RED, PWM_FWD5);
      break;
    case 14:
      step(RED, PWM_FWD4);
      break;
    case 15:
      step(RED, PWM_FWD5);
      break;
    }

  delay(5);

  if (forward)
    {
    switch (acceleration) {
    case 0:
      step(BLUE, PWM_FLT);
      break;
    case 1:
      step(BLUE, PWM_FWD1);
      break;
    case 2:
      step(BLUE, PWM_FWD2);
      break;
    case 3:
      step(BLUE, PWM_FWD3);
      break;
    case 4:
      step(BLUE, PWM_FWD4);
      break;
    case 5:
      step(BLUE, PWM_FWD5);
      break;
    case 6:
      step(BLUE, PWM_FWD6);
      break;
    case 7:
      step(BLUE, PWM_FWD7);
      break;      
      }    
    }  
  else
    {
    switch (acceleration) {
    case 0:
      step(BLUE, PWM_FLT);
      break;
    case 1:
      step(BLUE, PWM_REV1);
      break;
    case 2:
      step(BLUE, PWM_REV2);
      break;
    case 3:
      step(BLUE, PWM_REV3);
      break;
    case 4:
      step(BLUE, PWM_REV4);
      break;
    case 5:
      step(BLUE, PWM_REV5);
      break;
    case 6:
      step(BLUE, PWM_REV6);
      break;
    case 7:
      step(BLUE, PWM_REV7);
      break;      
      }      
    }  
  delay(5);  
  }

}

void step(uint8_t output, uint8_t pwm) {
  pf.single_pwm(output, pwm);
}
