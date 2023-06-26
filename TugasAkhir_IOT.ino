//=====================================================LIBRARY=======================================================================
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_DEVICE_NAME ""
#define BLYNK_AUTH_TOKEN ""
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//======================================================DONE=========================================================================


//==================================================INITIALIZATION=======================================================================

// V1 --> gas & smoke Chart
// V2 --> vibration Chart
// V3 --> Parking slot 1
// V4 --> Parking slot 2
// V5 --> Parking slot 3
// V6 --> Gas & smoke Notification 
// V7 --> Earthquake Notification 

int led1 = D1;
int led2 = D2;
int led3 = D3;

const int ir1 = D4;
const int ir2 = D5;
const int ir3 = D6;

int ir1_value;
int ir2_value;
int ir3_value;

int trafic1;
int trafic2;
int trafic3;


const int gas = A0;
const int vibration = D7;

float gas_value;
int vibra_value;

bool present = LOW;
bool previous = LOW;

int state = 0;
int count_vibra = 0;

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "";
char pass[] = "";

BlynkTimer timer;

//======================================================DONE=========================================================================

//====================================================FUNCTION=======================================================================
void gas_vibra_Read(){
  int current = millis();
  int pre_current;
  if(current - pre_current > 33){
     gas_value = analogRead(gas);
      vibra_value = digitalRead(vibration) ;
      // Serial.print("gas:");
      // Serial.println(gas_value);
      // Serial.print("vibra:");
      // Serial.println(vibra_value);

    pre_current = current;
  }
  
  Blynk.virtualWrite(V1, gas_value);
  Blynk.virtualWrite(V2, vibra_value);
  if(gas_value >= 380){
    Blynk.virtualWrite(V6, "Alert Gas Detection!!!!");
  }
  else {
    Blynk.virtualWrite(V6, "No Gas Detection!!!!");
  }
  // previous = present;
  if (state == 0){
    switch (vibra_value) {
    case 0:
      state = 0;

      break;

    case 1: 
      state = 1;
      count_vibra = count_vibra +1;
    break;
      
    }

  }

  if (vibra_value == LOW){
    state = 0;

  }
  
  if (count_vibra >=3){
    Blynk.virtualWrite(V7, "Alert Earthquake Detection!!!!");
  }

  else {
    Blynk.virtualWrite(V7, "No Earthquake Detection!!!!");
  }

  
  

  
  Serial.print("gas:");
  Serial.println(gas_value);
  Serial.print("vibra:");
  Serial.println(count_vibra);
}

BLYNK_WRITE(V0) {
  int state2= param.asInt();
  count_vibra = 0; 

}



//======================================================DONE=========================================================================


// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);

  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  pinMode(ir3,INPUT);

  pinMode(gas,INPUT);
  pinMode(vibration,INPUT);
  Blynk.begin(auth,ssid,pass);
  timer.setInterval(100L,gas_vibra_Read);


}


// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run(); // Initiates SimpleTimer
  int current1 = millis();
  int pre_current1;

  if(current1 - pre_current1 > 50){
    ir1_value = digitalRead(ir1);
    // Serial.println(ir1_value);
    ir2_value = digitalRead(ir2);
    ir3_value = digitalRead(ir3);
    pre_current1 = current1;
  }

  //============= LED INDICATOR ======================
  if (ir1_value == LOW ){
    trafic1 = 1;
    digitalWrite(led1, HIGH);
    Blynk.virtualWrite(V3,HIGH);
  }

  else {
    trafic1 = 0;
    digitalWrite(led1, LOW);
    Blynk.virtualWrite(V3,LOW);

  }

  if (ir2_value == LOW ) {
    trafic2=1;
    digitalWrite(led2, HIGH);
    Blynk.virtualWrite(V4,HIGH);
  }
  else {
    trafic2=0;
    digitalWrite(led2, LOW);
    Blynk.virtualWrite(V4,LOW);
  }

  if (ir3_value == LOW ) {
    trafic3 = 1; 
  digitalWrite(led3, HIGH);
  Blynk.virtualWrite(V5,HIGH);
  }

  else {
     trafic3 = 0; 
  digitalWrite(led3, LOW);
  Blynk.virtualWrite(V5,LOW);
  }

  int count_tra = trafic1 + trafic2 +trafic3;
  Blynk.virtualWrite(V8,count_tra);


  

}
