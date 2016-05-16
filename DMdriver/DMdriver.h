/*


*/
#ifndef DM_library
#define DM_library

#include "Arduino.h"
#include "DMconfig.h"


#define DM631 24
#define DM632 32
#define DM633 24
#define DM634 32


#define LATpin_D0 0
#define LATpin_D1 1
#define LATpin_D2 2
#define LATpin_D3 3
#define LATpin_D4 4
#define LATpin_D5 5
#define LATpin_D6 6
#define LATpin_D7 7
#define LATpin_D8 8
#define LATpin_D9 9
#define LATpin_D10 10
#define LATpin_D12 12
#define LATpin_A0 A0
#define LATpin_A1 A1
#define LATpin_A2 A2
#define LATpin_A3 A3
#define LATpin_A6 A6
#define LATpin_A7 A7

//#define DM256PWM *pixel[k] // <<8 puts it in 8-bit resolution mode; for 16bit DM chips only
//#define DMLEDTABLE uint8_t // uses look up table; type of data in the table (uint8_t HIGHLY RECOMMENDED!)
//#define DMCHAIN 3 // alternative chain: 0-7, 16-31, 8-15 for 2 chips. Number of chips per segment
                  // if defined with the previous, will be undefined after the lookup table is built

/*** Get LAT low */
#define LAT_low() *LATout &= ~LATbit

/*** LAT pulse - high, low */
#define LAT_pulse() *LATout |= LATbit; *LATout &= ~LATbit

/*** Get LAT high */
#define LAT_high() *LATout |= LATbit


class DMdriver
{
 public:
   DMdriver(uint8_t Driver, uint8_t Number, uint8_t Latch);
   DMLEDTABLE* ledTable; // led lookup table, type defined by DMLEDTABLE
   void init(DMLEDTABLE *table = NULL); // initialise the object and SPI interface  
   void setPoint(uint16_t pixNum, uint16_t pixVal); // sets single LED
   uint16_t getPoint(uint16_t pixNum); // returns the value of a single LED
   void setRGBpoint(uint16_t LED, uint16_t red, uint16_t green, uint16_t blue);
   void setRGBmax(uint16_t LED, uint16_t red, uint16_t green, uint16_t blue, uint16_t max = 0);
   void setRGBled(uint16_t LED, uint16_t red, uint16_t green, uint16_t blue);
   void sendAll(); // send data to the chip
   void clearAll(); // clear all pixels
   void setGlobalBrightness(uint8_t bri); // set overall brightness, DM633 and DM634 only
   void setGBCbyDriver(uint8_t *bri); // set individual Global Brightness Correction for each DM chip
   void turnOff(); // destructor; frees the dynamic memory; use init to start again
   void deallocLedTable(); // free the lookup table memory if not needed
   uint8_t* pixel;  //actual bytes sent to the driver
   
 private: 
   void dm_shift(uint8_t value);
   uint16_t getChainValue (uint16_t pixNum);
   uint8_t LATbit, LATport;
   uint16_t pinNum, byteNum;
   volatile uint8_t *LATreg, *LATout;
   uint8_t DMtype,  DMnum,  LATpin;
   
};

#endif