/*   -----------------------------------------------------------
     |  Theia Music Visualizer Code for Arduino                |
     -----------------------------------------------------------

     Some code was modified from http://ardx.org/CIRC03
*/

int ccw_motor_pin = 9; 
int cw_motor_pin = 10; 

int blue_violet_laser_pin = 12;

int green_laser_pin = 13;

int current_motor_pin = ccw_motor_pin;

int MIN_MOTOR_SPEED = 115;
int MAX_MOTOR_SPEED = 255;

int STROBE_DELAY = 175;

/*
   setup() - this function runs once when you turn your Arduino on
*/
void setup()
{
  pinMode(ccw_motor_pin, OUTPUT);
  pinMode(cw_motor_pin, OUTPUT);
  pinMode(blue_violet_laser_pin, OUTPUT);
  pinMode(green_laser_pin, OUTPUT);
  digitalWrite(ccw_motor_pin, LOW);
  digitalWrite(cw_motor_pin, LOW);

  digitalWrite(blue_violet_laser_pin, HIGH);
  digitalWrite(green_laser_pin, LOW);
}


void loop()
{
  //motorOnThenOff();
  //motorOnThenOffWithSpeed();
  //motorAcceleration();

  motorAccelerationRandom();

  int spins = random(0, 7);
  for (int i = 0; i < spins; i++) {
    spinShape();
  }
}

void strobeLasers() {
  digitalWrite(blue_violet_laser_pin, HIGH);
  digitalWrite(green_laser_pin, LOW);
  delay(STROBE_DELAY);
  digitalWrite(blue_violet_laser_pin, LOW);
  digitalWrite(green_laser_pin, HIGH);
  delay(STROBE_DELAY);
}

/*
   motorOnThenOff() - turns motor on then off
   (notice this code is identical to the code we used for
   the blinking LED)
*/
void motorOnThenOff() {
  int onTime = 2500;  //the number of milliseconds for the motor to turn on for
  int offTime = 1000; //the number of milliseconds for the motor to turn off for

  digitalWrite(current_motor_pin, HIGH); // turns the motor On
  delay(onTime);                // waits for onTime milliseconds
  digitalWrite(current_motor_pin, LOW);  // turns the motor Off
  delay(offTime);               // waits for offTime milliseconds
}

/*
   motorOnThenOffWithSpeed() - turns motor on then off but uses speed values as well
   (notice this code is identical to the code we used for
   the blinking LED)
*/
void motorOnThenOffWithSpeed() {

  int onSpeed = 200;  // a number between 0 (stopped) and 255 (full speed)
  int onTime = 2500;  //the number of milliseconds for the motor to turn on for

  int offSpeed = 50;  // a number between 0 (stopped) and 255 (full speed)
  int offTime = 1000; //the number of milliseconds for the motor to turn off for

  analogWrite(current_motor_pin, onSpeed);   // turns the motor On
  delay(onTime);                    // waits for onTime milliseconds
  analogWrite(current_motor_pin, offSpeed);  // turns the motor Off
  delay(offTime);                   // waits for offTime milliseconds
}

/*
   motorAcceleration() - accelerates the motor to full speed then
   back down to zero
*/
void motorAcceleration() {
  int delayTime = 100; //milliseconds between each speed step

  //Accelerates the motor
  for (int i = MIN_MOTOR_SPEED; i < 256; i++) { //goes through each speed from 0 to 255
    analogWrite(current_motor_pin, i);   //sets the new speed
    delay(delayTime);           // waits for delayTime milliseconds
  }

  //Decelerates the motor
  for (int i = 255; i >= 45; i--) { //goes through each speed from 255 to 0
    analogWrite(current_motor_pin, i);   //sets the new speed
    delay(delayTime);           // waits for delayTime milliseconds
  }
}

void motorAccelerationRandom() {
  analogWrite(current_motor_pin, random(MIN_MOTOR_SPEED, MAX_MOTOR_SPEED));

  delay(random(7500, 30000));
}

void spinShape() {
  analogWrite(current_motor_pin, MAX_MOTOR_SPEED);
  
  for (int i = 0; i < 3; i++) {
    strobeLasers();
  }
  
  swapDirections();
}

void swapDirections() {
  //turn off both parts of H-bridge
  digitalWrite(ccw_motor_pin, LOW);
  digitalWrite(cw_motor_pin, LOW);

  //swap motor pin
  if (current_motor_pin == ccw_motor_pin) {
    current_motor_pin = cw_motor_pin;
  } else {
    current_motor_pin = ccw_motor_pin;
  }

  //turn on appropriate half of h-bridge
  digitalWrite(current_motor_pin, HIGH);
}
