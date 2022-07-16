const int lMotor = 9;
const int rMotor = 10;

float analogInput;

void setup() {
  //pin setup:
  pinMode(lMotor, OUTPUT);
  pinMode(rMotor, OUTPUT);

}

void loop() {
  delay(8000);
  forward(95.0);
  delay(8000);
  pause();
  delay(8000);
  forward(85.0);
  delay(8000);
  pause();
  delay(8000);
  forward(75.0);
  delay(8000);
  pause();
  delay(8000);
  forward(65.0);
  delay(8000);
  pause();
}

void forward(float dutyCycle) {
  analogInput = dutyCycle * 255.0 / 100.0;
  analogWrite(lMotor, analogInput / 1.1);
  analogWrite(rMotor, analogInput);
}

void pause() {
  analogWrite(lMotor, 0);
  analogWrite(rMotor, 0);
}

