
#include <at89c5131.h>
#include "lcd.h"		//Header file with LCD interfacing functions
#include "serial.c"	//C file with UART interfacing functions
#include <stdio.h>
#include <stdlib.h>

unsigned char K = 0;                                  // varaible for the while loop
unsigned char i;                                      // i as a argument for the  loop
unsigned char j;

unsigned char temp = 0;                              // temp stores the score after each game for comparison with current score 

const unsigned char string_1[]="Get Ready";          //  string is stored for LCD display

const unsigned char string_4[]="Score:";

const unsigned char string_5[] = "High";

unsigned char word[10][5];                          // array of sequence of 10 words
unsigned char digit[10];                            // array of digits associated withe the words
unsigned char index = 0;  

unsigned char present_value = 0x08 ;                // intialization of the first word from the sequence of 32 words   
unsigned char next_value;                           // variable to store digit of the next word given by lfsr

unsigned char bit_b3 = 0x08;                   
unsigned char bit_b0 = 0x01;
unsigned char bit_xor = 0;

unsigned char count = 0;                           // VARIABLE TO STORE THE SCORE AFTER EVERY GAME
unsigned char m ;                                  // M STORES THE VALUE OF SBUF


 //We first define our sequence of 31 word as stored in a 2D array
 
    code unsigned char  Sequence[31][5] = {"cafe","chef","asia","hand","john","king","lady","lava","nova","next","pero","silk","zero","zoom","wolf","bank","yoga","baby","year","axis","twin","fish","snow",
	"null","wave","user","time","july","join","hair","fuel"};




	
	
	
	


//Following function will get the digit for the given word from the 5_bit sequence 
unsigned char associated_num(unsigned char five_bitsequence){
    unsigned char temp = five_bitsequence;                   //temporary storage of the 5bit_sequence	
	  unsigned char digit = 0;
	  five_bitsequence &= 0x0F;                                // get the lower 4 bits of the sequence
    digit = five_bitsequence%10;                             // get the remainder 
    five_bitsequence = temp;                                 // store the initial sequence back
    return digit+48;                                         // return the ASCII vslue of the remainder
}


	





//********************************************************************************************************************************************************************//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//********************************************************************************************************************************************************************//

