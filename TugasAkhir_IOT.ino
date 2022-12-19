//=====================================================LIBRARY=======================================================================
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLVMDmBQ8V"
#define BLYNK_DEVICE_NAME "budi"
#define BLYNK_AUTH_TOKEN "5oP02FZyEDHCkzRhA9HxG0Scu9IwIUSA"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//======================================================DONE=========================================================================


//==================================================INITIALIZATION=======================================================================
int led1 = D1;
int led2 = D2;
int led3 = D3;

const int ir1 = D4;
const int ir2 = D5;
const int ir3 = D6;

int ir1_value;
int ir2_value;
int ir3_value;

const int gas = A0;
const int vibration = D7;

float gas_value;
float vibra_value;

char auth[] = BLYNK_AUTH_TOKEN;
//char ssid[] = "Pelatihan_Elektro";
//char pass[] = "elektro12345*";

char ssid[] = "sitibudi_laptop";
char pass[] = "luncuran123";

BlynkTimer timer;

//======================================================DONE=========================================================================

//====================================================FUNCTION=======================================================================
void gas_vibra_Read(){
  int current = millis();
  int pre_current;
  if(current - pre_current > 33){
     gas_value = analogRead(gas);
      vibra_value = digitalRead(vibration) ;
    pre_current = current;
  }
  
  Blynk.virtualWrite(V1, gas_value);
  Blynk.virtualWrite(V2, vibra_value);
  Serial.print("gas:");
  Serial.println(gas_value);
  Serial.print("vibra:");
  Serial.println(vibra_value);
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
  timer.setInterval(1000L,gas_vibra_Read);


}


// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {
  // put your main code here, to run repeatedly:

  int current1 = millis();
  int pre_current1;

  if(current1 - pre_current1 > 50){
    ir1_value = analogRead(ir1);
    ir2_value = analogRead(ir2);
    ir3_value = analogRead(ir3);
    pre_current1 = current1;
  }

  //============= LED INDICATOR ======================
  if (ir1_value <=3 ){
    digitalWrite(led1, HIGH);
  }

  else if (ir2_value <=3 ) {
    digitalWrite(led2, HIGH);
  }

  else if (ir3_value <= 3) {
  digitalWrite(led3, HIGH);
  }

  else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }


  Blynk.run();
  timer.run(); // Initiates SimpleTimer

}
