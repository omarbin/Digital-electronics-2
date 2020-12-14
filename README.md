# :lock: Application of the door lock system :lock:

### Team members
Guillermo Cortés Orellana. ['*Personal repository*'](https://github.com/GuicoRM) :bowtie:

Omar Bin Rahman. ['*Personal repository*'](https://github.com/omarbin) :bowtie:

### Project objectives
Current project it has been designed as final project of the subject **Digital Electronics 2** at Brno University Of Technology.

The main purpose of the project is program security software for door lock system based on Arduino.

System counts with 4 possible passwords made of 4 digits which allows the user to open the door.

Initially, the system's door will stay closed. The user will have to enter her/his personal password in order to open it (as it has been said, there are only 4 possible combinations). If the user enters **correct password**, the door will open and the user can get access to the hall. If on the contrary, the user enters **wrong password**, he/she will have 2 more opportunities (in total 3) to unlock the door. Just in case the user introduces wrong password 3 times in a row, the system will be locked for 5 seconds and the access will be forbidden.

On the other hand, at the moment the user enters first digit of the password, he/she will have **5 seconds** to complete the rest of the password, otherwise, he/she will have to enter again the code.

All the process is divided in several states:

1. **START**

This is the initial state. Door will be close (relay), state LEDs will be off, speaker will be mute and welcome message on LCD screen will be displayed.

2. **Intermediate state**

While user introduces the password.

3. **Final state**

There will be 3 possibilities:

- 3.1 **Counter key < 5" AND correct key**

If the user enters correct password in a period less than 5 seconds since he/she entered first digit, door will be open (relay), green LED will be on, speaker will play simple buzz and the corresponding user's name will be displayed as an identification message on LCD screen for 5 seconds. 

- 3.2 **Counter key > 5" OR incorrect key**

If the user enters incorrect password or he/she spent more than 5 seconds since first digit was introduced, door will remain closed (relay), red LED will be on, speaker will be mute and warning message on LCD screen for 5 seconds will be displayed.

- 3.3 **Incorrect password for 3 times**

If the user enters incorrect password 3  times in a row, door will remain closed (relay), red LED will blink, speaker will be play simple buzz every 1 second for 5 seconds and warning message on LCD screen will also be displayed for 5 seconds.

After final state (any of its variants), system will return to START state.

**Note:** program will never stop due to it is a simulation with learning purposes.

## Hardware description
Door lock system is divided in several hardware modules, such as:

- [x] 1. ATMega328P microcontroller
- [x] 2. Keypad
- [x] 3. Speaker
- [x] 4. Relay
- [x] 5. LCD screen
- [x] 6. LEDs

In the following lines it will be explain different functions of this modules and their relation with complete system:

- **AMega328P microcontroller**

    This module is similar to the microcontroller we have used for the semester. 

    You can find the datasheet ['*on this link*'](http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf).

- **Keypad**

    The main different hardware module we have introduced on this topic is the **keypad**.

    It consists on several push button connected between them by **ROWS** and **COLUMNS**, in our case we have 4 ROWS and 3 COLUMNS.

    It is possible to configure keypad using some libraries by default included in Arduino, but we have programmed our own.
    
    Click here to find our ['*keypad.h*'](https://github.com/omarbin/Digital-electronics-2/blob/master/labs/Final_Project_DE2/Final_Project/Final_Project/keypad.h) and ['*keypad.c*'](https://github.com/omarbin/Digital-electronics-2/blob/master/labs/Final_Project_DE2/Final_Project/Final_Project/keypad.c) libraries.  

    You can find the connection of keypad and how it works ['*on this link*'](https://www.circuitbasics.com/how-to-set-up-a-keypad-on-an-arduino/).

- **Speaker**

    One of the others hardware modules we have introduced on this topic is the **speaker**. Its purpose is plays simple buzz when the user enter the password.
    
    The way we have to get the sound is setting the pin of the speaker as an output and sending high level to play the buzz using ['*gpio.h*'](https://github.com/omarbin/Digital-electronics-2/blob/master/labs/Final_Project_DE2/Final_Project/Final_Project/gpio.h) and ['*gpio.c*'](https://github.com/omarbin/Digital-electronics-2/blob/master/labs/Final_Project_DE2/Final_Project/Final_Project/gpio.c) libraries.   

- **Relay**

    One of the others hardware modules we have introduced on this topic is the **relay**. We will use it to simulate a door.
    
    You can find the connection of relay and how it works ['*on this link*'](https://www.circuitbasics.com/setting-up-a-5v-relay-on-the-arduino/).

- **LCD screen**

    This module is similar to the LCD screen we have used for the semester by using [*lcd_definitions.h*](https://github.com/omarbin/Digital-electronics-2/blob/master/labs/Final_Project_DE2/Final_Project/Final_Project/lcd_definitions.h) and Peter Flurry's libraries: [*lcd.h*](https://github.com/omarbin/Digital-electronics-2/blob/master/labs/Final_Project_DE2/Final_Project/Final_Project/lcd.h) and [*lcd.c*](https://github.com/omarbin/Digital-electronics-2/blob/master/labs/Final_Project_DE2/Final_Project/Final_Project/lcd.c) 

    You can find the explanations on ['*Mr.Fryza's GitHub*'](https://github.com/tomas-fryza/Digital-electronics-2/tree/master/Labs/06-lcd).

- **LEDs**

    This module is similar to the LEDs we have used for the semester. 

    You can find the explanations on ['*Mr.Fryza's GitHub*'](https://github.com/tomas-fryza/Digital-electronics-2/tree/master/Labs/02-leds).

## Code description and simulations
Write your text here.

## Video/Animation
You can find personal video where all the previous features of the system described ['*on this link*'](https://www.youtube.com/watch?v=GhaDPUAOq3g&feature=youtu.be).

## References
1. ['*How keypad works*'](https://arduinogetstarted.com/tutorials/arduino-keypad).

2. ['*How speaker works*'](https://shallowsky.com/arduino/class/buzzer.html#:~:text=A%20%22piezo%20buzzer%22%20is%20basically,the%20crystal%20can%20make%20sound.).

3. ['*How relays works*'](https://maker.pro/arduino/projects/driving-a-relay-with-an-arduino#:~:text=*%20A%20relay%20basically%20allows%20a,off%20a%20higher%20power%20circuit).

