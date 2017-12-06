/*************************
  Joel Bartlett
  SparkFun Electronics
  December 27, 2012

  This code controls a stepper motor with the
  EasyDriver board. It spins forwards and backwards
***************************/
//FSR
int fsrAnalogPin = 0;
int fsrReading;      // the analog reading from the FSR resistor divider

//Stepper Motor
int dirpin = 4;
int steppin = 9;

int state = 0;
int statePrev = 0;
// 0 - no step
// 1 - someone is steping (FSR > 100)

int stepsForward = 6000;
int initStepDelay = 200; //ms
int interStepDelay = 1000; // microsec

void setup() {
  Serial.begin(9600);

  //Stepper Motor
  pinMode(dirpin, OUTPUT);
  pinMode(steppin, OUTPUT);
}

void behavior1() {
  int i;
  digitalWrite(dirpin, LOW);     // Set the direction.
  delay(initStepDelay);

  for (i = 0; i < stepsForward; i++) {    // Iterate for 4000 microsteps.
    digitalWrite(steppin, LOW);  // This LOW to HIGH change is what creates the
    digitalWrite(steppin, HIGH); // "Rising Edge" so the easydriver knows to when to step.
    delayMicroseconds(interStepDelay);      // This delay time is close to top speed for this
  }

delay(3000);

  digitalWrite(dirpin, HIGH);    // Change direction.
  delay(initStepDelay);


  for (i = 0; i < stepsForward; i++) {   // Iterate for 4000 microsteps

    digitalWrite(steppin, LOW);  // This LOW to HIGH change is what creates the
    digitalWrite(steppin, HIGH); // "Rising Edge" so the easydriver knows to when to step.
    delayMicroseconds(interStepDelay);      // This delay time is close to top speed for this
  }
}

void loop() {
  //FSR
  fsrReading = analogRead(fsrAnalogPin);

  Serial.print("Analog reading = ");
  Serial.print(fsrReading);
  Serial.print(" ; state = ");
  Serial.print(state);
  Serial.print(" statePrev = ");
  Serial.println(statePrev);
  delay(500);

  if (fsrReading > 500) {
    statePrev = state;
    state = 1; //i've stepped on
    if (statePrev == 0) { //was i stepping on it before

      behavior1();
    }


  } else {
    statePrev = state;
    state = 0; //i've stepped off

  }


}


