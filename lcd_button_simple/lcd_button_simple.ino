/*                                                                        /*
      1/27/2015
      I copied this sketch from http://linksprite.com/wiki/index.php5?title=16_X_2_LCD_Keypad_Shield_for_Arduino
      Use it to test your Arduino and LCD keypad
      Make sure all buttons work!
      Kevin
*/


/*
 
  This example code is in the public domain.
 
  ---------------------------------------------------------------------
 
  This program demonstrates button detection, LCD text/number printing,
  and LCD backlight control on the Freetronics LCD & Keypad Shield, connected to an Arduino board.
 
 
  Pins used by LCD & Keypad Shield:
 
    A0: Buttons, analog input from voltage ladder
    D4: LCD bit 4
    D5: LCD bit 5
    D6: LCD bit 6
    D7: LCD bit 7
    D8: LCD RS
    D9: LCD E
    D10: LCD Backlight (high = on, also has pullup high so default is on)
 
  ADC voltages for the 5 buttons on analog input pin A0:
 
    RIGHT:  0.00V :   0 @ 8bit ;   0 @ 10 bit
    UP:     0.71V :  36 @ 8bit ; 145 @ 10 bit
    DOWN:   1.61V :  82 @ 8bit ; 329 @ 10 bit
    LEFT:   2.47V : 126 @ 8bit ; 505 @ 10 bit
    SELECT: 3.62V : 185 @ 8bit ; 741 @ 10 bit
*/
/*--------------------------------------------------------------------------------------
  Includes
--------------------------------------------------------------------------------------*/
#include <LiquidCrystal.h>   // include LCD library
#include <limits.h>



//#define OLD_LCD_SHIELD
#define DEBUG 1
/*--------------------------------------------------------------------------------------
  Defines
--------------------------------------------------------------------------------------*/
// Pins in use
#define BUTTON_ADC_PIN           A0  // A0 is the button ADC input
#define LCD_BACKLIGHT_PIN         10  // D10 controls LCD backlight

#ifndef OLD_LCD_SHIELD
// ADC readings expected for the 5 buttons on the ADC input
#define RIGHT_10BIT_ADC         814  // right
#define UP_10BIT_ADC            931  // up
#define DOWN_10BIT_ADC          903  // down
#define LEFT_10BIT_ADC          856  // left
#define SELECT_10BIT_ADC        614  // right
#else
#define RIGHT_10BIT_ADC           0  // right
#define UP_10BIT_ADC            145  // up
#define DOWN_10BIT_ADC          329  // down
#define LEFT_10BIT_ADC          505  // left
#define SELECT_10BIT_ADC        741  // right
#endif
#define BUTTONHYSTERESIS         10  // hysteresis for valid button sensing window
//return values for ReadButtons()
#define BUTTON_NONE               0  // 
#define BUTTON_RIGHT              1  // 
#define BUTTON_UP                 2  // 
#define BUTTON_DOWN               3  // 
#define BUTTON_LEFT               4  // 
#define BUTTON_SELECT             5  // 
//some example macros with friendly labels for LCD backlight/pin control, tested and can be swapped into the example code as you like
#define LCD_BACKLIGHT_OFF()     digitalWrite( LCD_BACKLIGHT_PIN, LOW )
#define LCD_BACKLIGHT_ON()      digitalWrite( LCD_BACKLIGHT_PIN, HIGH )
#define LCD_BACKLIGHT(state)    { if( state ){digitalWrite( LCD_BACKLIGHT_PIN, HIGH );}else{digitalWrite( LCD_BACKLIGHT_PIN, LOW );} }
/*--------------------------------------------------------------------------------------
  Variables
--------------------------------------------------------------------------------------*/
byte buttonJustPressed  = false;         //this will be true after a ReadButtons() call if triggered
byte buttonJustReleased = false;         //this will be true after a ReadButtons() call if triggered
byte buttonWas          = BUTTON_NONE;   //used by ReadButtons() for detection of button events




/*--------------------------------------------------------------------------------------
  Init the LCD library with the LCD pins to be used
--------------------------------------------------------------------------------------*/
LiquidCrystal lcd( 8, 9, 4, 5, 6, 7 );   //Pins for the freetronics 16x2 LCD shield. LCD: ( RS, E, LCD-D4, LCD-D5, LCD-D6, LCD-D7 )
/*--------------------------------------------------------------------------------------
  setup()
  Called by the Arduino framework once, before the main loop begins
--------------------------------------------------------------------------------------*/


void setup()
{
   //button adc input
   pinMode( BUTTON_ADC_PIN, INPUT );         //ensure A0 is an input
   digitalWrite( BUTTON_ADC_PIN, LOW );      //ensure pullup is off on A0
   //lcd backlight control
   digitalWrite( LCD_BACKLIGHT_PIN, LOW );  //backlight control pin D3 is high (on)
   pinMode( LCD_BACKLIGHT_PIN, OUTPUT );     //D3 is an output
   //set up the LCD number of columns and rows: 
   lcd.begin( 16, 2 );
   //Print some initial text to the LCD.
   lcd.setCursor( 0, 0 );   //left top
   //          1234567890123456
   lcd.print( "Kevin Lee  16x2" );
   //
   lcd.setCursor( 0, 1 );   //left bottom
   //          1234567890123456
   lcd.print( "Btn:" );
   


  Serial.begin(9600);
  

  digitalWrite( LCD_BACKLIGHT_PIN, HIGH );

  
 }//setup
