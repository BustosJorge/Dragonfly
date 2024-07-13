//Define la posicion del elemento dentro del arreglo status
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
int leds[] ={2,3,4,5,6,7,9,17,18,19};//en lista el numero de pin de los leds que se van a utiliar
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

