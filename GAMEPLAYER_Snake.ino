#include <Wire.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define GRID_SIZE 4

int snakeX[30], snakeY[30];
byte snakeLen = 3;
byte foodX, foodY;
int dirX = 1, dirY = 0;
bool gameOver = false;
byte score = 0;

byte buttonL = 25;
byte buttonR = 26;
byte buttonUp = 27;
byte buttonDn = 14;

int buzzerPin = 33;

byte buttonstateL = 0;
byte buttonstateR = 0;
byte buttonstateUp = 0;
byte buttonstateDn = 0;

byte prevstateL = 1;
byte prevstateR = 1;
byte prevstateUp = 1;
byte prevstateDn = 1;



void setup() {
u8g2.begin();
//Serial.begin(9600);
randomSeed(analogRead(0));


snakeX[0] = 8, snakeY[0] = 8;
snakeX[1] = 7, snakeY[1] = 8;
snakeX[2] = 6, snakeY[2] = 8;

foodX = random(1, 32);
foodY = random(1, 16);

pinMode(buttonL, INPUT_PULLUP);
pinMode(buttonR, INPUT_PULLUP);
pinMode(buttonUp, INPUT_PULLUP);
pinMode(buttonDn, INPUT_PULLUP);
pinMode(buzzerPin, OUTPUT); 
}

void drawGame(){
  u8g2.clearBuffer();

  for(byte i = 0;i < snakeLen; i++){
    u8g2.drawBox(snakeX[i] * GRID_SIZE, snakeY[i] * GRID_SIZE, GRID_SIZE, GRID_SIZE);

  }
  u8g2.drawBox(foodX * GRID_SIZE, foodY * GRID_SIZE, GRID_SIZE, GRID_SIZE);

  u8g2.sendBuffer();
}

void loop() {
  readInput();
  moveSnake();
  checkCollision();
  endGame();
  drawGame();
  delay(100);


}

void moveSnake(){
  for (byte i = snakeLen - 1; i > 0; i--){
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  snakeX[0] += dirX;
  snakeY[0] += dirY;

  if( snakeX[0] == foodX && snakeY[0] == foodY){
    snakeLen++;
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

  score = snakeLen - 3;
}

void readInput(){
  buttonstateR = digitalRead(buttonR);
  buttonstateL = digitalRead(buttonL);
  buttonstateUp = digitalRead(buttonUp);
  buttonstateDn = digitalRead(buttonDn);


  if (buttonstateR == false && dirX != -1 && prevstateR == true){
    if(dirX != 1 || dirY != 0){
      tone(buzzerPin, 1500, 10); 
    }
    dirX = 1; dirY = 0;
    //Serial.println("Right Pressed");
  }
  else if (buttonstateL == false && dirX != 1 && prevstateL == true){
    if(dirX != -1 || dirY != 0){
      tone(buzzerPin, 1500, 10); 
    }
    dirX = -1; dirY = 0;
    //Serial.println("Left Pressed");
  }
  else if (buttonstateUp == false && dirY != 1 && prevstateUp == true){
    if(dirX != 0 || dirY != -1){
      tone(buzzerPin, 1500, 10); 
    }
    dirX = 0; dirY = -1;
    //Serial.println("Up Pressed");
  }
  else if (buttonstateDn == false && dirY != -1 && prevstateDn == true){
    if(dirX != 0 || dirY != 1){
      tone(buzzerPin, 1500, 10); 
    }
    dirX = 0; dirY = 1;
    //Serial.println("Down Pressed");
  }

  prevstateL = buttonstateL;
  prevstateR = buttonstateR;
  prevstateUp = buttonstateUp;
  prevstateDn = buttonstateDn;
}

void checkCollision(){
  for(byte i = 1;i < snakeLen; i++) {
    if(snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]){
      gameOver = true;
     
    }
  
  }
}
void endGame(){
    if (gameOver == true){
    tone(buzzerPin, 300, 10);
    delay(200);
    endDisplay();
    delay(1500);
    restartGame();
    gameOver = false;

   }
}

void restartGame(){
  snakeLen = 3;
  dirX = 1, dirY = 0;
  score = 0;
  snakeX[0] = 8, snakeY[0] = 8;
  snakeX[1] = 7, snakeY[1] = 8;
  snakeX[2] = 6, snakeY[2] = 8;
  
}
void endDisplay(){
  if (gameOver == true){
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_9x15_tr);
    u8g2.drawStr(28, 39, "GameOver");
    u8g2.drawStr(28, 51, "Score:");
    u8g2.setCursor(82, 51);
    u8g2.print(score);
    u8g2.sendBuffer();
    delay(200);
  }
}
