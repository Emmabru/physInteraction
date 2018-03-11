/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* Crated by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*
*släck rätt lampa
*t'nd den sen igen
*ljud - gobetweenO
*/
#include <elapsedMillis.h>

elapsedMillis timeElapsed;

//DISTANCE
// defines pins numbers
const int trigPin = 6;
const int echoPin = 7;
const int trigPin2 = 4;
const int echoPin2 = 5;


const int lampa1 = 13;
const int lampa2 = 12;
const int lampa3 = 11;
const int lampa4 = 10;
int ledLight[4] = { lampa2, lampa1, lampa3, lampa4};
// Save up starting values from diods
int spotValue[4];
int temp[4];
// defines variables
long duration;
int distance;
long duration2;
int distance2=1000;
bool first[4] ={ true,true,true,true};

int blinks = 0;
int i;
int blinkDelay = 1;

int callDist = 220;
int talkDist = 20;
int patience= 200;
bool hej = true;
bool ins = true;

//resistance
int sensorValue =0;
int analogPin0= 0;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin2, INPUT); // Sets the echoPin as an Input

pinMode(lampa1, OUTPUT);
pinMode(lampa2, OUTPUT);
pinMode(lampa3, OUTPUT);
pinMode(lampa4, OUTPUT);



for(int i = 0; i < 4 ; i++) {
  spotValue[i] = analogRead(i+1);
//  digitalWrite(ledLight[i], HIGH);
 
}

Serial.begin(9600); // Starts the serial communication
}

