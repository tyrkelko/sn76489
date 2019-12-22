This is an SN76489 C++ library for Arduino 0004+ by Kobi Tyrkel, based on one created by 
Nicholas Zambetti for Wiring 0006+

Hardware Setup
--------------------------------------------------------------------------------

To use this library you will need SN76489 sound chip with an oscillator of up to 4MHz. An amplifier and speaker would be handy too.

/***************************************************************************
***** Directly interface SN76489 IC with the following PIN definitions *****
***** and by calling 8-bit constractor                                 *****
***** The SN76489 pinout considered for this library is as follows:    *****
*****                                                                  *****
*****                        ========                                  *****
*****        D2       --> [ 1]  ()  [16] <-- VCC                       *****
*****        D1       --> [ 2]      [15] <-- D3                        *****
*****        D0       --> [ 3]  7   [14] <-- CLOCK OSC                 *****
*****     READY       <-- [ 4]  6   [13] <-- D4                        *****
*****    NOT WE       --> [ 5]  4   [12] <-- D5                        *****
*****    NOT CE       --> [ 6]  8   [11] <-- D6                        *****
***** AUDIO OUT       <-- [ 7]  9   [10] <-- D7                        *****
*****       GND       --> [ 8]      [ 9] --- N.C.                      *****
*****                        ========                                  *****
***************************************************************************/

You can optionaly use a 75HC595 or similar Shift Register to interface with the sound chip and use less i/o pins on Arduino

/***************************************************************************
***** Interface SN76489 IC with 595 Shift Register and PIN definitions *****
***** and by calling 3 PIN constractor                                 *****
***** 595 Shift Register pins connection with SN76489 is as follows:   *****
*****                                                                  *****
*****                        ========                                  *****
*****       D6 <-- Q1 <-- [ 1]  ()  [16] <-- VCC                       *****
*****       D5 <-- Q2 <-- [ 2]      [15] --> Q0     --> D7             *****
*****       D4 <-- Q3 <-- [ 3]  5   [14] <-- SER    <-- PIN_SER        *****
*****       D3 <-- Q4 <-- [ 4]  9   [13] <-- Not CE <-- GND            *****
*****       D2 <-- Q5 <-- [ 5]  5   [12] <-- CLOCK  <-- PIN_CLK        *****
*****       D1 <-- Q6 <-- [ 6]      [11] <-- LATCH  <-- PIN_LATCH      *****
*****       D0 <-- Q7 <-- [ 7]      [10] <-- Not MR <-- VCC            *****
*****             GND --> [ 8]      [ 9] --- Q7'    --- Not used       *****
*****                        ========                                  *****
***************************************************************************/

Installation
--------------------------------------------------------------------------------

To install this library, just place this entire folder as a subfolder in your
Arduino/lib/targets/libraries folder.

When installed, this library should look like:

Arduino/lib/targets/libraries/SN76489              (this library's folder)
Arduino/lib/targets/libraries/SN76489/SN76489.cpp     (the library implementation file)
Arduino/lib/targets/libraries/SN76489/SN76489.h       (the library description file)
Arduino/lib/targets/libraries/SN76489/keywords.txt (the syntax coloring file)
Arduino/lib/targets/libraries/SN76489/examples     (the examples in the "open" menu)
Arduino/lib/targets/libraries/SN76489/readme.txt   (this file)

Building
--------------------------------------------------------------------------------

After this library is installed, you just have to start the Arduino application.
You may see a few warning messages as it's built.

To use this library in a sketch, go to the Sketch | Import Library menu and
select Test.  This will add a corresponding line to the top of your sketch:
#include <SN76489.h>

To stop using this library, delete that line from your sketch.

Geeky information:
After a successful build of this library, a new file named "SN76489.o" will appear
in "Arduino/lib/targets/libraries/SN76489". This file is the built/compiled library
code.

If you choose to modify the code for this library (i.e. "SN76489.cpp" or "SN76489.h"),
then you must first 'unbuild' this library by deleting the "SN76489.o" file. The
new "SN76489.o" with your code will appear after the next press of "verify"

