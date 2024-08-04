#define outputPin0 16
#define outputPin1 17
#define outputPin2 18
#define outputPin3 19

void forward(uint32_t pwm);
void slowly_left(uint32_t pwm);
void rapidly_left(uint32_t pwm);
void slowly_right(uint32_t pwm);
void nothing(void);
void back_slowly_left(uint32_t pwm);
void rapidly_right(uint32_t pwm);
void back_slowly_right(uint32_t pwm);
void backward(uint32_t pwm);
void stop(void);


uint32_t pwm = 255;
bool boost = false;

void setup() {
  Serial.begin(115200);

  pinMode(outputPin0, OUTPUT);
  pinMode(outputPin1, OUTPUT);
  pinMode(outputPin2, OUTPUT);
  pinMode(outputPin3, OUTPUT);

  ledcAttach(outputPin0, 5000, 8);
  ledcAttach(outputPin1, 5000, 8);
  ledcAttach(outputPin2, 5000, 8);
  ledcAttach(outputPin3, 5000, 8);
}

void loop() {
  forward(pwm);
  delay(10000);
  stop();

  slowly_left(pwm);
  delay(10000);
  stop();

  rapidly_left(pwm);
  delay(10000);
  stop();

  slowly_right(pwm);
  delay(10000);
  stop();

  rapidly_right(pwm); 
  delay(10000);
  stop();

  nothing();
  delay(10000);
  stop();

  back_slowly_left(pwm);
  delay(10000);
  stop();

  back_slowly_right(pwm);
  delay(10000);
  stop();

  backward(pwm);
  delay(10000);
  stop();
}

void forward(uint32_t pwm) {
  ledcWrite(outputPin0,pwm);
  ledcWrite(outputPin1,0);
  ledcWrite(outputPin2,pwm);
  ledcWrite(outputPin3,0);
}
void slowly_left(uint32_t pwm) {
  ledcWrite(outputPin0,pwm);
  ledcWrite(outputPin1,0);
  ledcWrite(outputPin2,0);
  ledcWrite(outputPin3,0);
}
void rapidly_left(uint32_t pwm) {
  ledcWrite(outputPin0,pwm);
  ledcWrite(outputPin1,0);
  ledcWrite(outputPin2,0);
  ledcWrite(outputPin3,pwm);
}
void slowly_right(uint32_t pwm) {
  ledcWrite(outputPin0,0);
  ledcWrite(outputPin1,0);
  ledcWrite(outputPin2,pwm);
  ledcWrite(outputPin3,0);
}
void nothing(void){
  ledcWrite(outputPin0,0);
  ledcWrite(outputPin1,0);
  ledcWrite(outputPin2,0);
  ledcWrite(outputPin3,0);
}
void back_slowly_left(uint32_t pwm) {
  ledcWrite(outputPin0,0);
  ledcWrite(outputPin1,0);
  ledcWrite(outputPin2,0);
  ledcWrite(outputPin3,pwm);
}
void rapidly_right(uint32_t pwm) {
  ledcWrite(outputPin0,0);
  ledcWrite(outputPin1,pwm);
  ledcWrite(outputPin2,pwm);
  ledcWrite(outputPin3,0);
}
void back_slowly_right(uint32_t pwm) {
  ledcWrite(outputPin0,0);
  ledcWrite(outputPin1,pwm);
  ledcWrite(outputPin2,0);
  ledcWrite(outputPin3,0);
}
void backward(uint32_t pwm) {
  ledcWrite(outputPin0,0);
  ledcWrite(outputPin1,pwm);
  ledcWrite(outputPin2,0);
  ledcWrite(outputPin3,pwm);
}
void stop(void){
  ledcWrite(outputPin0,255);
  ledcWrite(outputPin1,255);
  ledcWrite(outputPin2,255);
  ledcWrite(outputPin3,255);
}
