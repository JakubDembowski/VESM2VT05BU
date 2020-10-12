#include <LiquidCrystal.h>
#include <IRremote.h>
#define trigPin 7
#define echoPin 6
#define buzzer 9
#define backlight 10

LiquidCrystal lcd(12, 11, 5, 4, 3, 8);
UltraSonicDistanceSensor distanceSensor(trigPin, echoPin);

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

int blikktimi = 1000; 
unsigned long lidinn_blikk_timi = 0;

String lesaLykilord = ""; // innsláttur skrifast í þetta
String lykilord = "3830";
char stadfestaTakn = 'a'; // ýtt á 'a' til að kanna lykilorð

const unsigned long kodar[] = {  0xFFA25D,
                                 0xFF629D,
                                 0xFFE21D,
                                 0xFF22DD,
                                 0xFF02FD,
                                 0xFFC23D,
                                 0xFFE01F,
                                 0xFFA857,
                                 0xFF906F,
                                 0xFF9867,
                                 0xFFB04F,
                                 0XFF6897,
                                 0xFF30CF,
                                 0xFF18E7,
                                 0xFF7A85,
                                 0xFF10EF,
                                 0xFF38C7,
                                 0xFF5AA5,
                                 0xFF42BD,
                                 0xFF4AB5,
                                 0xFF52AD
                              };

const char takn[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g',
                     'h', 'i', 'j', 'k', '0', '1', '2',
                     '3', '4', '5', '6', '7', '8', '9'
                    };

char finnaTakn(unsigned long kodiFraRemote) {
  for (int i = 0; i < 21; i++)
    if (kodar[i] == kodiFraRemote)
      return takn[i];
  return 'x';
}

void setup() {
  irrecv.enableIRIn();
  lcd.begin(16, 2);
  attachInterrupt(0, changeMode, FALLING);
  pinMode(2, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(backlight, OUTPUT);
  digitalWrite(backlight, HIGH);
  backlightOn();
}

void loop() {
  if (irrecv.decode(&results)) {
    char innslegidTakn = finnaTakn(results.value);
    if (innslegidTakn != 'x') {
      lesaLykilord += innslegidTakn;
    }
    irrecv.resume(); // Receive the next value
  }
  if (lesaLykilord.endsWith(lykilord + 'b')) {
    Serial.println("------Rett Lykilord------");
    lesaLykilord = "";
    unbuzz();
  }
  if (lesaLykilord.length() > 20) { 
    lesaLykilord = lesaLykilord.substring(10);
  }
    
    if (distance >= 300 || distance <= 0) {
      rounded = 0;
      lcd.clear();
      backlightOff();
    }
    else {
      rounded = round(distance);
      if (distance >= 200) {
        backlightOff();
        lcd.clear();
      }
      else if (distance <= 150 && distance > 100) {
        backlightOn();
        lcd.clear();
        lcd.print("Please keep away");
        lcd.setCursor(0, 1);
        lcd.print("Distance:");
        lcd.print(rounded);
        lcd.print(" cm");
      }
      else if (distance <= 100 && distance > 100) {
        backlightOn();
        lcd.clear();
        lcd.print("Keep away");
        lcd.setCursor(0, 1);
        lcd.print("Distance:");
        lcd.print(rounded);
        lcd.print(" cm");
        delay(200);
        buzz();
        backlightOff();
        delay(100);
        unbuzz();
        backlightOn();
        delay(100);
      }
      else if (distance <= 90) {
        backlightOn();
        lcd.clear();
        lcd.print("STAY AWAY!");
        lcd.setCursor(0, 1);
        lcd.print("Distance:");
        lcd.print(rounded);
        lcd.print(" cm");
        if (irrecv.decode(&results)) {
    char innslegidTakn = finnaTakn(results.value);
    if (innslegidTakn != 'x') {
      lesaLykilord += innslegidTakn;
    }
    irrecv.resume(); // Receive the next value
  }
  if (lesaLykilord.endsWith(lykilord + 'a')) {
    Serial.println("------Rett Lykilord------");
    lesaLykilord = "";
  }
  if (lesaLykilord.length() > 20) { // til að minnið fyllist ekki af strengnum
    lesaLykilord = lesaLykilord.substring(10);
  }
 
  }
  delay(700);
}

void changeMode() {
  modes = !modes;
}

void backlightOn() {
  digitalWrite(backlight, HIGH);
}

void backlightOff() {
  digitalWrite(backlight, LOW);
}

void buzz() {
  digitalWrite(buzzer, HIGH);
}

void unbuzz() {
  digitalWrite(buzzer, LOW);
}
