# 21-Bands-Audio-Spectrum-Analyzer
Built with Arduino Mega2560 Pro
The hardware is been tested on a a bread-board and later on a revision 1.0 that was using an LM338 regulator.
Regulator that was getting too hot and has been replaced by an LX4015 and later by a Mini560 DC-DC 5v buck converter.
The 420 LEDs on the panel can be powerd up by the USB supply from the Mega if Brightness is set to 20 in the Sketch Settings.h
The original code is from Mark Donners from Netherlands who deservers the credits for setting up the nice flow in the code.
The code and hardware have been modified to allow adding an extra 7-frequency bands in the 40Hz 16Khz spectrum. I was not 
able to use the Si5351mcu.h Library created and optimized by Pavel Milanes. It would not allow Clk1 and Clk2 to be used simultaneously, 
therefore to make the jump form 14 bands to 21 bands I used the generic Si5351.g library from IDE. Other changes to the code include 
incerasing the ADC filter setting 'NOISE' from 120 to 180 and adding more Color Mode and Patterns includin Gradiant wave patterns from '
kriegsman/ColorWavesWithPalettes.ino' who also deserves thanks. Clk1 and Clk2 frequency was derived from Clk0 as the base (F1 = F0 x 1.3572 and F2 = F0 x 1.3572^2).
