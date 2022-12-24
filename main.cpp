#include "mbed.h"
#include "TS_DISCO_F429ZI.h"
#include "LCD_DISCO_F429ZI.h"
#include <iostream>
extern "C" uint32_t getQuad(uint16_t x, uint16_t y);
extern "C" uint32_t swapRedBlue(uint32_t color);
extern "C" void toggleAlphaMSB(uint32_t* color);
extern "C" uint32_t rotateRGBBytes(uint32_t color);
extern "C" uint32_t setRGBbits(uint32_t color, uint8_t n);

LCD_DISCO_F429ZI lcd;
TS_DISCO_F429ZI ts;


int main()
{        
    uint32_t quadOne = 0xFFFF0000;
    uint32_t quadTwo = 0xFF00FF00;
    uint32_t quadThree = 0xFF0000FF;
    uint32_t quadFour = 0xFFFFFF00;
    uint32_t currQuad = 0;
    
    uint8_t bits = 8;
    
    TS_StateTypeDef TS_State;
    uint16_t x, y;

    uint8_t text[30];
    uint8_t status;
  
    BSP_LCD_SetFont(&Font20);
  
    lcd.DisplayStringAt(0, LINE(5), (uint8_t *)"TOUCHSCREEN", CENTER_MODE);
    lcd.DisplayStringAt(0, LINE(6), (uint8_t *)"DEMO", CENTER_MODE);
    wait(1);
  
    status = ts.Init(lcd.GetXSize(), lcd.GetYSize());
  
    if (status != TS_OK)
    {
      lcd.Clear(LCD_COLOR_RED);
      lcd.SetBackColor(LCD_COLOR_RED);
      lcd.SetTextColor(LCD_COLOR_WHITE);
      lcd.DisplayStringAt(0, LINE(5), (uint8_t *)"TOUCHSCREEN", CENTER_MODE);
      lcd.DisplayStringAt(0, LINE(6), (uint8_t *)"INIT FAIL", CENTER_MODE);
    }
    else
    {
      lcd.Clear(LCD_COLOR_GREEN);
      lcd.SetBackColor(LCD_COLOR_GREEN);
      lcd.SetTextColor(LCD_COLOR_BLACK);
      lcd.DisplayStringAt(0, LINE(5), (uint8_t *)"TOUCHSCREEN", CENTER_MODE);
      lcd.DisplayStringAt(0, LINE(6), (uint8_t *)"INIT OK", CENTER_MODE);
    }
    
    wait(1);
    lcd.Clear(LCD_COLOR_WHITE);
    lcd.SetBackColor(LCD_COLOR_WHITE);
    lcd.SetTextColor(LCD_COLOR_RED);
    wait(2);
    
            
         //Quadrant 1
    lcd.SetTextColor(quadOne);
    lcd.FillCircle(170, 62, 50); 
     wait(0.1);
      //Quadrant 2 
    lcd.SetTextColor(quadTwo);
    lcd.FillCircle(50, 72, 50);
    wait(0.1);
      //Quadrant 3
    lcd.SetTextColor(quadThree);     
    lcd.FillCircle(50, 260, 50);
    wait(0.1);
      //Quadrant 4
      lcd.SetTextColor(quadFour);
      lcd.FillCircle(170, 261, 50);
      wait(0.1);  
    
    
    
    while(1)
    {
  
                  
    //Quadrant 1
    lcd.SetTextColor(quadOne);
    lcd.FillCircle(170, 62, 50); 
    
      //Quadrant 2 
    lcd.SetTextColor(quadTwo);
    lcd.FillCircle(50, 72, 50);
    
      //Quadrant 3
    lcd.SetTextColor(quadThree);     
    lcd.FillCircle(50, 260, 50);
    
      //Quadrant 4
      lcd.SetTextColor(quadFour);
      lcd.FillCircle(170, 261, 50);
  
          
   
      ts.GetState(&TS_State);    
        
      if (TS_State.TouchDetected)
      {
        x = TS_State.X;
        y = TS_State.Y;
        //SAVE Quad Value
        currQuad = getQuad(x,y);
        
        if(currQuad > 4){
         currQuad = 5;
         }
         
         sprintf((char*)text, "currQuad: %d ", currQuad);
        lcd.DisplayStringAt(0, LINE(8), (uint8_t *)&text, LEFT_MODE);
    
        
        sprintf((char*)text, "x=%d y=%d    ", x, y);
        lcd.DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);
    
        
         }
         
         //Touch Quadrant 1
      //x > 125 && x <= 255 && y < 125
      if(currQuad == 1){
        //Quadrant 1
        quadOne = swapRedBlue(quadOne);
         
     
          }
          
        //Touch Quadrant 2 
       // x > 0 && x <= 100 && y < 125
        if(currQuad == 2){
            toggleAlphaMSB(&quadTwo);
            
            }
        
        //Touch Quadrant 3
        //x > 0 && x <= 100 && y > 200
        if(currQuad == 3){
            quadThree = rotateRGBBytes(quadThree);
                
        }
        //Touch Quadrant 4
       //x > 125 && <= 255 && y > 200
        if(currQuad == 4){
            quadFour = setRGBbits(quadFour, bits);
            }
        wait(0.1);
      } 
}

