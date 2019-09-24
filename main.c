#include "TM4C123GH6PM.h"
#include <stdint.h>
#include "prototype.h"
#include "math.h"


uint8_t sign=0;    // store input sign (+,-,/,*)
uint32_t i=0;      //index for array of no[4]
uint8_t z=1;      // check that no signs can come after each other ex; ++,+= , intialized with 1 to prevent begining with any sign.
uint8_t x=0;      // calculate operands.
uint8_t no[5];    //array store the numbers of the operand
volatile uint8_t key;      //recieve the returned character
volatile int flag=0;       //it's value turns 1 in the handler so that it can't execute the instructions in the switch case without interrupt happens.
uint32_t res;     //the result.
uint32_t op=0;    //operand calculation.
uint64_t clock;
unsigned char contact[10];

   int main(void)
{
	     LCD_Init();
             keypad_init(); 
             Listinit();
             TimeRTCinint();
 start:      lcd_Command(1);     //clear LCD
             lcd_Command(0x80);  //LCD cursor location 
        lcd_data('s');
        lcd_data('e');
        lcd_data('l');
        lcd_data('e');
        lcd_data('c');
        lcd_data('t');
        lcd_data(' ');
        lcd_data('1');
        lcd_data('-');
        lcd_data('c');
        lcd_data('a');
        lcd_data('l');
        lcd_data('c');
        lcd_data('.');
        lcd_data(' ');
        lcd_data('2');
        lcd_data('-');
        lcd_data('c');
        lcd_data('l');
        lcd_data('o');
        lcd_data('c');
        lcd_data('k');
        lcd_data(' ');
        lcd_data('3');
        lcd_data('-');
        lcd_data('c');
        lcd_data('o');
        lcd_data('n');
        lcd_data('t');
        lcd_data('a');
        lcd_data('c');
        lcd_data('t');
        lcd_data(' ');
        lcd_data('l');
        lcd_data('i');
        lcd_data('s');
        lcd_data('t');
      
        delayMilliSec(3000);
        lcd_Command(1);    //clear LCD.
  while(1){
	    /* do{                          // be sure user entered a key.
           key= readKeypad();
           delayMilliSec(200);  
	       }
             while(key==0);*/
    if(flag==1){
                     flag=0;
                     if(key =='1')
                     {
                       key =0;
                        lcd_data('2');
                        lcd_data('-');
                        lcd_data('o');
                        lcd_data('p');
                          lcd_data('e');
                          lcd_data('r');
                          lcd_data('a');
                          lcd_data('n');
                        lcd_data('d');
                        lcd_data('s');
                          lcd_data(' ');
                          lcd_data('o');
                          lcd_data('n');
                          lcd_data('l');
                          lcd_data('y');
                       delayMilliSec(3000);
                        lcd_Command(1);    //clear LCD.
                     
        	     switch(key){
                case '0':
                     lcd_data(key);        //show the number.
        //store the number in array to use it later in the calculation of the input operand      
                     no[i]=key;								
        //increase the index of the array and zeroing the z again to enable entering a sign or  =    
                     i++;
                     z=0;            
                     break;
                case '1':
                    lcd_data(key);
                     no[i]=key;
                     i++;
                     z=0;
                //key='-';     
		   break;
                case '2':
                     lcd_data(key);
                     no[i]=key;
                     i++;
                     z=0;
                //key='=';     
		   break;
                case '3':
                     lcd_data(key);
                     no[i]=key;
                     i++;
                     z=0;
                     break;
                case '4':                
                     lcd_data(key);
                     no[i]=key;
                     i++;
                     z=0;
                     break;
                case '5':        
                     lcd_data(key);
                     no[i]=key;
                     i++;
                     z=0;
                   // key='-'; 
                     break;
                case '6':
                     lcd_data(key);
                     no[i]=key;
                     i++;
                     z=0;
                     break;
                case '7':
                     lcd_data(key);
                     no[i]=key;
                     i++;
                     z=0;
                     break;
                case '8':
                     lcd_data(key);
                     no[i]=key;
                     i++; z=0;
                     //store(op);
                     break;
                case '9':
                     lcd_data(key);
                     no[i]=key;
                     i++;
                     z=0;
                     break;
                
               
                  case '+':
                 //if z=1 that means that the previous pressed key was also a sign resulting in erro
                 if(z==0)     
                  {
                    calculate_operand(no,i-1);			//firstly calculate the operand stored in no[]
		    store(op);
		    lcd_data(key);              //show the new sign.
                     z++;                        //to prevent two signs from coming after each other
		    i=0;                        //Zeroing the index of the no[] again
                     sign=key;
                     break;
                  }
                  else
                  {
                     error();    //void function to preview an "error" on the lcd
		   goto start;  // go to label start that erase the lcd again and starting the code again.
                  }
                case '-':
                  if(z==0)
                  {
                     calculate_operand(no,i-1);
		    store(op);
                     lcd_data(key);
                     z++;
                     i=0;               
                     sign=key;
                    //key='2'; 
                     break;
                  }
                  else
                  {
                     error();
		   goto start;                 
                  }
               case '*':
                  if(z==0)
                  {
                     calculate_operand(no,i-1);						
                     store(op);
                     lcd_data(key);
                     z++;
		     i=0;                     
                     sign=key;
                     break;
                  }
                  else
                  {
                     error();
                     goto start;               
                  }
               case '/':
                  if(z==0)
                  {
                     calculate_operand(no,i-1);
                     store(op);
                     lcd_data(key);
                     z++;
		    i=0;                        
                     sign=key;
                     break;
                  }
                  else
                  {
                     error();
                     goto start;
                  }
              case '=':
                 if(z==0)
                  {
                     calculate_operand(no,i-1);
                     switch(sign)
                     {
                     case '+':
                       res=res+op;
                       lcd_data('=');
		      intTochar(res);
                       break;
                       
                     case '-':
                       res=res-op;
                       lcd_data('=');
                       intTochar(res);
                       break;

                     case '*':
                       res=res*op;
                       lcd_data('=');
                       intTochar(res);
                       break;
                     case '/':
                       if(op==0){
                        error();
                        goto start;}
                       res=res/op;
                       lcd_data('=');
                       intTochar(res);
                       break;
                     }
		 delayMilliSec(500);
                     sign=0;
                     i=0; 
                     z++;
                     op=0;	//zeroing the operand variable again
		  goto start;
                   }
                   else
                   {
                     error();
                     op=0;      
		    goto start;
                   }
        }  
     }
                else if (key == '2'){
                  key=0;
                     clock= TimerValueGet64(TIMER1_BASE);
                     intTochar (clock);
                     }
                else if (key == '3'){
                   key=0;             
                   contact={'h','a','b','i','b','a' ,' ', '0','1','1'};
                   writeContact(key);
                   lcd_data(ReadContact());
                     }
  }
}
}

//show  error message on the lcd
void error(void)
{
	     lcd_Command(1);    
	     lcd_Command(0x80); 
             delayMilliSec(500);
             lcd_data('e');
             lcd_data('r');
             lcd_data('r');
             lcd_data('o');
             lcd_data('r');
             delayMilliSec(1000);
             lcd_Command(1);     
}

//calculate operands
void calculate_operand(uint8_t arr[],uint32_t c)
  {        int t=c;
           int r;
           int g;
           for(x=0;x<=t;x++)
  {   
	   r=c;
	   g=1;      
           while(r>0)
  {
           g=g*10;
           if(r==0)
           break;
           r--;
  }					
          op=op+charToint(arr[x])*g;
          if(c==0)
          break;
          c--;
   }
}


//store first operand then zeroes the op variable again to use the calculate_operand again properly.
void store(uint32_t number)
{
          res=number;    //store the operand in res
          op=0;
}
