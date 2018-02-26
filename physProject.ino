/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* Crated by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/
//DISTANCE
// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int trigPin2 = 11;
const int echoPin2 = 12;
const int lampa2 = 2;

// defines variables
long duration;
int distance;
long duration2;
int distance2;

int blinks = 0;
int i;
int blinkDelay = 300;

int callDist = 20;
int talkDist = 5;
int patience= 5000;


//resistance
int sensorValue =0;
int analogPin0= 0;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
pinMode(lampa2, OUTPUT);
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
if ((distance || distance2 < callDist)){
      Serial.print("Hey Come here, read a book!     --->     ");
      Serial.print(distance);
      Serial.print("    ");
      Serial.println(distance2);
      delay(patience);
  
      if (distance || distance2 < talkDist) {
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
          
          /*
            Serial.println(" "); 
            Serial.print(Rx);
            Serial.println(" Ohms");
            Serial.print("Bok 1: ");
            Serial.println(analogRead(1));
            Serial.print("Bok 2: ");
            Serial.println(analogRead(2));
            Serial.print("Bok 3: ");
            Serial.println(analogRead(3));
            Serial.print("Bok 4: ");
            Serial.println(analogRead(4));
            //  Serial.print("Resistance 4: ");
            //Serial.print(analogRead(4));
           // Serial.println(" Ohms");
            delay(2000);*/
          
          //What book was taken   **************************************
          if (Rx < 175) {
            Serial.print("No book was taken    --> ");
            Serial.println(Rx);
            delay(1000);
          
          } else if (Rx > 174){   // Delay to stabalize values
              delay(1000);
              
              if (177 < Rx && Rx < 184) {
                Serial.print("Bok 1 was taken    --> ");
                Serial.print(Rx);
                Serial.print("    ");
                Serial.println(analogRead(1));
                tStart = millis();       // restart timer
                blinks = 1;
                for(i = 0; i < blinks ; i++){
                  digitalWrite(lampa2, HIGH);   // turn the LED on (HIGH is the voltage level)
                  delay(blinkDelay/blinks);                       // wait for a second
                  digitalWrite(lampa2, LOW); 
                }
              
              } else if (183 < Rx && Rx < 187) {
                Serial.print("Bok 2 was taken    --> ");
                Serial.print(Rx);
                Serial.print("    ");
                Serial.println(analogRead(2));
                tStart = millis();       // restart timer
                blinks = 2;
                for(i = 0; i < blinks ; i++){
                  digitalWrite(lampa2, HIGH);   // turn the LED on (HIGH is the voltage level)
                  delay(blinkDelay/blinks);                       // wait for a second
                  digitalWrite(lampa2, LOW); 
                }
                
              } else if (186 < Rx && Rx < 205) {
                Serial.print("Bok 3 was taken    --> ");
                Serial.print(Rx);
                Serial.print("    ");
                Serial.println(analogRead(3));
                tStart = millis();       // restart timer
                blinks = 3;
                for(i = 0; i < blinks ; i++){
                  digitalWrite(lampa2, HIGH);   // turn the LED on (HIGH is the voltage level)
                  delay(blinkDelay/blinks);                       // wait for a second
                  digitalWrite(lampa2, LOW); 
                }
                
              } else if (199 < Rx) {
                Serial.print("Bok 4 was taken    --> ");
                Serial.print(Rx);
                Serial.print("    ");
                Serial.println(analogRead(4));
                tStart = millis();       // restart timer
                blinks = 4;
                for(i = 0; i < blinks ; i++){
                  digitalWrite(lampa2, HIGH);   // turn the LED on (HIGH is the voltage level)
                  delay(blinkDelay/blinks);                       // wait for a second
                  digitalWrite(lampa2, LOW); 
                }
              }
          }
      }
  /*
    start 165                         170.18
  1   (100) 216-219   bok 4           210-211.30      478-480
  2   (150) 185 bok 3-4 mer 3         192-194.25      347-349
  3   (180) 181-187,6 bok 3           194-198.54      340-346
  4  (220) 182,87 bok 2??             190.81-201      351-358
    */
     }
      Serial.println(" ");  
  }

}
