int analogIN = 0;
int potPin = A3;
int b = 9;
int r = 10;
int g = 11;

void setup() {
  Serial.begin(9600);
  pinMode(potPin, INPUT);
  pinMode(b, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  analogReference(DEFAULT);
}
  
void loop() {
  analogIN = analogRead(potPin);
  if(analogIN < 25){
    digitalWrite(b, HIGH);
    digitalWrite(g, HIGH);
    digitalWrite(r, LOW);
  }
  else{
    digitalWrite(b, LOW);
    digitalWrite(g, LOW);
    digitalWrite(r, HIGH);

  }
  delay(35);
}
