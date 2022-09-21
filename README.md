Improved SparkFun AutoDriver Arduino Library
==========
[![AutoDriver](https://dlnmh9ip6v2uc.cloudfront.net/images/products/1/1/6/1/1/11611-01_medium.jpg)  
*AutoDriver (BOB-13752)*](https://www.sparkfun.com/products/13752)

The AutoDriver is a bipolar stepper driver based on the ST Micro L6470 chip.
It allows a processor to control a single 3A bipolar stepper motor across an 8-45V supply range.

This library was originally developed by the awesome folks at SparkFun, and their code can be found here: [SparkFun Autodriver Arduino Library](https://github.com/sparkfun/SparkFun_AutoDriver_Arduino_Library) Unfortunately, SparkFun's hookup guide makes a couple of errors and omissions that make it very easy for novice users (read -- their user base, including me) to burn up these fairly expensive stepper drivers. In an effort to both address these deficiencies and also expose more of the AutoDriver's substantial functionality, I've forked this 

Repository Contents
-------------------
* **src** - Contains the source for the Arduino library.
* **Examples** - Example sketches demonstrating the use of the library
* **keywords.txt** - List of words to be highlighted by the Arduino IDE
* **library.properties** - Used by the Arduino package manager

Documentation
-------------------
* **[Installing an Arduino Library Guide](https://learn.sparkfun.com/tutorials/installing-an-arduino-library)** - Basic information on how to install an Arduino library.
* **[Product Repository](https://github.com/sparkfun/L6470-AutoDriver)** - Main repository (including hardware files) for the AutoDriver board.
* **[STM Datasheet for L6470 Driver](https://www.st.com/resource/en/application_note/an4144-voltage-mode-control-operation-and-parameter-optimization-stmicroelectronics.pdf) - More in-depth documentation of the L6470, including the various registers that this library can access.
* **[STM App Note on tuning the L6470 for different motors](https://www.st.com/resource/en/application_note/an4144-voltage-mode-control-operation-and-parameter-optimization-stmicroelectronics.pdf) - Critical reading! Describes how the L6470's control technique works, and how it requires additional information about your motor's electrical parameters to work well - and why your motor may not be turning if your KVAL values aren't set correctly (they're not just gains!)
* **[Hookup Guide]()** - TO UPDATE. SparkFun's hookup guide is really hard to follow - will upload a better diagram later.

Version History
-------------------

License Information
-------------------
This product is open source! 
The code is beerware; if you see me (or any other SparkFun employee) at the local, and you've found our code helpful, please buy us a round!
Please use, reuse, and modify these files as you see fit. Please maintain attribution to SparkFun Electronics and release anything derivative under the same license.

Distributed as-is; no warranty is given.

