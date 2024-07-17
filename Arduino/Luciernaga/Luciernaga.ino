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

