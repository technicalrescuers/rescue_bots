int trigPin = 8;
int echoPin = 9;
float pingTime;
float speedOfSound = 343.; // in meters per second
float distance;

void setup() {
  Serial.begin(2400);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2000);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pingTime = pulseIn(echoPin, HIGH);
  pingTime = pingTime / 1000000.; // In seconds

  distance = 0.5 * speedOfSound * pingTime;

  Serial.print("The distance is: ");
  Serial.print(distance);
  Serial.println(" meters.");
  delay(200);
}
