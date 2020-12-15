# :lock: Application of the door lock system :lock:

### Team members
Guillermo Cortés Orellana. [*Personal repository*](https://github.com/GuicoRM) :bowtie:

Omar Bin Rahman. [*Personal repository*](https://github.com/omarbin/Digital-electronics-2) :bowtie:

### Project objectives
Final project of the subject **Digital Electronics 2** at Brno University Of Technology.

The main purpose of the project is to program security software for door lock system based on Arduino.

System counts with 4 possible passwords made of 4 digits which allows the user to open the door when password is typed correctly.

Initially, the system's door will stay closed. The user will have to enter her/his personal password in order to open it (as it has been said, there are only 4 possible combinations). If the user enters **correct password**, the door will open and the user can access to the hall. If on the contrary, the user enters **wrong password**, he/she will have 2 more opportunities (in total 3) to unlock the door. Just in case the user introduces wrong password 3 times in a row, the system will be locked temporarily and the access will be denied.

On the other hand, at the moment the user enters first digit of the password, he/she will have **5 seconds** to complete the rest of the password, otherwise, the system will reset and he/she will have to enter the code again.

The following image shows circuit of the system:

![Captura](https://user-images.githubusercontent.com/71753644/102131928-39ed6900-3e53-11eb-89f6-758fdda11748.PNG)

All the process is divided in several states:

1. **START**

This is the initial state. Door will be closed (relay), state LEDs will be off, speaker will be mute and welcome message on LCD screen will be displayed.

![Captura](https://user-images.githubusercontent.com/71753644/102140762-0b29bf80-3e60-11eb-9cc1-5cc54c87a2e5.PNG)

2. **Intermediate state**

While user introduces the password.

![Captura](https://user-images.githubusercontent.com/71753644/102140881-3b715e00-3e60-11eb-9316-0371a080b5bd.PNG)

3. **Final state**

There will be 3 possibilities:

- 3.1 **Counter password < 5" AND correct password**

If the user enters correct password in a period less than 5 seconds since he/she entered first digit, door will be open (relay), green LED will be on, speaker will play simple buzz when door opens and buzz again when door closes. Welcome message on LCD screen for 5 seconds will be displayed for the corresponding password.

![Captura](https://user-images.githubusercontent.com/71753644/102140972-622f9480-3e60-11eb-9ef1-32ad64f6852f.PNG)

- 3.2 **Counter password > 5" OR wrong password**

If the user enters wrong password or he/she spent more than 5 seconds since first digit was pressed, the door will remain closed (relay), red LED will be on, speaker will be mute, warning message on LCD screen for 5 seconds will be displayed and system will reset to START state.

If counter password > 5 seconds:

![Captura](https://user-images.githubusercontent.com/71753644/102141987-fb12df80-3e61-11eb-852d-e675332aceb1.PNG)

If wrong password:

![Captura](https://user-images.githubusercontent.com/71753644/102141102-9440f680-3e60-11eb-8dd5-12b048a79b72.PNG)

- 3.3 **Wrong password for 3 times**

If the user enters incorrect password 3 times in a row, door will remain closed (relay), red LED will blink every second, speaker will be play simple buzz every second and warning message on LCD screen for 5 seconds will be displayed. 

![Captura](https://user-images.githubusercontent.com/71753644/102141208-bf2b4a80-3e60-11eb-90c2-58dedaf274cd.PNG)

After final state (any of its variants), system will return to START state.

**Note:** program will never stop due to it is a simulation with learning purposes.

The following state diagram shows different states of the system:

![Captura](https://user-images.githubusercontent.com/71753644/102142331-7e343580-3e62-11eb-915e-22efe96c859c.PNG)

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

    You can find the datasheet [*on this link*](http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf).

- **Keypad**

    The main different hardware module we have introduced on this topic is the **keypad**.

    It consists on several push button connected between them by **ROWS** and **COLUMNS**, in our case we have 4 ROWS and 3 COLUMNS.

    It is possible to configure keypad using some libraries by default included in Arduino, but we have programmed our own: `keypad.c`. 

    You can find the connection of keypad and how it works [*on this link*](https://www.circuitbasics.com/how-to-set-up-a-keypad-on-an-arduino/).

- **Speaker**

    One of the others hardware modules we have introduced on this topic is the **speaker**. Its purpose is plays simple buzz when the user enters the password.
    
    The way we have to get the sound is setting the pin of the speaker as an output and sending high level to play the buzz. 

- **Relay**

    One of the others hardware modules we have introduced on this topic is the **relay**. We will use it to simulate a door.
    
    You can find the connection of relay and how it works [*on this link*](https://www.circuitbasics.com/setting-up-a-5v-relay-on-the-arduino/).

- **LCD screen**

    This module is similar to the LCD screen we have used for the semester. We will use it to display different messages.

    You can find the explanations on [*Mr.Fryza GitHub*](https://github.com/tomas-fryza/Digital-electronics-2/tree/master/Labs/06-lcd).

- **LEDs**

    This module is similar to the LEDs we have used for the semester. We will use them to signal different events.

    You can find the explanations on [*Mr.Fryza GitHub*](https://github.com/tomas-fryza/Digital-electronics-2/tree/master/Labs/02-leds).

## Code description and simulations
In the following it is explained the structure of the program and different libraries that have been used.

The structure of the program is similar to other programs students created during the semester, to know of:

- main.c
- libraries

### main.c
We divided `main.c` in 3 different parts:

- Defines, includes and global variables
  - Configuration of different pins, global variables and libraries we will use.
  
- Main function
  - Configuration area. Different TIMERs and other devices will be configured.
  
- ISR
  - 3 ISRs have been used, each of them, configured with previous TIMERs:
  
    **ISR(TIMER0_OVF_vect)**   
    
    It will carry out scan of keypad using one function created by the programmer and which will be explained later.
    Also, inside this ISR, it will be displayed the state of the door when user enters some correct password using **UART** and LCD screen.
    Besides, current ISR will be disabled and on of the other two ISRs will be enabled.
    
    **ISR(TIMER1_OVF_vect)**   
    
    This ISR will be enabled just in case user enters correct password.
    The door will be opened, speaker will play a sound and LED GREEN will be on.
    After 5 seconds, this ISR will be disabled and first ISR will be enabled again.
    
    **ISR(TIMER2_OVF_vect)**   
    
    This ISR will be enabled just in case user enters wrong password for 3 times.
    The door will be closed, speaker will play a sound every second and LED RED will blink also every second.
    After 5 seconds, this ISR will be disabled and first ISR will be enabled again.

You can find complete description on [*main.c*](https://github.com/GuicoRM/Final-Project-DE2/blob/main/Final_Project_DE2/Final_Project/Final_Project/main.c).

### libraries
We used several libraries of previous laboratories such as:

- GPIO: [*gpio.h*](https://github.com/GuicoRM/Final-Project-DE2/blob/main/Final_Project_DE2/Final_Project/Final_Project/gpio.h) and [*gpio.c*](https://github.com/GuicoRM/Final-Project-DE2/blob/main/Final_Project_DE2/Final_Project/Final_Project/gpio.c).
- Timer: [*timer.h*](https://github.com/GuicoRM/Final-Project-DE2/blob/main/Final_Project_DE2/Final_Project/Final_Project/timer.h).
- LCD: [*lcd_definitions.h*](https://github.com/GuicoRM/Final-Project-DE2/blob/main/Final_Project_DE2/Final_Project/Final_Project/lcd_definitions.h), [*lcd.h*](https://github.com/GuicoRM/Final-Project-DE2/blob/main/Final_Project_DE2/Final_Project/Final_Project/lcd.h) and [*lcd.c*](https://github.com/GuicoRM/Final-Project-DE2/blob/main/Final_Project_DE2/Final_Project/Final_Project/lcd.c).
- UART: [*uart.h*](https://github.com/GuicoRM/Final-Project-DE2/blob/main/Final_Project_DE2/Final_Project/Final_Project/uart.h) and [*uart.c*](https://github.com/GuicoRM/Final-Project-DE2/blob/main/Final_Project_DE2/Final_Project/Final_Project/uart.c).

We also created one library for keypad: `keypad.h` and `keypad.c`

On **keypad.h**, pins and functions prototypes have been described. You can find the code [*keypad.h*](https://github.com/GuicoRM/Final-Project-DE2/blob/main/Final_Project_DE2/Final_Project/Final_Project/keypad.h).

You can find the code of [*keypad.c*](https://github.com/GuicoRM/Final-Project-DE2/blob/main/Final_Project_DE2/Final_Project/Final_Project/keypad.c).

On **keypad.c**, there are 2 functions:

- **void keypad_setup_pin(void)**: this function will be used to set different ROWS and COLUMNS of the keypad:

```C
void keypad_setup_pin(void)
{	
	/************************ CONFIGURATION OF KEYPAD-ROWS ************************/
	/* PIN PC0 -> ROW1 */
	GPIO_config_output(&DDRC, ROW1);					// Set pin as OUTPUT in Data Direction Register... (PIN -> OUTPUT)
	GPIO_write_high(&PORTC, ROW1);						// Put in HIGH level
	
	/* PIN PC1 -> ROW2 */
	GPIO_config_output(&DDRC, ROW2);					// Set pin as OUTPUT in Data Direction Register... (PIN -> OUTPUT)
	GPIO_write_high(&PORTC, ROW2);						// Put in HIGH level
	
	/* PIN PC2 -> ROW3 */
	GPIO_config_output(&DDRC, ROW3);					// Set pin as OUTPUT in Data Direction Register... (PIN -> OUTPUT)
	GPIO_write_high(&PORTC, ROW3);						// Put in HIGH level
	
	/* PIN PC3 -> ROW4 */
	GPIO_config_output(&DDRC, ROW4);					// Set pin as OUTPUT in Data Direction Register... (PIN -> OUTPUT)
	GPIO_write_high(&PORTC, ROW4);						// Put in HIGH level
	
	/*********************** CONFIGURATION OF KEYPAD-COLUMNS ***********************/
	/* PIN PD3 -> COL1 */
	GPIO_config_input_pullup(&DDRD, COL1);					// Set pin as INPUT in Data Direction Register... (PIN -> INPUT)
	
	/* PIN PC5 -> COL2 */
	GPIO_config_input_pullup(&DDRC, COL2);					// Set pin as INPUT in Data Direction Register... (PIN -> INPUT)
	
	/* PIN PC4 -> COL3 */
	GPIO_config_input_pullup(&DDRC, COL3);					// Set pin as INPUT in Data Direction Register... (PIN -> INPUT)		
}
```

- **uint8_t keypad_scan(void)**: this function will be used to show which button is pushed. We will send 'low level' per ROW and then we will check the state of different COLUMNS:

```C
uint8_t keypad_scan(void)
{ 
	uint8_t key = 12;
	
	for(uint8_t i = 0; i<=3; i++)                                           // Loop to go over different ROWS
	{							
		if(i==0)                                                        // First iteration
		{																						
			GPIO_write_high(&PORTC, ROW4);		                // Put ROW4 in HIGH level
			GPIO_write_low(&PORTC, ROW1);		                // Put ROW1 in LOW level	
		}
		else if(i==1)                                                   // Second iteration
		{																					
			GPIO_write_high(&PORTC, ROW1);		                // Put ROW1 in HIGH level
			GPIO_write_low(&PORTC, ROW2);		                // Put ROW2 in LOW level
		}
		else if(i==2)                                                   // Third iteration
		{										
			GPIO_write_high(&PORTC, ROW2);		                // Put ROW2 in HIGH level
			GPIO_write_low(&PORTC, ROW3);		                // Put ROW3 in LOW level
		}
		else if(i==3)                                                   // Fourth iteration
		{										
			GPIO_write_high(&PORTC, ROW3);		                // Put ROW3 in HIGH level
			GPIO_write_low(&PORTC, ROW4);		                // Put ROW4 in LOW level
		}
		
		for(uint8_t j = 0; j<=2; j++)                                   // Loop to go over different COLUMNS
		{						
			if (GPIO_read(&PIND,COL1) == 1)		                // Read the value of COLUMN1 and compare it to '1' in order to know which key is pushed
			{
				if (i == 0)			                // Previous first iteration (ROW1 in LOW level)
				{
					key = 1;		                // We push key '1'
					i=4;					// End of first loop
					j=3;					// End of second loop
					GPIO_write_high(&PORTC, ROW1);		// Put ROW1 in HIGH level again
				}
				else if(i == 1)                                 // Previous second iteration (ROW2 in LOW level)
				{							
					key = 4;				// We push the key '4'
					i=4;					// End of first loop
					j=3;					// End of second loop
					GPIO_write_high(&PORTC, ROW2);		// Put ROW2 in HIGH level again
				}
				else if(i == 2)                                 // Previous third iteration (ROW3 in LOW level)
				{							
					key = 7;				// We push the key '7'
					i=4;					// End of first loop
					j=3;					// End of second loop
					GPIO_write_high(&PORTC, ROW3);		// Put ROW3 in HIGH level again
				}
				else if(i == 3)                                 // Previous fourth iteration (ROW4 in LOW level)
				{							
					key = 10;				// We push the key '*'
					i=4;					// End of first loop
					j=3;					// End of second loop
					GPIO_write_high(&PORTC, ROW4);		// Put ROW4 in HIGH level again
				}
			}
			else if(GPIO_read(&PINC,COL2) == 1)                     // Read the value of COLUMN2 and compare it to '1' in order to know which key is pushed
			{		
				if (i == 0)					// Previous first iteration (ROW1 in LOW level)
				{
					key = 2;				// We push the key '2'
					i=4;					// End of first loop
					j=3;					// End of second loop
					GPIO_write_high(&PORTC, ROW1);		// Put ROW1 in HIGH level again	
				}
				else if(i == 1)                                 // Previous second iteration (ROW2 in LOW level)
				{							
					key = 5;				// We push the key '5'
					i=4;					// End of first loop
					j=3;					// End of second loop
					GPIO_write_high(&PORTC, ROW2);		// Put ROW2 in HIGH level again
				}
				else if(i == 2)                                 // Previous third iteration (ROW3 in LOW level)
				{							
					key = 8;				// We push the key '8'
					i=4;					// End of first loop
					j=3;					// End of second loop
					GPIO_write_high(&PORTC, ROW3);		// Put ROW3 in HIGH level again	
				}
				else if(i == 3)                                 // Previous fourth iteration (ROW4 in LOW level)
				{								
					key = 0;				// We push the key '0'
					i=4;					// End of first loop
					j=3;					// End of second loop
					GPIO_write_high(&PORTC, ROW4);		// Put ROW4 in HIGH level again
				}
			}
			else if(GPIO_read(&PINC,COL3) == 1)                     // Read the value of COLUMN3 and compare it to '1' in order to know which key is pushed
			{			
				if (i == 0)					// Previous first iteration (ROW1 in LOW level)
				{
					key = 3;				// We push the key '3'
					i=4;					// End of first loop	
					j=3;					// End of second loop
					GPIO_write_high(&PORTC, ROW1);	        // Put ROW1 in HIGH level again
				}
				else if(i == 1)                                 // Previous second iteration (ROW2 in LOW level)
				{							
					key = 6;				// We push the key '6'
					i=4;					// End of first loop
					j=3;					// End of second loop
					GPIO_write_high(&PORTC, ROW2);		// Put ROW2 in HIGH level again
				}
				else if(i == 2)                                 // Previous third iteration (ROW3 in LOW level)
				{							
					key = 9;				// We push the key '9'
					i=4;					// End of first loop
					j=3;					// End of second loop
					GPIO_write_high(&PORTC, ROW3);		// Put ROW3 in HIGH level again
				}
				else if(i == 3)                                 // Previous fourth iteration (ROW4 in LOW level)
				{							
					key = 11;				// We push the key '#'
					i=4;					// End of first loop
					j=3;					// End of second loop
					GPIO_write_high(&PORTC, ROW4);		// Put ROW4 in HIGH level again
				}
			}							// end 'if' for  COLuMNS	
		}								// end 2º 'for'
	}									// end 1º 'for'
	return key;							        // Return the value of the key which is pushed
}
```

## Video/Animation
You can find personal video where all the previous features of the system described [*on this link*](https://www.youtube.com/watch?v=qahc68WCkCg&feature=youtu.be).

**Note:** background noise is from the computer itself, not the door security system.

## References
1. [*How keypad works*](https://arduinogetstarted.com/tutorials/arduino-keypad).

2. [*How speaker works*](https://shallowsky.com/arduino/class/buzzer.html#:~:text=A%20%22piezo%20buzzer%22%20is%20basically,the%20crystal%20can%20make%20sound.).

3. [*How relays works*](https://maker.pro/arduino/projects/driving-a-relay-with-an-arduino#:~:text=*%20A%20relay%20basically%20allows%20a,off%20a%20higher%20power%20circuit).

