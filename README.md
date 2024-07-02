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
#define ESTADO 0
#define T_OFF 1
#define T_ON 2
#define T_ANTERIOR 3

//Rango de los intervalos para encendido y apagado
unsigned long MAX_OFF = 9000;
unsigned long MIN_OFF = 2000;
unsigned long MAX_ON = 400;
unsigned long MIN_ON = 200;
//Intervalos por defecto
unsigned long interval_off = MAX_OFF;
unsigned long interval_on = MAX_ON;

unsigned long currentMillis = 0;
int leds[] ={13,2,3,4,5};//en lista el numero de pin de los leds que se van a utiliar
unsigned long status[]={0,interval_off,interval_on,0};//[ESTADO,T_OFF, T_ON,T_ANTERIOR]
unsigned long LED_status[sizeof(leds)][5];//[No. led][ESTADO,T_OFF, T_ON,T_ANTERIOR]
void setup() {
  //configura la lista de leds como salida
  for (int i = 0; i < sizeof(leds); i++){
     pinMode(leds[i], OUTPUT);
  }

  //se rellena la matriz de led con los datos por defecto
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
//Revisa el estado de cada uno de los led y actualiza sus estados
    for (int i = 0; i < sizeof(leds); i++){

        if (currentMillis - LED_status[i][T_ANTERIOR] >= LED_status[i][T_OFF] && LED_status[i][ESTADO] == LOW) {
        // save the last time you blinked the LED
          LED_status[i][T_ANTERIOR] = currentMillis;
          LED_status[i][ESTADO]=1;
          LED_status[i][T_ON] = random(MIN_ON,MAX_ON);
        }

        else if (currentMillis - LED_status[i][T_ANTERIOR] >= LED_status[i][T_ON] && LED_status[i][ESTADO] == HIGH) {
            LED_status[i][T_ANTERIOR] = currentMillis;
            LED_status[i][ESTADO]=0;
            LED_status[i][T_OFF] = random(MIN_OFF, MAX_OFF);
        }

        // set the LED with the ledState of the variable:
        digitalWrite(leds[i], LED_status[i][ESTADO]);
    }
}

```

## Components
10 LEDs SMD 0603 (for fireflies)
Jumper wires
1 PCB base
1 PCB Dragonfly
1 Contacto USB Type C Power supply (5V)
1 Lithium polymer (Li-Po) battery (400 mAh)
1 2P2T switch
4 M3 screws
3D-printed base

## Circuit Diagram

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