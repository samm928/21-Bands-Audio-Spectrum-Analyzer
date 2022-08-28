/********************************************************************************************************************************
*
*  Project:         21 Band Spectrum Analyzer
*  Target Platform: Arduino Mega2560 or Mega2560 PRO MINI
*  
*  Version: 4.0
*  Hardware setup: https://github.com/donnersm/14ChannelAnalyzerV2.0/tree/main/Documentation
*  Spectrum analyses done with analog chips MSGEQ7
*  
*  Mark Donners
*  The Electronic Engineer
*  Website:   www.theelectronicengineer.nl
*  facebook:  https://www.facebook.com/TheelectronicEngineer
*  youtube:   https://www.youtube.com/channel/UCm5wy-2RoXGjG2F9wpDFF3w
*  github:    https://github.com/donnersm
*  
********************************************************************************************************************************/

#pragma once
char version[]="4.0";                               // Define version number for reference only

// Debugging
#define DEBUG_BUFFER_SIZE 100                       // Debug buffer size
int  DEBUG = 1;                                     // When debug=1, extra information is printed to serial port. Turn of if not needed--> DEBUG=0

// Ledstrip Logo
#define LOGO_PIN         10                         // second ledstrip for logo.
#define NUM_LEDS_LOGO    10                         // how many leds on your logo. You can define more leds then connected, that will result in wider gradient.

// Ledstrips/ matrix main display  **************************************************************************************
#define LED_PIN           9                         // This is the data pin of your led matrix, or ledstrips.
#define COLUMNS          21                         // Number of bands on display, this is not the same as display width...because display can be 28 ( double pixels per bar)

//const uint8_t                                     // if you have more then 16 bands, you will need to change the Led Matrix Arrays in the main file.
#define kMatrixWidth     21                         // Matrix width --> number of columns in your led matrix
#define kMatrixHeight    16                         // Matrix height --> number of leds per column   

// Some definitions for setting up the matrix  **************************************************************************
#define BAR_WIDTH         1
//#define BAR_WIDTH  (kMatrixWidth / (COLUMNS -1))  // If width >= 8 light 1 LED width per bar, >= 16 light 2 LEDs width bar etc
#define TOP        (kMatrixHeight - 0)              // Don't allow the bars to go offscreen
#define NUM_LEDS   (kMatrixWidth * kMatrixHeight)   // Total number of LEDs in the display array

// Ledstrips or pixelmatrix  +*******************************************************************************************
#define CHIPSET      WS2812B                        // LED strip type -> Same for both ledstrip outputs( Matrix and logo)
#define BRIGHTNESSMAX     50                        // Max brightness of the leds...carefull...to bright might draw to much amps!
#define COLOR_ORDER      GRB                        // If colours look wrong, play with this
#define LED_VOLTS          5                        // Usually 5 or 12
#define MAX_MILLIAMPS   2000                        // Careful with the amount of power here if running off USB port, This will effect your brightnessmax. Currentlimit overrules it.
                                                    // If your power supply or usb can not handle the set current, arduino will freeze due to power drops.
// ADC Filter  **********************************************************************************************************
#define NOISE             20                        // Used as a crude noise filter on the adc input, values below this are ignored

//Controls  *************************************************************************************************************
#define PEAKDELAYPOT      A3                        // Potmeter for sensitivity input 0...5V (0-3.3V on ESP32)
#define SENSITIVITYPOT    A4                        // Potmeter for Brightness input 0...5V (0-3.3V on ESP32)  
#define BRIGHTNESSPOT     A5                        // Potmeter for Peak Delay Time input 0...5V (0-3.3V on ESP32)
#define Switch1          A10                        // Connect a push button to this pin to change patterns
#define LONG_PRESS_MS   3000                        // Number of ms to count as a long press on the switch

// MSGEQ7 Pinout Connections  ******************************************************************************************
#define STROBE_PIN        6                         //MSGEQ7 strobe pin
#define RESET_PIN         7                         //MSGEQ7 reset pin

int BRIGHTNESSMARK =    100;                        // Default brightnetss, however, overruled by the Brightness potmeter
int AMPLITUDE      =   2000;                        // Depending on your audio source level, you may need to alter this value. it's controlled by the Sensitivity Potmeter

// Peak related stuff
#define Fallingspeed     30                         // This is the time it takes for peak tiels to fall to stack, this is not the extra time that you can add by using the potmeter
                                                    // for peakdelay. Because that is the extra time it levitates before falling to the stack    
#define AutoChangetime   10                         // If the time  in seconds between modes, when the patterns change automatically, if to fast, you can increase this number            

CRGB leds[NUM_LEDS];                                // Leds on the Ledstrips/Matrix of the actual Spectrum analyzer lights.
CRGB LogoLeds[NUM_LEDS_LOGO];                       // Leds on the ledstrip for the logo

#define NumberOfModes    13                         // The number of modes, remember it starts counting at 0,so if your last mode is 11 then the total number of modes is 12
#define DefaultMode       1                         // This is the mode it will start with after a reset or boot
#define DemoAfterSec   6000                         // if there is no input signal during this number of seconds, the unit will go to demo mode
#define DemoTreshold     10                         // this defines the treshold that will get the unit out of demo mode

/****************************************************************************
 * Colors of bars and peaks in different modes, changeable to your likings  *
 ****************************************************************************/

// Colors mode 0 *************************************************************
#define ChangingBar_Color   y * (255 / kMatrixHeight) + colorTimer, 255, 255
// no peaks