/*--------------------------------------------------------------------------------------
  loop()
  Arduino main loop
--------------------------------------------------------------------------------------*/


void loop()
{
   byte button;
 
   //get the latest button pressed, also the buttonJustPressed, buttonJustReleased flags
   button = ReadButtons();
   //blank the demo text line if a new button is pressed or released, ready for a new label to be written
   if( buttonJustPressed || buttonJustReleased )
   {
     lcd.setCursor( 4, 1 );
     lcd.print( "            " );
   }
   //show text label for the button pressed
   switch( button )
   {

      case BUTTON_NONE:
      {
         break;
      }
      case BUTTON_RIGHT:
      {
        lcd.setCursor( 4, 1 );
        lcd.print( "Right" ); 
         break;
      }
      case BUTTON_UP:
      {
         lcd.setCursor( 4, 1 );
        lcd.print( "Up" ); 
       
         break;
      }
      case BUTTON_DOWN:
      {
        lcd.setCursor( 4, 1 );
        lcd.print( "Down" ); 
        
         break;
      }
      case BUTTON_LEFT:
      {
          lcd.setCursor( 4, 1 );
        lcd.print( "Left" ); 
         break;
     }
     case BUTTON_SELECT:
     {
        lcd.setCursor( 4, 1 );
        lcd.print( "SELECT-FLASH" );    
 
        //SELECT is a special case, it pulses the LCD backlight off and on for demo
        digitalWrite( LCD_BACKLIGHT_PIN, HIGH );
        delay( 150 );
        digitalWrite( LCD_BACKLIGHT_PIN, LOW
        );   //leave the backlight on at exit
        delay( 150 );
 
        /* an example of LCD backlight control via macros with nice labels
        LCD_BACKLIGHT_OFF();
        delay( 150 );
        LCD_BACKLIGHT_ON();   //leave the backlight on at exit
        delay( 150 );
        */
 
        /*
        // an example of LCD backlight control via a macro with nice label, called with a value
        LCD_BACKLIGHT(false);
        delay( 150 );
        LCD_BACKLIGHT(true);   //leave the backlight on at exit
        delay( 150 );
        */
 
        break;
      }
      default:
     {
        break;
     }
   }



   
     //clear the buttonJustPressed or buttonJustReleased flags, they've already done their job now.
   if( buttonJustPressed )
      buttonJustPressed = false;
   if( buttonJustReleased )
      buttonJustReleased = false;


    
}//loop

/*--------------------------------------------------------------------------------------
  ReadButtons()
  Detect the button pressed and return the value
  Uses global values buttonWas, buttonJustPressed, buttonJustReleased.
--------------------------------------------------------------------------------------*/
byte ReadButtons()
{
    int buttonVoltage;
   byte button = BUTTON_NONE;   // return no button pressed if the below checks don't write to btn

   static int oldVoltage = 0;
   
   //read the button ADC pin voltage
   buttonVoltage = analogRead( BUTTON_ADC_PIN );
  if (DEBUG && oldVoltage != buttonVoltage){
        Serial.println(buttonVoltage);
        oldVoltage = buttonVoltage;
  }
  
   //sense if the voltage falls within valid voltage windows
   if( buttonVoltage >= ( RIGHT_10BIT_ADC - BUTTONHYSTERESIS ) 
    && buttonVoltage <= ( RIGHT_10BIT_ADC + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_RIGHT;
   }
   else if(   buttonVoltage >= ( UP_10BIT_ADC - BUTTONHYSTERESIS )
           && buttonVoltage <= ( UP_10BIT_ADC + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_UP;
   }
   else if(   buttonVoltage >= ( DOWN_10BIT_ADC - BUTTONHYSTERESIS )
           && buttonVoltage <= ( DOWN_10BIT_ADC + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_DOWN;
   }
   else if(   buttonVoltage >= ( LEFT_10BIT_ADC - BUTTONHYSTERESIS )
           && buttonVoltage <= ( LEFT_10BIT_ADC + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_LEFT;
   }
   else if(   buttonVoltage >= ( SELECT_10BIT_ADC - BUTTONHYSTERESIS )
           && buttonVoltage <= ( SELECT_10BIT_ADC + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_SELECT;
   }
   //handle button flags for just pressed and just released events
   if( ( buttonWas == BUTTON_NONE ) && ( button != BUTTON_NONE ) )
   {
      //the button was just pressed, set buttonJustPressed, this can optionally be used to trigger a once-off action for a button press event
      //it's the duty of the receiver to clear these flags if it wants to detect a new button change event
      buttonJustPressed  = true;
      buttonJustReleased = false;
   }
   if( ( buttonWas != BUTTON_NONE ) && ( button == BUTTON_NONE ) )
   {
      buttonJustPressed  = false;
      buttonJustReleased = true;
   }
 
   //save the latest button value, for change event detection next time round
   buttonWas = button;
 
   return( button );
}







