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
// defines variables
long duration;
int distance;


//resistance
int sensorValue =0;
int analogPin0= 0;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}

void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
delay(3000);

//Resistance


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
  delay(3000);
}