void timer_0(void)interrupt 1
{ TH0 = 0x15;                         // load timer 0 count for  delay of 0.3s 
	TL0 = 0x09f;
	K +=1;
	TR0 = 1;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//**********************************************main function?**********************************************************************************************
//----------------------------------------------------------------------------------------------------------------------------------------------------------

void main(void)
{
  lcd_init();                                                    // Initializes LCD port and LCD display parameters
  uart_init();                                                   // Initializes UART peripheral for 8_bit transfer, 1 start and 1 stop bits.
	TMOD = 0X21;                                                   // timer 0 in mode 2
  EA = 1;                                                        // enable global interrupt
  ET0 = 1;                                                       // enable timer 0 interrupt
  TH0 = 0x15;
  TL0 = 0x09f;                                                   // count values
	

	next_value = present_value;
    
    
   while(1)                                                     // inifinite loop
		 
	  {
			
			
		
      for( i=0; i<10; i++){                                // loop for dispalying words-digit pair for 1s each
				unsigned char bit_b3 = 0x08;                       // load bit_b3 to get the b3 from the 5_bit sequence
        unsigned char bit_b0 = 0x01;                       // load bit_b0 to get the b0 from the 5_bit sequence
        present_value = next_value;                        // assign next value to present value
        
  

        index = present_value-1;                        // index of the word in the array is 1 less than the present value of the word
        
        for( j=0; j<5; j++){
					
					
					
			    word[i][j] = Sequence[index][j];              // array contains the word according to the index defined by the present value
					
					
					
			   }
			
        digit[i] = associated_num(present_value);       // digit value correspnding to the word to be displayed on LCD
                      
        next_value = present_value;                 
				next_value >>= 1;                               // shift right by one unit 
				bit_b3 &= present_value;                        // anding present value with 0x08 to get b3
	      bit_b0 &= present_value;                        // anding present value with 0x01 to get b0
	      bit_xor = (bit_b0 <<4)^(bit_b3 <<1);            // shifting bit_b0 by 4 units [to get b0,0,0,0,0] and shifting bit_b3 by 1 unit [to get b3,0,0,0,0] 
				                                                //    and xor the two results
				
				next_value &=0x0F;                             // and next value wiht 0x0F to get the lower 4bits
	      next_value |= bit_xor;                         // add the  next value with bit_xor to get the required next state[ b3 xor bo,b4,b3,b2,b1]
	
					
					
  //------------------------------WORD PAIR PRINT-----------------------------------------------------------------------------------------------------------       
    
        lcd_cmd(0x85);                                  // move the cursor to 1st row,5th column
		    lcd_write_string(word[i]);                      // display the word on the 1st row of LCD
		    lcd_cmd(0xc7);                                  // move cursor to the 2nd row 7th column
		    lcd_write_char(digit[i]);                       // display the digit on the 2nd row of LCD
		    msdelay(1000);                                  // diplay word-digit pair for 1s each
				}
			
			lcd_cmd(0x01);                                    // clear LCD screen
			lcd_cmd(0x83);                                   // move cursor to the 1st row,3rd cloumn
			lcd_write_string(string_1);                      // diplay the message 'Get Ready'
			msdelay(3000);                                   // 3s delay
			lcd_cmd(0x01);                                   // clear the lcd screen
			
			  
				count = 0;                                     // initialize our score to zero(here count represent the score)
				
//--------------------------------WORD PRINT AND TAKES INPUT FROM THE USER----------------------------------------------------------------------------------				
				
	// this loop will print the 10 words each for 3 seconds	and takes
  // user input and compare with the digit of the word and increase the score if recieved digit is same as digit				
				
				for(i=0;i<10;i++)            
				{ 
				
				  lcd_cmd(0x85);                  // move cursor to row 1,column 5
		    	lcd_write_string(word[i]);      // write the word from the array according to the index
					TR0 =1;                         // enable timer 1for 3 seconds
			    while(K<100);                   // ssimple loop to give 3 s delay for timer
					
					                
					lcd_cmd(0xc7);             // move cursor to 2nd row,7th column
	
					lcd_write_char(m);          // write the recieved digit(in SBUF) ON LCD
			//digit[i] and m(SBUF) both are in ASCII		
					if(digit[i]==m)             //condition to compare both digits
					{ count += 1;                // if they are equal we will increase score by 1
					}
					K=0;                       // reset counter
	
				}
				lcd_cmd(0x01);                 // clear lcd
				lcd_cmd(0x80);                 // move cursor to 1st row 1st column
				lcd_write_string(string_4);     // print the Score: on lcd
				if(count >9){
					lcd_cmd(0x8e);               // if score = 10 we directly print using string function
					lcd_write_string("10");
				
				}
				
			else if(count <= 9){
				lcd_cmd(0x8e);
				lcd_write_char(count+48);
			}				// if score < 10 we print the ascii value of the score
				
				lcd_cmd(0xc0);              // clear the lcd
				lcd_write_string(string_5);
				lcd_cmd(0xc5);                  // print High Score: on lcd
				lcd_write_string(string_4);
				
		// Here we define a variable temp to store our score temporarily and compare it with our  score after 1 game is over
				if(count >= temp && count >9)     // if our score is greater than previous score and also greater then 9( so 10) ,we print "10"
					
					
				 {
					 
					 
					 temp = count;                // update the local score
					 lcd_cmd(0xce);
					 lcd_write_string("10");       // print "10" at 2nd row,15th column
					 msdelay(3000);
					 lcd_cmd(0x01);
					 
				  }
	// if current score is greater than previous score but less than 10 we print the current score and also update the variable score 
				 else if(count >= temp && temp <= 9)
					 
				  {
						
				    temp = count;     // variable score updated
					  lcd_cmd(0xce);
					  lcd_write_char(count+48);   // highest score printed on 2nd row 15th column
					  msdelay(3000);          // display it for 3s
					  lcd_cmd(0x01);          // clear the LCD  
						
						
				    }
	// if current score is less than previous score but previous score was 10 then we print 10				
				  else if(count <= temp && temp >9)
						
						
				   {
						 
						 

					   lcd_cmd(0xce);
					   lcd_write_string("10");     //  print "10" on 2nd row and 15th column
					   msdelay(3000);             // dispaly for 3s
					   lcd_cmd(0x01);              // clear the lcd
						 
						 
				     }
		// if current score is less than previous	score and prevous score was less than 10 we print the ascii value of the previous score 		 
					 
				   else if(count <= temp && temp <= 9)
						 
						 
				    {
							
						 
					   lcd_cmd(0xce);
				     lcd_write_char(temp+48);     // print the ascii value of previous score at the 2nd row 15th column
				     msdelay(3000);             // delay for 3s
				     lcd_cmd(0x01);               // clear the lcd
						}
					}
				}
				

					

					
					
					
					
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
			
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
		
		
		
    
   
    