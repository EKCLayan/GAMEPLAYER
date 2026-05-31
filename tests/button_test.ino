// Button connection test 
// Open Serial Monitor at 9600 baud to verify all 4 buttons are wired correctly 
// Each button should print its direction in loop when pressed

byte buttonL = 6;
byte buttonR = 5;
byte buttonUp = 7;
byte buttonDn = 8;

byte buttonstateL = 0;
byte buttonstateR = 0;
byte buttonstateUp = 0;
byte buttonstateDn = 0;

void setup() {
pinMode(buttonL, INPUT_PULLUP);
pinMode(buttonR, INPUT_PULLUP);
pinMode(buttonUp, INPUT_PULLUP);
pinMode(buttonDn, INPUT_PULLUP);
Serial.begin(9600);

}

void loop() {
  buttonstateR = digitalRead(buttonR);
  buttonstateL = digitalRead(buttonL);
  buttonstateUp = digitalRead(buttonUp);
  buttonstateDn = digitalRead(buttonDn);

if (buttonstateR == false){
  Serial.println("Right was clicked");  
}
else if (buttonstateL == false){
  Serial.println("Left was clicked");
}
else if (buttonstateUp == false){
  Serial.println("Up was clicked");
}
else if (buttonstateDn == false){
  Serial.println("Down was clicked");
}
}
