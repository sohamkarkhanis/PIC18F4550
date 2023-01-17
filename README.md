# PIC18F4550
This is a collection of some of the code that I've written, while working with the PIC18F4550 microcontroller!
I've interfaced a few output and input devices without using user-defined libraries with the PIC18Fxx series.

While writing HIGH or LOW logic on the pins of the microcontroller, I have used the PORT register. This can also be done using the LAT register, and is infact preferred over writing using the PORT register as using PORT-write is not recommended due to the Read-Modify-Write issue. 

RMW is usually an issue with the mid range PIC16 microcontrollers but in my testing I found no issues regarding RMW on my PIC18F4550 DevBoard.
