// include the library code:
#include <LiquidCrystal.h>

// storing pin numbers in a variable
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2,d8 = 8, d9 = 9;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// declaring global variables
// t - 100th part of 1 second used in clock
// s - second used in clock
// min - minute used in clock
// hrs - hours used in clock
// swt - 100th part of second used in stopwatch
// sws - second used in stopwatch
// swmin - minute used in stopwatch
int t,s,min,hrs, swt,sws,swmin = 0;

// defining function to calculate normal time and alarm
void time(){
if(t >= 99){ 
    t = 0;
    s = s + 1;
  }
  else{
    t = t + 1;
  }
  if(s == 60){
    s = 0;
    min = min + 1;
  }
  if(min == 60){
    min = 0;
    hrs = hrs + 1;
  }
  if(hrs == 24){
    hrs = 0;
  }
  if(digitalRead(d8) == 1){
    t = 0;
    s = 0;
    min = 0;
    hrs = 0;
  }
  // to see time in serial monitor
  //Serial.print(hrs);
  //Serial.print(":");
  //Serial.print(min);
  //Serial.print(":");
  //Serial.println(s);
}

// defining function to create stopwatch
void stopwatch(){
  // if pin-8(d8) is high then the stopwatch will start otherwise 
  // it will stop
  if(digitalRead(d8) == 1){
  if(swt >= 99){
    swt = 0;
    sws = sws + 1;
  }
  else{
    swt = swt + 1;
  }
  if(sws == 60){
    sws = 0;
    swmin = swmin + 1;
  }
  if(swmin == 60){
    swmin = 0;
  }
  }
  else if(digitalRead(d8) == 0){
    swt = swt;
    sws = sws;
    swmin = swmin;
  }
  
  // to see stopwatch time in serial monitor
  //Serial.print(swmin);
  //Serial.print(":");
  //Serial.print(sws);
  //Serial.print(".");
  //Serial.println(swt);
}

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 3);
  // set up bit exchange rate b/w arduino and system
  Serial.begin(9600);
  // defining pin modes
  pinMode(d8,INPUT); // start stopwatch and stop it
  pinMode(d9,INPUT); // switch b/w clock and stopwatch
  pinMode(10,OUTPUT); // to control buzzer buzzer
}

void loop(){ 
  // make sure that switch is closed so as to complete the 
  // circuit of buzzer
  // if time is 0:0:4 buzzer will give sound
  if(hrs == 0 & min == 0 & s == 4){
    digitalWrite(10,HIGH);
    //Serial.print("Buzzer is ringing");
  }
  // after 2s buzzer will turn off
  if(hrs == 0 & min == 0 & s == (4+2)){
    digitalWrite(10,LOW);
  }
  
  // if digital pin-9(d9) is high work as Clock with alarm else work as a Stopwatch
  if(digitalRead(d9) == 1){
    lcd.setCursor(0, 0);  
    lcd.print("Time :       ");
    lcd.setCursor(0, 1);
    time();
    swt = 0;
    sws = 0;
    swmin = 0;
    lcd.print(hrs);
    lcd.print(":");
    lcd.print(min);
    lcd.print(":");
    lcd.print(s);
    lcd.print("   ");
  }
  else if(digitalRead(d9) == 0){
    lcd.setCursor(0, 0);
    lcd.print("Stopwatch : ");
    lcd.setCursor(0, 1);
    time();
    stopwatch();
    lcd.print(swmin);
    lcd.print(":");
    lcd.print(sws);
    lcd.print(".");
    lcd.print(swt);
  }
  delay(10);       // giving delay of 10ms.
}
