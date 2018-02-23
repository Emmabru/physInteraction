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

// Prints the distance on the Serial Monitor
if (distance < 300) {
 // Serial.println(" HEY left BUDDY! COME ON OVER!");
  
  if (distance < 150) {
   // Serial.println(" WANNA READ A BOOK?!?!");
  }  
}
//Serial.print("Distance left: ");
//Serial.println(distance);
//delay(2000);

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
//Serial.print("Distance Right: ");
//Serial.println(distance2);
//delay(3000);

//lights                  **********************************
//digitalWrite(lampa2, );   // turn the LED on (HIGH is the voltage level)
//delay(1000);                       // wait for a second
digitalWrite(lampa2, LOW); 


// Books                   *********************************

//Resistance
delay(1500);
sensorValue = analogRead(0);
  
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (3.5 / 1024.0);

  float I = voltage / 100;
  float VRx = 3.5 - voltage;
  float Rx = VRx / I;
  Rx = (3.5 - voltage) / I;

  // print out the value you read:
  //Serial.println("Vilken Bok: ");
  /*if(Rx > 1700)
  {
   Serial.println("#S|LILLBOKEN|[]#");

    }
else if(Rx > 1500)
      {
    Serial.println("#S|STORBOKEN|[]#");

    }*/
  Serial.println(" "); 
  Serial.print(Rx);
  Serial.println(" Ohms");
  /*Serial.print("Bok 1: ");
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

} else if (Rx > 174){   // Delay to stabalize values
    delay(1000);
    
    if (175 < Rx && Rx < 184) {
      Serial.print("Bok 1 was taken    --> ");
      Serial.print(Rx);
      Serial.print("    ");
      Serial.println(analogRead(1));
    
    } else if (183 < Rx && Rx < 187) {
      Serial.print("Bok 2 was taken    --> ");
      Serial.print(Rx);
      Serial.print("    ");
      Serial.println(analogRead(2));
      
    } else if (186 < Rx && Rx < 205) {
      Serial.print("Bok 3 was taken    --> ");
      Serial.print(Rx);
      Serial.print("    ");
      Serial.println(analogRead(3));
      
    } else if (199 < Rx) {
      Serial.print("Bok 4 was taken    --> ");
      Serial.print(Rx);
      Serial.print("    ");
      Serial.println(analogRead(4));
    }
}
/*
  start 165
1   (100) 216-219   bok 4
2   (150) 195-201 bok 3-4 mer 3  
3   (180) 181-187,6 bok 3
4  (220) 182,87 bok 2??
  */
}
