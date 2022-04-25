## STM32F407 - HAL API project

Design of microprocessor systems / Faculty of Electrical Engineering (University in Tuzla)

## Specification

### Equipment:

1. STM32F407VG Discovery borad
2. Battery -> 9 [V]
3. Water lelvel sensors (2x or 4x)
4. Servo motor SG90 (2x) -> for valve simulation
5. DC motor
6. relay (better transistor control)
7. Potentiometer 10k (2x)
8. LCD 1602

### Functionality

The system consists of two tanks and a bowl for mixing liquids. First, we will check if there is liquid in the tanks, if there is liquid, we will enter the while loop, and if there is not, the code will not be executed (this part of the program is not currently implemented). When we find that we have liquid in the tanks, the first valve will open (the first servo motor starts) while the second valve remains closed. When the water in the mixing bowl reaches the first level (the first flag is changed), the first valve closes (we return the first servo motor to the initial position) and the second valve opens (we start the second servo motor). We will now wait for the water in the bowl to reach the second level. When the water reaches the second level (the second flag changes) the second valve closes. Now we have enough liquid in the bowl and mixing is possible. Pressing the button on the board triggers the relay and starts the motor connected to external power (9 V battery). The DC motor is running while we hold the button. When we release the button
the DC motor stops moving, ie. mixing is stopped.
