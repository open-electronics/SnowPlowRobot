
// Sketch per Robot Spazzaneve 
// di Vittorio Loschiavo
// pubblicato sul numero 191 Dic2014/Gen2015 Elettronica In - www.elettronicain.it
// utilizza: Arduino Uno Rev3 - Motor Shield VMA03 - PS2 Shield - Driver 2x15A DRI0018 - Controller Wireless PS2

 
#include <Shield_PS2.h>

//declare class objects
PS2 ps2=PS2();                    //PS2 class object: ps2

int FOTORES = A0;    // Ingreaao A0 per Fotoresistenza
int RELAY = 13;      // Uscita pin 13 per relè
int sensorValue = 0;  // Variabile per valore fotoresistenza

int ALZAPALA = 12;       // Attuatore lineare per alzare e abbassare la PALA - pin 12 DIRB
int ONALZAPALA = 11;     // attiva i motori dx e sx sul pin 11 PWMB
int RUOTAPALA = 2;       // Attuatori lineari per ruotare a destra e sinistra la pala - pin 2 DIRA
int ONRUOTAPALA = 3;     // attiva motori per la PALA sul pin 3 PWMA

int E1 = 5;  //MOTORE 1 SPEED CONTROL M1_PWM
int E2 = 6;  //MOTORE 2 SPEED CONTROL M2_PWM
int M1 = 4;  //MOTORE 1 DIRECTION CONTROL M1_EN
int M2 = 7;  //MOTORE 2 DIRECTION CONTROL M2_EN

int counter=0;
int stato=0;
int val=0;
int velo=0;
int motori=0;

