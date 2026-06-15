#include <Wire.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 22, 21);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define GRID_SIZE 4

int ballp = 1;
int score = 0;
int buttonR = 26;
int buttonstateR = 0;
bool gameOver = false;
int buzzerPin = 33;
int speed = 100;

void setup(){
  u8g2.begin();
  pinMode(buttonR, INPUT_PULLUP);
  //Serial.begin(9600);
}

void loop(){
moveBall();
speedInc();
ballScore();
checkScore();
drawGame();
}

void drawGame(){
  u8g2.clearBuffer();
  u8g2.drawLine(100, 0, 100, 64);
  u8g2.drawDisc(ballp, 32, 3);
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.drawStr(5, 7, "Score:");
  u8g2.setCursor(40, 7);
  u8g2.print(score);
  u8g2.sendBuffer();


}

void moveBall(){
  if(ballp > 128){
    delay(100);
    ballp = -1;
 
 }else{ 
  ballp = ballp + 3 ;
  delay(speed);
  }
}

void ballScore(){
  buttonstateR = digitalRead(buttonR);

  if(buttonstateR == false && ballp > 95 && ballp < 105){
  score = score+1;
  tone(buzzerPin, 1500, 10);
  delay(100);
  //Serial.println("Right Pressed");
  }
  else if(buttonstateR == false && (ballp < 95 || ballp > 105)){
  score = score-1;
  tone(buzzerPin, 1500, 10);
  delay(100);
  tone(buzzerPin, 1000, 10);
  delay(100);
 }
}

void restartGame(){
  score = 0;
  gameOver = false;
}

void checkScore(){
 if (score < 0){
  gameOver = true;
  tone(buzzerPin, 300, 10);
  delay(200);
  endDisplay();
 }
}

void endDisplay(){
  if (gameOver == true){
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_9x15_tr);
    u8g2.drawStr(28, 39, "GameOver");
    u8g2.sendBuffer();
    delay(1500);
    restartGame();
  }
    
}

void speedInc(){
  if(score >= 30){
    speed = 0;
  }
  else if(score >= 25){
    speed = 10;
  }
  else if(score >= 20){
    speed = 20;
  }
  else if(score >= 15){
    speed = 30;
  }
  else if(score >= 10){
    speed = 40;
  }
  else if(score >= 5){
    speed = 50;
  }
  else{
    speed = 100;
  }
}




