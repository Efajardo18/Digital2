// ------------------------------------------------------------------
// NOMBRE:  Edgar Oliverio Fajardo Monzón
// CARNE:   18270
// CURSO:   Electrónica Digital II
// SECCIÓN: 31
// -------------------------------------------------------------------

const byte ledPin1 = RED_LED;
const byte ledPin2 = GREEN_LED;
const byte ledPin3 = BLUE_LED;
const byte interruptPin1 = PF_4;
const byte interruptPin2 = PF_0;
volatile byte cont1 =1;
volatile byte cont2 =1;
volatile byte state =0;
volatile byte win1 =0;
volatile byte win2 =0;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(interruptPin1, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin1), suma1, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), suma2, RISING);
}

void loop() {
  if(state==0){
    analogWrite(ledPin1, 255);
  }
  else if(state==1){
    analogWrite(ledPin1, 255);
    analogWrite(ledPin2, 233);
    delay(1000);
    state=state+1;
  }
  else if(state==2){
    analogWrite(ledPin1, 0);
    analogWrite(ledPin2, 255);
  }
  else{
    if(win1==1){
      analogWrite(ledPin1,0);
      analogWrite(ledPin2,0);
      analogWrite(ledPin3,255);
    }
    else if(win2==1){
      analogWrite(ledPin1,255);
      analogWrite(ledPin2,164);
      analogWrite(ledPin3,32);
    }
  }
}

void suma1() {
  if(state==0){
    state=state+1;
  }
  else if(state==2){
    if(cont1==128){
      state=state+1;
      win1=1;
    }
    else{
      cont1 = 2* cont1;
    }
  }
}

void suma2() {
  if(state==0){
    state=state+1;
  }
  else if(state==2){
    if(cont2==128){
      state=state+1;
      win2=1;
    }
    else{
      cont2 = 2* cont2;     
    }
  }
}
