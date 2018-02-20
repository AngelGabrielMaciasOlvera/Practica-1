/* ----------------------Semaforo Peatonal Mexicano------------------------
 *  El Siguiente trabajo en Arduino es un ejemplo que ejemplifica el trabajo
 *  de un semaforo Peatonal Mexicano, el cual se encuentra en un estado de 
 *  transición para los carros (luz verde) y en un estado de paro para los  
 *  peatones (luz roja) en un "comportamiento normal". Cuando un peaton desea
 *  pasar debe de oprimir el botón, el cual hará que el semaforo pase de luz
 *  verde a amarilla para posteriormente pasar a luz roja y a la par luz verde
 *  permitiendo el pase peatonal; cabe a destacar que el tiempo en que permanecerá 
 *  en luz verde para los peatones y luz roja para los automoviles será controlada 
 *  por los valores entrantes al sistema por parte del potenciometro para posteriormente 
 *  y una vez acabado el tiempo de pase peatonal vuelva a su "comportamiento normal" 
 *  
 *  
 *  Archivo para consulta y modificación orientado al público en general
*/

//Leds del semaforo del carro
int rojoCarro=13;
int amarilloCarro=12;
int verdeCarro=11;

//Leds del semaforo del peaton
int rojoPeaton=7;
int verdePeaton=6;

//Pulsador
int boton=2;

//Variable para detectar el estado del boton
boolean op=false;

//Valor de tiempo de espera (será asigando por valor de multimetro)
long valor=0;

//Variables Auxiliares para "controlar" si el
//boton ha sido presionado en oacsiones seguidas
//Dar oportunidad de pase a los autos
long previousMillis = 0;
 unsigned long currentMillis = 0;


void setup() {
  //Boton en entrada
  pinMode(boton,INPUT);
  
  //Leds del semaforo del carro en salida
  pinMode(rojoCarro,OUTPUT);
  pinMode(amarilloCarro,OUTPUT);
  pinMode(verdeCarro,OUTPUT);

  //Leds del semaforo del Peaton en Salida
  pinMode(rojoPeaton,OUTPUT);
  pinMode(verdePeaton,OUTPUT);

  //Inicio de Comunicación Serial
  Serial.begin(9600); //Inicia comunicación serial
}

void loop() {
  //Comunicación Serial
  //Asigna el tiempo que se dará a los
  //peatones para que pasen 
  valor= (analogRead(A0));
  currentMillis = millis();

  /*Se multiplica por 9 el valor otorgado por el potenciometro para visualizar con
  mayor claridad el funcionamiento de tiempo de espera; además se propone colocar 
  el potenciometro en su máximo valor (1024)
  para tener una mejor visualización de resultados*/
  if (digitalRead(boton)==HIGH&&(currentMillis - (previousMillis)) > (valor*9)){
    previousMillis = (currentMillis);
    //-------------Estado de Cambio
    proporcionarPasoPeatonal();
  }

  else
    //----------Estado Normal
    proporcionarPasoAutomoviles();
}

void proporcionarPasoAutomoviles(){
     //Semaforo del carro
    digitalWrite(verdeCarro,HIGH);
    digitalWrite(amarilloCarro,LOW);
    digitalWrite(rojoCarro,LOW);
    
    //Semaforo del Peaton
    digitalWrite(verdePeaton,LOW);
    digitalWrite(rojoPeaton,HIGH);
  
}

void proporcionarPasoPeatonal(){
    //Semaforo del carro
    //Aviso de cambio con luz parpadeando en verde
    for (int x=0; x<7; x++){
      digitalWrite(verdeCarro,HIGH);
      delay(250);
      digitalWrite(verdeCarro,LOW);
      delay(250);
    }
    digitalWrite(verdeCarro,LOW);
    digitalWrite(amarilloCarro,HIGH);
    digitalWrite(verdeCarro,LOW);
    delay(1700);
    digitalWrite(rojoCarro,HIGH);
    digitalWrite(amarilloCarro,LOW);
    digitalWrite(verdeCarro,LOW);
    digitalWrite(verdePeaton,HIGH);
    digitalWrite(rojoPeaton,LOW);
    //Tiempo de espera Peatonal (valor multiplicado por 2 para mejor visualización de resultados)
    delay((valor*2));
}
