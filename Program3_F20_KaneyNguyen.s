        AREA Program3_F20_KaneyNguyen, CODE, READONLY  
        
        GLOBAL getQuad
        
        ;uint32_t getQuad(uint16_t x, uint16_t y)
   //x > 125 && x <= 255 && y < 125
getQuad CMP R0,#125
        BLE otherQuad
        CMP R1, #125
        BGE quad4
        MOV R0, #1
        b leave
         //Quad 4
        //x > 125 && <= 255 && y > 200
quad4   CMP R0,#125
        BLE otherQuad
        CMP R1, #200
        BLE otherQuad
        MOV R0, #4
    
        b leave
otherQuad        
        //Quad 2
        // x > 0 && x <= 100 && y < 125
        CMP R1, #125
        BGE quad3
        //EXECUTE CODE
        MOV R0, #2
        
        b leave
        //Quad 3
        //x > 0 && x <= 100 && y > 200
quad3   CMP R1, #200
        BLE leave
        MOV R0, #3
        b leave
        
leave   BX LR
        
        GLOBAL swapRedBlue
        ;uint32_t swapRedBlue(uint32_t color)
swapRedBlue     LDR R1, =0x000000FF //blue byte
                LDR R2, =0x00FF0000//red byte
                LDR R3, =0xFF00FF00//Alpha, green byte
                
                //Grab Each color
                AND R1, R0, R1
                AND R2, R0, R2
                AND R3, R0, R3
                
                // Mov the position
                MOV R1, R1, LSL 16
                MOV R2, R2, LSR 16
                
                //Merge
                ORR R3, R3, R1
                ORR R3, R3, R2
                
                MOV R0, R3
                
         GLOBAL toggleAlphaMSB   
        ;void toggleAlphaMSB(uint32_t* color)
toggleAlphaMSB  // alpha on and off
                LDR R1, [R0,#0]
                MVN R1, R1;
                STR R1, [R0,#0] 
                
                BX LR
    
        GLOBAL rotateRGBBytes
        ;uint32_t rotateRGBBytes(uint32_t color)
                //0xFF0000FF;
                //0xFFFF0000
rotateRGBBytes  LDR R1,=0x0000FF00 //G
                LDR R2,=0x000000FF //B 
                LDR R3,=0xFFFF0000 //A R
                // SWAP BYTE 1 And Byte 0 in the color      
                AND R1, R0, R1
                AND R2, R0, R2
                AND R3, R0, R3
                                
                MOV R1, R1, LSR 8
                MOV R2, R2, LSL 8
                
                ORR R3, R3, R1
                ORR R3, R3, R2
                
                
                // R3  is RBG 
                //----  
                //SWAP BYTE 2 with 1 Which a complete rotation 
                LDR R1,=0x00FF0000
                LDR R2,=0x0000FF00
                LDR R4,=0xFF0000FF
                
                AND R1, R3, R1
                AND R2, R3, R2
                AND R4, R3, R4    
                
                MOV R1, R1, LSR 8
                MOV R2, R2, LSL 8
                     
                ORR R4, R4, R1
                ORR R4, R4, R2
                
                MOV R0, R4
                BX LR
            
            GLOBAL setRGBbits   
        ;uint32_t setRGBbits(uint32_t color, uint8_t n)
setRGBbits      LDR R2,=0x00FF0000
                LDR R3,=0x0000FF00
                LDR R4,=0x000000FF
                LDR R5,=0xFF000000
                //00000001
                //n = 1 => 0 
                //n = 2 => 1 
                //the formula to get into specific bits position is
                //Make a hex value of 1, then shif the value by n-1, 
                //because in binary representation of 1, 
                // 00000001, if n = 8, that mean n-1 = 7, shift the value to the left 7, bits binary become 10000000
                //NEXT USE ORR OPERATOR On every single byte, a byte represent as 8 bits
                //so if color bits is 11000000, Exclusive OR OPERATOR to turn bit on and off
                SUB R1, R1, #1                  
                LDR R6, =0x00000001    
            
                                
                AND R2, R2, R0
                AND R3, R3, R0
                AND R4, R4, R0
                AND R5, R5, R0
                //Shift by hex
                MOV R6, R6, LSL 16
                //Shift by bits
                LSL R6, R6, R1
                
                EOR R2, R2, R6
                
                
                 //Shift by hex
                MOV R6, R6, LSR 8
                //shift by bits
                LSL R6, R6, R1
                
                EOR R3, R3, R6
                    
                 //Shift by hex
                 MOV R6, R6, LSR 8
                 //Shift by bits
                 
                 //Shift by hex
                 MOV R6, R6, LSR 8
                 //Shift by bits
                 LSL R6, R6, R1
                     
                EOR R4, R4, R6
                 
                ORR R5, R5, R2
                ORR R5, R5, R3
                ORR R5, R5, R4
                
                MOV R0, R5
                
                BX LR    
                 
                NOP   
                END
                
    