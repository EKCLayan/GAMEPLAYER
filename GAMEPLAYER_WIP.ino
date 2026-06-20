#include <Wire.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 22, 21);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define GRID_SIZE 8

int blockpp = 1;
int blockp = blockpp * GRID_SIZE;

void setup() {
 u8g2.begin();

}

void loop() {
 drawGame();
 moveBlock();
 

}

void drawGame(){
  u8g2.clearBuffer();
  u8g2.drawBox(blockp, SCREEN_HEIGHT - GRID_SIZE, GRID_SIZE, GRID_SIZE);
  u8g2.sendBuffer();
  delay(100);


}
void moveBlock(){
 if(blockpp < 4){
  blockpp = blockpp + 1;
  blockp = blockpp * GRID_SIZE;
  delay(100);
 }
}

