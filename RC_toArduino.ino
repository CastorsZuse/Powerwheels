const int rc_pin = 4; 
const int Extend_pin = 7;
const int Retract_pin = 8;
const int Position_pin = A5;
const int M1_engage = A0;
const int M1_engage = A0;
int RC_duration;
int RC_location;
int actual_location;
int deadband = 10;

void setup() {
  pinMode(rc_pin, INPUT);
  pinMode(Extend_pin, OUTPUT);
  pinMode(Retract_pin, OUTPUT);
  pinMode(M1_engage,OUTPUT);
  digitalWrite(Extend_pin, LOW);
  digitalWrite(Retract_pin, LOW);
}

void loop() {
  digitalWrite(M1_engage, HIGH);
  RC_duration = constrain(pulseIn(rc_pin, HIGH), 1000, 2000);
  RC_location = map(RC_duration, 1000, 2000, 056, 257);


  actual_location = analogRead(Position_pin);

  if((actual_location <= RC_location + deadband) && (actual_location >= RC_location - deadband)) {
    digitalWrite(Extend_pin, LOW);
    digitalWrite(Retract_pin, LOW);
  }

  if(actual_location > RC_location + deadband) {
    digitalWrite(Extend_pin, LOW); 
    digitalWrite(Retract_pin, HIGH);
  }

  if(actual_location < RC_location - deadband) {
    digitalWrite(Extend_pin, HIGH);
    digitalWrite(Retract_pin, LOW);
  }

  delay(50);
}