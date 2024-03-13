//code by Science Fun on youtube
//https://youtu.be/c7JtfogOsTQ?si=0qD5I2hjL-gD5Zv-

const int rc_pin = 7; 
const int Extend_pin = 10;
const int Retract_pin = 9;
const int Position_pin = A0;
int RC_duration;
int RC_location;
int actual_location;
int deadband = 20;

void setup() {
  Serial.begin(115200);
  pinMode(rc_pin, INPUT);
  pinMode(Extend_pin, OUTPUT);
  pinMode(Retract_pin, OUTPUT);
  digitalWrite(Extend_pin, LOW);
  digitalWrite(Retract_pin, LOW);
}

void loop() {
  
  RC_duration = constrain(pulseIn(rc_pin, HIGH), 1000, 2000);
  RC_location = map(RC_duration, 1000, 2000, 056, 257);

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
  
  delay(50);


  Serial.print("Duration: ");
  Serial.print(RC_duration);
  Serial.print("Location: ");
  Serial.print(RC_location);
  Serial.print("Actual Location: ");
  Serial.println(actual_location);
}
