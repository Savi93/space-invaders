# "Embedded" Space Invaders

"Embedded" reinterpretation of the famous arcade game "Space Invaders". 
The firmware was completely developed with Mbed OS (C/C++) and runs at the actual state on an STM32 Nucleo board.
The user is provided with a small N.O. pushbutton for shooting, a resistive joypad for moving the spacecraft along the X-axis and a 1.8'' TFT LCD display (controlled through the SPI interface) for the visualization of the content.
Finally, a small active buzzer has been placed and controlled through a PWM wave, in order to reproduce sounds according to the occurring events (shoot, explosion) and for the startup and end game melodies.
