#include <Wire.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 22, 21);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define GRID_SIZE 8

int blockpp = 1;
int wallpp = 128;
int buttonUp = 27;
int buttonstateUp = 1;
int blockp = blockpp * GRID_SIZE;
int blockhp = SCREEN_HEIGHT - GRID_SIZE - 3;
int buzzerPin = 33;
bool blocktopos = false;
bool gameOver = false;

void setup() {
 u8g2.begin();
 pinMode(buttonUp, INPUT_PULLUP);
 //Serial.begin(9600);

}

void loop() {
 drawGame();
 blockJump();
 moveBlock();
 moveWall();
 blockwallCollision();

}

void drawGame(){
  u8g2.clearBuffer();
  blockFloor();
  u8g2.drawBox(blockp, blockhp, GRID_SIZE, GRID_SIZE);
  u8g2.drawBox(wallpp, 45, 4, 16);
  u8g2.sendBuffer();
  delay(100);

  blockhp = SCREEN_HEIGHT - GRID_SIZE - 3;

}
void moveBlock(){
 if(blockpp < 4){
  blockpp = blockpp + 1;
  blockp = blockpp * GRID_SIZE;
  delay(100);
 }
 else{
  blocktopos = true;
 }
}

void moveWall(){
 if(blocktopos == true && wallpp > 0){
  wallpp = wallpp - 3;
  delay(100);
 }
 else if(wallpp <= 0){
  wallpp = 128;
 }
}
void blockJump(){
buttonstateUp = digitalRead(buttonUp);

if(buttonstateUp == LOW){
 //Serial.println("button pressed");
 blockhp = blockhp - 25;
}
}

void blockFloor(){
u8g2.drawBox(0, 61, 124, 3);
}

void blockwallCollision(){
if(blockp + GRID_SIZE >= wallpp && blockhp >= 45 && blockp<= wallpp + 4){
  gameOver = true;
  tone(buzzerPin, 300, 10);
  endDisplay();
}
}
void endDisplay(){
  if(gameOver == true){
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_9x15_tr);
    u8g2.drawStr(28, 39, "GameOver");
    u8g2.sendBuffer();
    delay(2000);
    restartGame();
    gameOver = false;
  }
}

void restartGame(){
  blockpp = 1;
  blockp = blockpp * GRID_SIZE;
  blocktopos = false;
  wallpp = 128;
}