void setup()
{
  Serial.begin(9600);
   ps2.init(9600, 8, 9);   //initialize the main board to use desired (baudrate, rx, tx)
                           //for Arduino Mega use RX:10, TX: 11 for software serial
                           //for Arduino Leonardo use pin 8, 9, 10, 11 as RX and TX for software serial
                            
  pinMode (FOTORES, INPUT);                          
  pinMode (RELAY, OUTPUT); 
  pinMode (RUOTAPALA, OUTPUT);
  pinMode (ALZAPALA, OUTPUT);
  pinMode (ONRUOTAPALA, OUTPUT);
  pinMode (ONALZAPALA, OUTPUT); 
  pinMode (E1, OUTPUT);
  pinMode (M1, OUTPUT);
  pinMode (E2, OUTPUT);
  pinMode (M2, OUTPUT);
  stato=0;
      
}
void loop(){
    motori=0;
  if( ps2.getval(p_up)==0 || ps2.getval(p_joy_lu)==100) { // se pulsante up è premuto o il joystick sinistro è in posizione up
    Serial.println("AVANTI");    //
    analogWrite (E1,velo);      //PWM Speed Control
  digitalWrite(M1,HIGH);        //
  analogWrite (E2,velo);        //
  digitalWrite(M2,HIGH);       ///
  motori=1;  
      }
  if (ps2.getval(p_down)==0 || ps2.getval(p_joy_ld)==100) { // se pulsante down è premuto o il joystick sinistro è in posizione down
    Serial.println("INDIETRO");  
   analogWrite (E1,velo);
  digitalWrite(M1,LOW);   
  analogWrite (E2,velo);    
  digitalWrite(M2,LOW); 
  motori=1;    
      }  
  if (ps2.getval(p_right)==0 || ps2.getval(p_joy_lr)==100){ // se pulsante right è premuto o il joystick sinistro è in posizione right
    Serial.println("DESTRA"); 
   analogWrite (E1,velo);
  digitalWrite(M1,HIGH);    
  analogWrite (E2,velo);    
  digitalWrite(M2,LOW); 
  motori=1;  
    }
  if (ps2.getval(p_left)==0 || ps2.getval(p_joy_11)==100) { // se pulsante left è premuto o il joystick sinistro è in posizione left
    Serial.println("SINISTRA");    //
     analogWrite (E1,velo);      //
  digitalWrite(M1,LOW);          //
  analogWrite (E2,velo);         // 
  digitalWrite(M2,HIGH);        //
  motori=1;                     // 
       }
  if (ps2.getval(p_triangle)==0) { // se il pulsante triangolo è premuto
    Serial.println("TRIANGOLO"); // invia la scritta TRIANGOLO sulla seriale
    if (velo<250)              // e se la variabile velocità (velo) è inferiore a 250
{                              //
   velo=velo+25;              // aumente di 25 il valore della variabile velocità (velo)
   }                          //
else                          // 
{                            //
ps2.vibrate(2, 255);         // attiva la vibrazione sul controller se il valore della variabile velocità (velo) è uaguale a 250
delay(500);                  // pausa 500 ms
ps2.vibrate(2,0);            // disattiva vibrazione
 }                           // 
  analogWrite (M1, velo);    //
    analogWrite (M2, velo);   // 
 Serial.println(velo);       
      }
  if (ps2.getval(p_cross)==0) { // se premuto il pulsante "X"
    Serial.println("X");        // invia la scritta "X" sulla seriale
    if (velo>0 && velo<=250)    // se la variabile velocità (velo) è maggiore di zero e inferiore a 250
{                               // 
  velo=velo-25;                // diminuisci di 25 il valore della variabile velocità (velo)
   }
else 
{
//non fa niente
} 
    analogWrite (M1, velo);
    analogWrite (M2, velo);
   Serial.println(velo);
      }
  if (ps2.getval(p_circle)==0) {
    Serial.println("CERCHIO");
    if (stato==0)
    {                               // 
     stato=stato+1;
     delay(100);
     Serial.println(stato); 
     digitalWrite(RELAY, HIGH);
     ps2.vibrate(2, 255);         // attiva la vibrazione sul controller
    delay(500);                  // pausa 500 ms
    ps2.vibrate(2,0);            // disattiva vibrazione
    delay(500);
    ps2.vibrate(2,255);
    delay(500);
    ps2.vibrate(2,0);
      }
else 
{
stato=0;
delay(100);
Serial.println(stato); 
digitalWrite(RELAY, LOW);
ps2.vibrate(2, 255);         // attiva la vibrazione sul controller
    delay(500);                  // pausa 500 ms
    ps2.vibrate(2,0);            // disattiva vibrazione
} 
     }
  if (ps2.getval(p_square)==0) { //se premuto ferma i motori
    Serial.println("QUADRATO");
      digitalWrite(E1,0); 
  digitalWrite(M1,LOW);    
  digitalWrite(E2,0);   
  digitalWrite(M2,LOW);  
  velo=0;
     }
  if (ps2.getval(p_l1)==0) {
    Serial.println("L1");
    digitalWrite (ONALZAPALA, HIGH);  //alza la pala
digitalWrite (ALZAPALA, LOW);     //
   }
 if (ps2.getval(p_l1)==1) {
    Serial.println("L1");
   digitalWrite (ONALZAPALA, LOW);  //disattiva alza pala
digitalWrite (ALZAPALA, LOW);     //
     }
  if (ps2.getval(p_l2)==0) {
    Serial.println("L2");
     digitalWrite (ONRUOTAPALA, HIGH);  //ruota la pala a sinistra
digitalWrite (RUOTAPALA, LOW);     //
         }
          if (ps2.getval(p_l2)==1) {
Serial.println("L2");
digitalWrite (ONRUOTAPALA, LOW);  //ferma rotazione pala a sinistra
digitalWrite (RUOTAPALA, LOW);     //
     }
  if (ps2.getval(p_r1)==0) {
    Serial.println("R1");
    digitalWrite (ONALZAPALA, HIGH);  //attiva alza pala
digitalWrite (ALZAPALA, HIGH);    //
       }
  if (ps2.getval(p_r2)==0) {
    Serial.println("R2");
    digitalWrite (ONRUOTAPALA, HIGH);  //attiva rotazione pala a destra
digitalWrite (RUOTAPALA, HIGH);    //
     }
  if (ps2.getval(p_start)==0) {
    Serial.println("START");
        }
  if (ps2.getval(p_select)==0) {
    Serial.println("SELECT");
                }
  if (motori==0) { // ferma i motori se la variabile è uguale a 0
       analogWrite (E1,0); 
  digitalWrite(M1,LOW);    
  analogWrite (E2,0);    
  digitalWrite(M2,LOW);
}
  sensorValue = analogRead(FOTORES);
  Serial.println(sensorValue); 
 if (sensorValue<30 || stato==0) {
   // {  
    digitalWrite(RELAY, HIGH);
        }
else 
{
  digitalWrite(RELAY, LOW);  
delay(100);  
{
  //non fa niente
  }
}
}