void loop() {
// Clears the trigPin1   **********************************
digitalWrite(trigPin, LOW);
//delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
//delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;
  
// Clears the trigPin2    **********************************
digitalWrite(trigPin2, LOW);
//delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin2, HIGH);
//delayMicroseconds(10);
digitalWrite(trigPin2, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration2 = pulseIn(echoPin2, HIGH);

// Calculating the distance
//distance2= duration2*0.034/2;
       /*  Serial.print(distance);
      Serial.print("    ");
      Serial.println(distance2);
      delay(patience);*/
// Prints the distance on the Serial Monitor
if ((distance < callDist || distance2 < callDist)&& (distance2 != 0 && distance != 0)&& (distance2 != 95 || distance != 95)&& (distance2 != 94 || distance != 94)){
      //Serial.println("Hey Come here, read a book!     --->     ");
      if(hej){
        for(int i = 0; i < 4 ; i++) {
 // spotValue[i] = analogRead(i+1);
 delay(300);
// Serial.println(timeElapsed);
  digitalWrite(ledLight[i], HIGH);
 
}
      Serial.print("#S|");
                Serial.print("HEJ");
                   Serial.println("|[]#");
                   hej= false;}

   /*   Serial.print(distance);
      Serial.print("    ");
      Serial.println(distance2);
      delay(patience);*/
  
      if ((distance < talkDist || distance2 < talkDist) && (distance2 != 0 && distance != 0)) {
       // Serial.println("Fun! Grab a book and I'll talk about it! ");
        if(ins) {
         // timeElapsed = 0;
        Serial.print("#S|");
                Serial.print("INS");
                   Serial.println("|[]#");
                   ins = false;
                  // Serial.println(timeElapsed);
                   }
   /*  Serial.print(distance);
      Serial.print("    ");
      Serial.println(distance2);*/
      delay(patience);

      //        LIGHTS                 **********************************           LIGHTS
   /*   for(i = 0; i < blinks ; i++){
        digitalWrite(lampa2, HIGH);   // turn the LED on (HIGH is the voltage level)
        //delay(1000);                       // wait for a second
        digitalWrite(lampa2, LOW); 
      }
      */
      //        BOOKS                   *********************************           BOOKS
  /*     if (timeElapsed>5000 && timeElapsed < 12000)
      {
         Serial.println(timeElapsed);
        digitalWrite(lampa1, HIGH);
         digitalWrite(lampa2, LOW);
         digitalWrite(lampa3, LOW);
         digitalWrite(lampa4, LOW);
        
      }
      else if (timeElapsed>13000 && timeElapsed < 23000)
      {
        digitalWrite(lampa2, HIGH);
        digitalWrite(lampa1, LOW);
         digitalWrite(lampa3, LOW);
         digitalWrite(lampa4, LOW);
         
      }
       else if (timeElapsed>24000 && timeElapsed < 32000)
      {
        digitalWrite(lampa3, HIGH);
        digitalWrite(lampa2, LOW);
         digitalWrite(lampa1, LOW);
         digitalWrite(lampa4, LOW);
         
      }
       else if (timeElapsed>33000 && timeElapsed < 44000)
      {
        digitalWrite(lampa4, HIGH);
        digitalWrite(lampa2, LOW);
         digitalWrite(lampa3, LOW);
         digitalWrite(lampa1, LOW);
         
      }
       else if (timeElapsed>44000)
      {
        digitalWrite(lampa1, HIGH);
        digitalWrite(lampa2, HIGH);
        digitalWrite(lampa3, HIGH);
        digitalWrite(lampa4, HIGH);
      }*/
 
      //timer for loop, until it looks at distance again
      uint32_t period = 5 * 10000L;       // 1 minutes
    
      for( uint32_t tStart = millis();  (millis()-tStart) < period;  ){
             
          //Resistance
          //delay(1500);
          sensorValue = analogRead(0);
            
            // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
            float voltage = sensorValue * (3.5 / 1024.0);
          
            float I = voltage / 100;
            float VRx = 3.5 - voltage;
            float Rx = VRx / I;
            Rx = (3.5 - voltage) / I;
          
          /*
            Serial.println(" "); 
            Serial.print(Rx);
            Serial.println(" Ohms");
            Serial.print("ANALOG 1: ");
            Serial.println(analogRead(1));
            Serial.print("ANALOG 2: ");
            Serial.println(analogRead(2));
            Serial.print("ANALOG 3: ");
            Serial.println(analogRead(3));
            Serial.print("ANALOG 4: ");
            Serial.println(analogRead(4));
                
            delay(100);

*/
          
          //What book was taken   **************************************
         /*if (Rx < 192) {
            Serial.print("No book was taken    --> ");
            Serial.println(Rx);
            int max = 0;
              int testValue = 0;
              int spot = 0;

            for(int i = 0; i < 4 ; i++) {
               spotValue[i] = analogRead(i);
               digitalWrite(ledLight[i], HIGH);
             }
             digitalWrite(ledLight[spot], LOW);
        
               Serial.print("Släck lampa ");
               Serial.println(spot);
              
          
          } *///else if (Rx > 191){   // Delay to stabalize values
              delay(1000);

              //if book is taken, from what spot
              int maxIndex = 5;
             // int testValue = 0;
              int max = 0;
           temp[0] = analogRead(2)+analogRead(3)+analogRead(4)-analogRead(1);
            temp[1] = analogRead(1)+analogRead(3)+analogRead(4)-analogRead(2);
             temp[2] = analogRead(1)+analogRead(2)+analogRead(4)-analogRead(3);
              temp[3] = analogRead(2)+analogRead(3)+analogRead(1)-analogRead(4);
              for(int i = 0; i < 4 ; i++) {
          
                if(spotValue[i]-70> analogRead(i+1))
                {
                  if(first[i]){
                  digitalWrite(ledLight[i], LOW);
                   //Serial.println("ABCP" + i);
                   Serial.print("#S|");
                Serial.print("ABCP" + i);
                   Serial.println("|[]#");
                   
                 
                  // Serial.print("Släck lampa ");
               //Serial.println(i+1);
                   first[i]=false;
                  }
                 
            
                }
                 else {
                 if( first[i]==false)
                 {
                  Serial.print("#S|");
                 Serial.print("TYST");
                   Serial.println("|[]#");
                  
                 }
             
                  first[i] = true;
                    digitalWrite(ledLight[i], HIGH);
                    
                   // Serial.print("TYST"+ i);
                  
                 }
                }
               /* if (max !=0)
                {
                  digitalWrite(ledLight[maxIndex], LOW);
                }*/
                
                
                

                
        
               
              
             
                
              //}
          /*    if (200 > Rx) {
                Serial.print("KATTRESAN    --> "); //181
                Serial.print(Rx);
                Serial.print("    ");
                Serial.println(analogRead(4));
                tStart = millis();       // restart timer
              }
               else if (199 < Rx && Rx < 206) {
                Serial.print("HUS ÄR GOTT    --> "); //181 -182
                Serial.print(Rx);
                Serial.print("    ");
                Serial.println(analogRead(3));
                tStart = millis();       // restart timer
                
              }
              else if (205 < Rx && Rx < 213) {
                Serial.print("SNURRAN    --> "); // 193 194
                Serial.print(Rx);
                Serial.print("    ");
                Serial.println(analogRead(2));
                tStart = millis();       // restart timer
                }
               else  if ( Rx > 206) {
                Serial.print("HUNDTJUVEN    --> "); //202.6 201.18 202.06
                Serial.print(Rx);
                Serial.print("    ");
                Serial.println(analogRead(1));
                tStart = millis();       // restart timer
                
              
              }*/
          }
      }
  /*
    start 165                         170.18          163.92
  1   (100) 216-219   bok 4           210-211.30      203.86---200-206      197-->
  2   (150) 185 bok 3-4 mer 3         192-194.25      179.78 -191-196       188-->     
  3   (180) 181-187,6 bok 3           194-198.54      182.09---184-188:45   181-->
  4  (220) 182,87 bok 2??             190.81-201      190.91-----178-180    175-->


    181-186
  1 100-->  520     220         
  2 140 --> 518     210.67
  3 180 --> 505     202-204
  4 220 --> 504     198.5
  
  
  */
    }
     // Serial.println(" ");  
}


