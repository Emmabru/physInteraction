/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* Crated by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/
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
int ledLight[5] = { 0,lampa1, lampa2, lampa3, lampa4};
// Save up starting values from diods
int spotValue[4];

// defines variables
long duration;
int distance;
long duration2;
int distance2;

int blinks = 0;
int i;
int blinkDelay = 1;

int callDist = 300;
int talkDist = 150;
int patience= 200;


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



for(int i = 1; i < 5 ; i++) {
  spotValue[i] = analogRead(i);
  digitalWrite(ledLight[i], HIGH);
 
}

Serial.begin(9600); // Starts the serial communication
}

void loop() {
// Clears the trigPin1   **********************************
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

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
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration2 = pulseIn(echoPin2, HIGH);

// Calculating the distance
distance2= duration2*0.034/2;
      
// Prints the distance on the Serial Monitor
if (distance < callDist || distance2 < callDist){
      Serial.print("Hey Come here, read a book!     --->     ");

        digitalWrite(lampa1, HIGH);   // turn the LED on (HIGH is the voltage level)
        digitalWrite(lampa2, HIGH); 
        digitalWrite(lampa3, HIGH); 
        digitalWrite(lampa4, HIGH); 
        delay(100);                       // wait for a second
        digitalWrite(lampa1, LOW); 
        digitalWrite(lampa2, LOW); 
        digitalWrite(lampa3, LOW); 
        digitalWrite(lampa4, LOW); 

      Serial.print(distance);
      Serial.print("    ");
      Serial.println(distance2);
      delay(patience);
  
      if (distance < talkDist || distance2 < talkDist) {
        Serial.print("Fun! Grab a book and I'll talk about it! ");
      Serial.print(distance);
      Serial.print("    ");
      Serial.println(distance2);
      delay(patience);

      //        LIGHTS                 **********************************           LIGHTS
      for(i = 0; i < blinks ; i++){
        digitalWrite(lampa2, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(1000);                       // wait for a second
        digitalWrite(lampa2, LOW); 
      }
      
      //        BOOKS                   *********************************           BOOKS
      
      //timer for loop, until it looks at distance again
      uint32_t period = 5 * 10000L;       // 1 minutes

      for( uint32_t tStart = millis();  (millis()-tStart) < period;  ){

          //Resistance
          delay(1500);
          sensorValue = analogRead(0);
            
            // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
            float voltage = sensorValue * (3.5 / 1024.0);
          
            float I = voltage / 100;
            float VRx = 3.5 - voltage;
            float Rx = VRx / I;
            Rx = (3.5 - voltage) / I;
          
          
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
          
          //What book was taken   **************************************
         if (Rx < 192) {
            Serial.print("No book was taken    --> ");
            Serial.println(Rx);
            delay(1000);
          
          } else if (Rx > 191){   // Delay to stabalize values
              delay(1000);

              //if book is taken, from what spot
              int max = 0;
              int testValue = 0;
              int spot = 0;
              for(int i = 1; i < 5 ; i++) {
                testValue = spotValue[i] - analogRead(i);
                 if(testValue > max) {
                  max = testValue;
                  spot = i;
                  }
                }

                digitalWrite(ledLight[spot], LOW);
        
               Serial.print("Släck lampa ");
               Serial.println(spot);
              
              if ( Rx > 206) {
                Serial.print("HUNDTJUVEN    --> ");
                Serial.print(Rx);
                Serial.print("    ");
                Serial.println(analogRead(1));
                tStart = millis();       // restart timer
                
              
              } else if (205 < Rx && Rx < 213) {
                Serial.print("SNURRAN    --> ");
                Serial.print(Rx);
                Serial.print("    ");
                Serial.println(analogRead(2));
                tStart = millis();       // restart timer
                }
                
              } else if (199 < Rx && Rx < 206) {
                Serial.print("HUS ÄR GOTT    --> ");
                Serial.print(Rx);
                Serial.print("    ");
                Serial.println(analogRead(3));
                tStart = millis();       // restart timer
                
              } else if (200 > Rx) {
                Serial.print("KATTRESAN    --> ");
                Serial.print(Rx);
                Serial.print("    ");
                Serial.println(analogRead(4));
                tStart = millis();       // restart timer
              }
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
      Serial.println(" ");  
}


