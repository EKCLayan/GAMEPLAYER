#include <Wire.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define GRID_SIZE 4

int snakeX[100], snakeY[100];
int snakeLen = 3;
int foodX, foodY;
int dirX = 1, dirY = 0;
bool gameOver = false;
int score = 0;

int buttonL = 6;
int buttonR = 5;

int buttonstateL = 0;
int buttonstateR = 0;



void setup() {
u8g2.begin();
randomSeed(analogRead(0));

snakeX[0] = 8, snakeY[0] = 8;
snakeX[1] = 7, snakeY[1] = 8;
snakeX[2] = 6, snakeY[2] = 8;

foodX = random(1, 32);
foodY = random(1, 16);

pinMode(buttonL, INPUT_PULLUP);
pinMode(buttonR, INPUT_PULLUP);
}

void drawGame(){
  u8g2.clearBuffer();

  for(int i = 0;i < snakeLen; i++){
    u8g2.drawBox(snakeX[i] * GRID_SIZE, snakeY[i] * GRID_SIZE, GRID_SIZE, GRID_SIZE);

  }
  u8g2.drawBox(foodX * GRID_SIZE, foodY * GRID_SIZE, GRID_SIZE, GRID_SIZE);

  u8g2.sendBuffer();
}

void loop() {
  readInput();
  moveSnake();
  drawGame();
  delay(100);


}

void moveSnake(){
  for (int i = snakeLen - 1; i > 0; i--){
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  snakeX[0] += dirX;
  snakeY[0] += dirY;

  if( snakeX[0] == foodX && snakeY[0] == foodY){
    snakeLen++;
    score++;
    foodX = random(1, 32);
    foodY = random(1, 16);
  }

  if(snakeX[0] > 31){
    snakeX[0] = 0;
  }
  if(snakeY[0] < 0){
    snakeY[0] = 15;
  }
  if(snakeX[0] < 0){
    snakeX[0] = 31;
  }
  if(snakeY[0] > 15){
    snakeY[0] = 0;
  }
}

void readInput(){
  buttonstateR = digitalRead(buttonR);
  buttonstateL = digitalRead(buttonL);


  if (buttonstateR == false && buttonstateL == true && dirX == 1 ){
    dirX = 0; dirY = 1;
    //Serial.println("Moving Right");
  }
  else if (buttonstateL == false && buttonstateR == true && dirX == 1){
    dirX = 0; dirY = -1;
    //Serial.println("Moving left");
  }
  else if (buttonstateR == false && buttonstateL == true && dirX == -1 ){
    dirX = 0; dirY = -1;
    //Serial.println("Moving Right");
  }
  else if (buttonstateL == false && buttonstateR == true && dirX == -1){
    dirX = 0; dirY = 1;
    //Serial.println("Moving left");
  }
  else if (buttonstateR == false && buttonstateL == true && dirY == 1 ){
    dirX = -1; dirY = 0;
    //Serial.println("Moving Right");
  }
  else if (buttonstateL == false && buttonstateR == true && dirY == 1){
    dirX = 1; dirY = 0;
    //Serial.println("Moving left");
  }
  else if (buttonstateR == false && buttonstateL == true && dirY == -1 ){
    dirX = 1; dirY = 0;
    //Serial.println("Moving Right");
  }
  else if (buttonstateL == false && buttonstateR == true && dirY == -1){
    dirX = -1; dirY = 0;
    //Serial.println("Moving left");
  }

}

