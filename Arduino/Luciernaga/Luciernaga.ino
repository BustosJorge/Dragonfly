// Defines the position of the element within the status array
#define STATE 0
#define TIME_OFF 1
#define TIME_ON 2
#define TIME_PREVIOUS 3
/*Fireflys variables*/
// Interval range for on and off
unsigned long MAX_OFF = 9000;
unsigned long MIN_OFF = 2000;
unsigned long MAX_ON = 400;
unsigned long MIN_ON = 200;
// Default intervals
unsigned long interval_off = MAX_OFF;
unsigned long interval_on = MAX_ON;

unsigned long currentMillis = 0;
int leds[] = {2, 3, 4, 5, 6, 7, 9, 17, 18, 19};               // List the pin number of the LEDs that will be used
unsigned long status[] = {LOW, interval_off, interval_on, 0}; //[STATE,TIME_OFF, TIME_ON,TIME_PREVIOUS]
unsigned long LED_status[sizeof(leds)][5];                    //[No. led][STATE,TIME_OFF, TIME_ON,TIME_PREVIOUS]

/*Dragonflay variables*/
int dragonflay = 8; // pin numbrer dragronfly control

// Variables for the increment and decrement cycle of the work cycle
int dutyCycleMin = 10;        // MINIMUM duty cycle from 0 to 100
int dutyCycleMax = 90;        // MAXIMUM duty cycle from 0 to 100
int dutyCycle = dutyCycleMin; // MAXIMUM duty cycle from 0 to 100
unsigned long previousTime;   // Previous Time
unsigned long delayTime = 15; // Delay Time
bool state = LOW;             // state of increase or decrease

// variables for PWM simulation
int counter = 0;
const int period = 100;

void setup()
{
  // configure led list as output
  for (int i = 0; i < sizeof(leds); i++)
  {
    pinMode(leds[i], OUTPUT);
  }

  // the LED matrix is ​​filled with the default data
  for (int i = 0; i < sizeof(leds); i++)
  {
    for (int j; j < 4; j++)
    {
      LED_status[i][j] = status[j];
    }
  }

  pinMode(dragonflay, OUTPUT); // Configure pin as output
}

void loop()
{
  // put your main code here, to run repeatedly:
  currentMillis = millis();
  fireflay_array();
  simulationPWM(dragonflay, upDownDutyCyle());
}

void fireflay_array(void)
{
  // Check the status of each of the LEDs and update their statuses
  for (int i = 0; i < sizeof(leds); i++)
  {

    if (currentMillis - LED_status[i][TIME_PREVIOUS] >= LED_status[i][TIME_OFF] && LED_status[i][STATE] == LOW)
    {
      // save the last time you blinked the LED
      LED_status[i][TIME_PREVIOUS] = currentMillis;
      LED_status[i][STATE] = HIGH;
      LED_status[i][TIME_ON] = random(MIN_ON, MAX_ON);
    }

    else if (currentMillis - LED_status[i][TIME_PREVIOUS] >= LED_status[i][TIME_ON] && LED_status[i][STATE] == HIGH)
    {
      LED_status[i][TIME_PREVIOUS] = currentMillis;
      LED_status[i][STATE] = LOW;
      LED_status[i][TIME_OFF] = random(MIN_OFF, MAX_OFF);
    }

    // set the LED with the ledState of the variable:
    digitalWrite(leds[i], LED_status[i][STATE]);
  }
}

int upDownDutyCyle(void)
{

  if (currentMillis > previousTime + delayTime)
  {
    previousTime = currentMillis;
    if (dutyCycle < dutyCycleMax && state == HIGH)
    {
      dutyCycle++;
      if (dutyCycle >= dutyCycleMax)
      {
        state = LOW;
      }
    }
    else if (dutyCycle >= dutyCycleMin && state == LOW)
    {
      dutyCycle--;
      if (dutyCycle < dutyCycleMin)
      {
        state = HIGH;
      }
    }
  }
  return dutyCycle;
}

void simulationPWM(int pin, int dutyCycle)
{

  if (counter >= 0 && counter < dutyCycle)
  {
    digitalWrite(pin, HIGH);
  }
  else
  {
    digitalWrite(pin, LOW);

    if (counter > period)
    {
      counter = 0;
    }
  }
  counter++;
}
