# Dragonfly

## Description
Dragonfly is a night lamp that simulates fireflies in a jar and features an illuminated flying dragonfly. Originally designed as a gift for my girlfriend, this project showcases my skills in electronic design and embedded programming. **Please note that this project is still in development and not yet complete.**


## Table of Contents

1. [Usage](#usage)
2. [Example Code](#example-code)
3. [Components](#components)
4. [Circuit Diagram](#circuit-diagram)
5. [Assembly Instructions](#assembly-instructions)
6. [License](#license)
7. [Contact](#contact)


## Usage
Instructions on how to use the Dragonfly night lamp:

Once the assembly is finished, it is charged with a USB type C cable, the switch turns on the lamp by charging or with the battery.


## Example Code
```cpp
//Defines the position of the element within the status array
#define STATE 0
#define TIME_OFF 1
#define TIME_ON 2
#define TIME_PREVIOUS 3

//Interval range for on and off
unsigned long MAX_OFF = 9000;
unsigned long MIN_OFF = 2000;
unsigned long MAX_ON = 400;
unsigned long MIN_ON = 200;
//Default intervals
unsigned long interval_off = MAX_OFF;
unsigned long interval_on = MAX_ON;

unsigned long currentMillis = 0;
int leds[] ={2,3,4,5,6,7,9,17,18,19};//List the pin number of the LEDs that will be used
unsigned long status[]={LOW,interval_off,interval_on,0};//[STATE,TIME_OFF, TIME_ON,TIME_PREVIOUS]
unsigned long LED_status[sizeof(leds)][5];//[No. led][STATE,TIME_OFF, TIME_ON,TIME_PREVIOUS]
void setup() {
  //configure led list as output
  for (int i = 0; i < sizeof(leds); i++){
     pinMode(leds[i], OUTPUT);
  }

  //the LED matrix is ​​filled with the default data
  for (int i = 0; i < sizeof(leds); i++){
    for(int j; j < 4; j++){
      LED_status[i][j]=status[j];
    }
  } 
}

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();
  Luciernaga_array();

}

void Luciernaga_array(void){
//Check the status of each of the LEDs and update their statuses
    for (int i = 0; i < sizeof(leds); i++){

        if (currentMillis - LED_status[i][TIME_PREVIOUS] >= LED_status[i][TIME_OFF] && LED_status[i][STATE] == LOW) {
        // save the last time you blinked the LED
          LED_status[i][TIME_PREVIOUS] = currentMillis;
          LED_status[i][STATE]=HIGH;
          LED_status[i][TIME_ON] = random(MIN_ON,MAX_ON);
        }

        else if (currentMillis - LED_status[i][TIME_PREVIOUS] >= LED_status[i][TIME_ON] && LED_status[i][STATE] == HIGH) {
            LED_status[i][TIME_PREVIOUS] = currentMillis;
            LED_status[i][STATE]=LOW;
            LED_status[i][TIME_OFF] = random(MIN_OFF, MAX_OFF);
        }

        // set the LED with the ledState of the variable:
        digitalWrite(leds[i], LED_status[i][STATE]);
    }
}
```

## Components
| Element | Description | Decignator  | Quanty |
| ------- | ----------- | ----------- | ------ |
| Battery | Li-Po battery 400 mAh | BAT | 1 |
| 22uF | Capacitor | C1, C4 | 2 |
| 22pF | Capacitor | C2, C3 | 2 |
| 10uF | Capacitor | C5, C6 | 2 |
| 100nF | Capacitor | C7 | 1 |
| 1uF | Capacitor | C8 | 1 |
|LED GREAN |Typical GREAN LED| D1, D2, D3, D4, D5, D6, D7, D8, D9, D10| 10 |
| 1PS76SB10,115 | Schottky Diode | D11, D12 | 2 |
| ATMEGA328PB-AN | Integrated Circuit | IC2 | 1 |
| MT3608 | Integrated Circuit | IC3 | 1 |
| TC4056A | Integrated Circuit | IC4 | 1 |
| SRP1038CC-220M | Inductor | L1 | 1 |
| LTST-C191TBKT-5A | LED | LED1 | 1 |
| DMP3125L-7 | MOSFET (P-Channel) | Q1, Q2 | 2 |
| 33K | Resistor | R1, R15 | 2 |
| 4.7K | Resistor | R2 | 1 |
| 10K | Resistor | R3, R18 | 2 |
| 1K | Resistor | R4, R5, R6, R7, R8, R9, R10, R11, R12, R13, R14, R17 | 12 |
| 100k | Resistor | R16 | 1 |
| SW | 2P2T SWITCH, 2 POLES 2 THROWS | SW | 1 |
| Type C female connector | USB Type C 2 Pins Connector Jack Female Type-C 3A 30V Oval with Wire Current Fast Charging Jacker Port USB-C Charger Plug Socket | V_IN | 1 |
| ECS-160-10-37-JGP-TR | Crystal or Oscillator | Y1 | 1 |


## Circuit Diagram
![PCB base 1](/PCBs/PCB_Luciernagas/Schematic_PCB_base_1_2.jpg)
![PCB base 2](/PCBs/PCB_Luciernagas/Schematic_PCB_base_2_2.jpg)
![PCB base](/PCBs/PCB_Luciernagas/PCB_FIREFLYS.jpg)
![PCB dragonfly](/PCBs/PCB_Libelula/DRAGONFLY.jpg)
[PDF PCB base](/PCBs/PCB_Luciernagas/PCB_Luciernagas.pdf)

## Assembly Instructions
1. Connect the electronic components as per the provided circuit diagram on PCB base (exept USB conector,switch and battery).
2. Load the bootloader on atmega328p with the help of an arduino board, through the ICSP connector. You can search on the internet how to do it, here is some documentation of Arduino [Arduino as ISP and Arduino Bootloaders](https://docs.arduino.cc/built-in-examples/arduino-isp/ArduinoISP/), although you can search for a more specific tutorial.
3. Upload sketch by Arduino ISP programmer, here is some documentation [Getting Started with the Arduino ISP](https://docs.arduino.cc/retired/getting-started-guides/ArduinoISP/) or you can search for a tutorial how to upload sketch by ISP.
4. Solder wires to the SMD LEDs to PCB base, so that they remain in the air and look like they are floating (check polarity).
5. Solder wires to the PCB Dragonfly to PCB base,so that it remains in the air and appears to be floating (check polarity).
6. Drill the Lid of the bottle, according to the holes in the 3D printed base.
7. Place the USB connector under pressure in a smaller hole at the base of the bottle lid.
8. Place the switch in the hole at the base 3D printing.
9. Place the battery in the base of the bottle.
10. Solder the connector and switch to the base PCB.
11. Glue the 3d printing base to the lid.
12. Screw the pcb to the base with the M3 screws
11. Connect the battery to the PCB base and switch on the night lamp. The dragonfly will Power on the device to see the fireflies and the illuminated dragonfly in action.

![assembly](/Models%203D/Ensamblaje/IMG_1.JPG/)



## License
This project is licensed under the MIT License. 


## Contact
Jorge Bustos - bustos.jorge21@gmail.com

Project Link: https://github.com/BustosJorge/Dragonfly