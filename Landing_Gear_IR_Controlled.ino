#include <IRremote.h> 

const int irReceiverPin = 6;  
const int enA = 9;
const int in1 = 4;
const int in2 = 5;
 
IRrecv irrecv(irReceiverPin); 
decode_results results;   
 
void setup()
{
  Serial.begin(9600);   
  irrecv.enableIRIn();

  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}
 
void loop() 
{
  if (irrecv.decode(&results)) 
  {  
    Serial.print("irCode: ");            
    Serial.print(results.value, HEX); 
    Serial.print(",  bits: ");           
    Serial.println(results.bits); 
    irrecv.resume();    
  }  
  delay(20); 

 if (results.value == 0x68733A46){ // vol+
  Serial.println("forward");
  forward();
 }
 if (results.value == 0x83B19366) { // vol-
  Serial.println("reverse");
  reverse();
 }
// else{
//  Serial.println("stop");  
//  stoped();
// }
 
 
 if (results.value == 0x5F12E8C4) {// ch up
  Serial.println("stop");
  stoped();
  }
}

void forward(){
  analogWrite(enA,255);
  digitalWrite(in1, LOW);
  digitalWrite(in2,HIGH);
  delay(50);
}

void reverse(){
  analogWrite(enA,255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2,LOW);
  delay(50);
}

void stoped(){
  analogWrite(enA,0);
  delay(50);
}