// Colors MODE 1 These are the colors from the TRIBAR ************************
#define TriBar_Color_Top            5, 255, 255
#define TriBar_Color_Middle        30, 255, 255
#define TriBar_Color_Bottom        65, 255, 255

#define TriBar_Color_Top_Peak       0, 255, 255
#define TriBar_Color_Middle_Peak   20, 255, 255
#define TriBar_Color_Bottom_Peak   95, 255, 255

// Colors MODE 2 Static horizontal Rainbow ***********************************
#define RainbowBar_Color  (x / BAR_WIDTH) * (255 / COLUMNS), 255, 255
#define PeakColor1  220, 150, 255              // Purple peaks

// Colors MODE 3 *************************************************************
#define PeakColor2  130,  30, 255              // White peaks
DEFINE_GRADIENT_PALETTE( purple_gp ) {
    0,   2,  1,  1,
   53,  18,  1,  0,
  104,  69, 29,  1,
  153, 167,135, 10,
  255,  46, 56,  4};
CRGBPalette16 purplePal = purple_gp;

// Colors mode 4 *************************************************************
#define SameBar_Color1    185, 235, 235
#define PeakColor3        240, 245, 255       // Hot Pink peaks

// Colors mode 5 *************************************************************
#define SameBar_Color2   110, 245, 160
#define PeakColor4       255, 190, 225        // Red peaks

// Colors mode 6 *************************************************************
DEFINE_GRADIENT_PALETTE( redyellow_gp ) {  
  0,   0,   0, 255,
 64, 255, 218,   0,
128, 231,   0,   0,
192, 255, 218,   0,
255,   0,   0,   0 };
CRGBPalette16 heatPal = redyellow_gp;
// no peaks

// Colors mode 7 *************************************************************
DEFINE_GRADIENT_PALETTE( Outrun_gp ) {
    0,  47, 30,  2,
   42, 213,147, 24,
   84, 103,219, 52,
  127,   3,219,207,
  170,   1, 48,214,
  212,   1,  1,111,
  255,   1,  7, 33};
CRGBPalette16 outrunPal = Outrun_gp;
// no peaks

// Colors mode 8a ************************************************************
DEFINE_GRADIENT_PALETTE( dan_gp ) {
    0,  10, 85,  5,
   25,  29,109, 18,
   60,  59,138, 42,
   93,  83, 99, 52,
  106, 110, 66, 64,
  109, 123, 49, 65,
  113, 139, 35, 66,
  116, 192,117, 98,
  124, 255,255,137,
  168, 100,180,155,
  255,  22,121,174};
CRGBPalette16 danPal = dan_gp;

// Colors mode 8b ***********************************************************
DEFINE_GRADIENT_PALETTE( Lava_gp ) {
    0,   0,  0,  0,
   46,  18,  0,  0,
   96, 113,  0,  0,
  108, 142,  3,  1,
  119, 175, 17,  1,
  146, 213, 44,  2,
  174, 255, 82,  4,
  188, 255,115,  4,
  202, 255,156,  4,
  218, 255,203,  4,
  234, 255,255,  4,
  244, 255,255, 71,
  255, 255,255,255};
CRGBPalette16 danPal1 = Lava_gp;

// Colors mode 8c ******************************************************
DEFINE_GRADIENT_PALETTE( Sunset_Real_gp ) {
    0, 120,  0,  0,
   22, 179, 22,  0,
   51, 255,104,  0,
   85, 167, 22, 18,
  135, 100,  0,103,
  198,  16,  0,130,
  255,   0,  0,160};
CRGBPalette16 danPal2 = Sunset_Real_gp;

// Colors mode 8c
DEFINE_GRADIENT_PALETTE( ib15_gp ) {
    0, 113, 91,147,
   72, 157, 88, 78,
   89, 208, 85, 33,
  107, 255, 29, 11,
  141, 137, 31, 39,
  255,  59, 33, 89};
CRGBPalette16 danPal3 = ib15_gp;

// Colors mode 8d ********************************************************
DEFINE_GRADIENT_PALETTE( es_ocean_breeze_068_gp ) {
    0, 100,156,153,
   51,   1, 99,137,
  101,   1, 68, 84,
  104,  35,142,168,
  178,   0, 63,117,
  255,   1, 10, 10};
CRGBPalette16 danPal4 = es_ocean_breeze_068_gp;

// Colors mode 10 ********************************************************
// no bars only peaks
#define PeakColor5  160, 255, 255   // blue CHSV

// These are the colors from the TRIPEAK mode 11
// no bars only peaks
#define TriBar_Color_Top_Peak2      0, 255, 255
#define TriBar_Color_Bottom_Peak2  95, 255, 255
#define TriBar_Color_Middle_Peak2  45, 255, 255

/******************************************************************
* Setting below are only related to the demo Fire mode            *
*******************************************************************/


#define FPS 15              /* Refresh rate 15 looks good*/

//Flare constants
const uint8_t flarerows =   10;  //2  /* number of rows (from bottom) allowed to flare */
const uint8_t maxflare =     5;  //8  /* max number of simultaneous flares */
const uint8_t flarechance = 50;       /* chance (%) of a new flare (if there's room) */
const uint8_t flaredecay =  14;       /* decay rate of flare radiation; 14 is good */

// This is the map of colors from coolest (black) to hottest. Want blue flames? Go for it ! 
const uint32_t colors[] = {
  0x000000,
  0x100000,
  0x300000,
  0x600000,
  0x800000,
  0xA00000,
  0xC02000,
  0xC04000,
  0xC06000,
  0xC08000,
  0x807080
};
