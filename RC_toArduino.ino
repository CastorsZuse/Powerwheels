const int rc_pin = 3; 
const int Extend_pin = 4;
const int Retract_pin = 9;
const int Position_pin = A5;
const int M1_engage = A0;
const int M2_engage = A1;
int RC_duration;
int RC_location;
int actual_location;
int deadband = 10;
void setup() {
  Serial.begin(115200);
  pinMode(rc_pin, INPUT);
  pinMode(Extend_pin, OUTPUT);
  pinMode(Retract_pin, OUTPUT);
  pinMode(M1_engage,OUTPUT);
  pinMode(M2_engage,OUTPUT);
  digitalWrite(Extend_pin, LOW);
  digitalWrite(Retract_pin, LOW);
}
void loop() {
  digitalWrite(M1_engage, HIGH);
  digitalWrite(M2_engage, HIGH);
  RC_duration = constrain(pulseIn(rc_pin, HIGH), 1000, 2000);
  RC_location = map(RC_duration, 1000, 2000, 046, 257);
  actual_location = analogRead(Position_pin);
  if((actual_location <= RC_location + deadband) && (actual_location >= RC_location - deadband)) {
    digitalWrite(Extend_pin, LOW);
    digitalWrite(Retract_pin, LOW);
    Serial.println("Idle");

  }

  if(actual_location > RC_location + deadband) {
    digitalWrite(Extend_pin, LOW); 
    digitalWrite(Retract_pin, HIGH);
    Serial.println("Retract");
  }

  if(actual_location < RC_location - deadband) {
    digitalWrite(Extend_pin, HIGH);
    digitalWrite(Retract_pin, LOW);
    Serial.println("Extend");
  }


  Serial.print("Duration: ");
  Serial.print(RC_duration);
  Serial.print("Location: ");
  Serial.print(RC_location);
  Serial.print("Actual Location: ");
  Serial.println(actual_location);
}
