/******************************************************************************
 Title:    Use IR sensors as analog values to keep a servo centered on an object.
 
 
 Author:   Rue Mohr
 Date:     Mar 2023
 Software: AVR-GCC  
 Hardware: attiny13 @ 1Mhz
 
    

PB0 Motor (PWM 50% = zero) This connects to the DIR pin on your driver.
PB1 
PB2 sensor LEDS
PB3 sensor 2
PB4 sensor 1

PB5 (RESET)   


                            +-----U-----+    
               RESET    PB5 | o         | VCC
               ADC3     PB3 |           | PB2 ADC1 
               ADC2     PB4 |   Tiny13  | PB1 OC0B
                        GND |           | PB0 OC0A
                            +-----------+    





    
*******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "avrcommon.h"
#include "stdint.h"
 
#define OUTPUT                   1
#define INPUT                    0

void ADCinit(void) ;


volatile uint8_t IntFlag;

volatile uint16_t level1L;
volatile uint16_t level1H;
volatile uint16_t level2L;
volatile uint16_t level2H;

void PCIInit( void ) ;
void PWMInit( void ) ;

  #define LED              2
  
  #define LEDOn()          SetBit(LED, PORTB)
  #define LEDOff()         ClearBit(LED, PORTB)                       
  
  void presend8 (unsigned int bits) ;
  void send8 (unsigned int bits);
  


int main (void)  {
  int16_t D1, D2;
  int16_t delta;
  
  // Set clock prescaler: 0 gives full 9.6 MHz from internal oscillator.
  CLKPR = (1 << CLKPCE);
  CLKPR = 0;  
         
  DDRB = (OUTPUT << DDB0 | INPUT << DDB1 | OUTPUT << DDB2 | INPUT << DDB3 | INPUT << DDB4 | INPUT << DDB5 ); 
  
  PWMInit() ;
  ADCinit() ;
  
  sei();         // turn on interrupts      
                   
  while(1) {
                 
   while(IntFlag == 0); // wait for new data      
   IntFlag = 0;
   
   if ((level1H > level1L) && (level2H > level2L)) { // sane?
     D1 = (level1H - level1L);           
     D2 = (level2H - level2L);
     
     delta = D1 - D2;
     delta /= 3;            // gain
     delta += 128;          // 50% = 0 speed
     
     limit(delta, 0, 255);  // who is rolling over!?! }:/  
     
     OCR0A = delta;
   }
             
  }
}

    
//------------------------| FUNCTIONS |------------------------




#define rate 94 

// set to 60Hz (noise cancel, maybe 50Hz where you are?)

ISR(  ADC_vect) {     
  static uint16_t countdown = 100;
  
  countdown--;
  
  if (0) {
  } else if (countdown == 0)               { LEDOn(); countdown = rate; ADMUX  =  2;      // reset count, LED ON  
  } else if (countdown == ((rate*2)/3)+1)  { level1L = ADC;             ADMUX  =  3;
  } else if (countdown == ((rate*2)/3))    { level2L = ADC;             
  } else if (countdown == (rate/2))        { LEDOff();                  ADMUX  =  2;      // LED OFF      
  } else if (countdown == (rate/3)+1)      { level1H  = ADC;            ADMUX  =  3;  
  } else if (countdown == (rate/3))        { level2H  = ADC; IntFlag = 1;     
  }     
  
  ADCSRA |= (1 << ADSC) ;
}



void ADCinit(void) {
 
 // ADC, 9.6Mhz / 128
  ADMUX  = ( 2 << MUX0 ); //ADC2 on PB4 pin 7
  ADCSRA = ( (1 << ADEN) | (1 << ADIF) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) ) ;
  ADCSRA |= (1 << ADSC) ;
 
}




void PWMInit() {
  // clear pwm levels
  OCR0A = 32; 
  
  // set up WGM, clock, and mode for timer 0
  TCCR0A = 1 << COM0A1 | 
           0 << COM0A0 | 
           1 << WGM00  |
           1 << WGM01  ;
  
  // set up WGM, clock, and mode for timer 2
  // 9.6 MHz  / 8 = 4.7kHz
  TCCR0B = 0 << CS02  |
           1 << CS01  |
           0 << CS00  ;
  
 }













































