#define outputPin0 32
#define outputPin1 33
#define outputPin2 26
#define outputPin3 25

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


uint32_t pwm = 250;
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
  ledcWrite(0,pwm);
  ledcWrite(1,0);
  ledcWrite(2,pwm);
  ledcWrite(3,0);
}
void slowly_left(uint32_t pwm) {
  ledcWrite(0,pwm);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,0);
}
void rapidly_left(uint32_t pwm) {
  ledcWrite(0,pwm);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,pwm);
}
void slowly_right(uint32_t pwm) {
  ledcWrite(0,0);
  ledcWrite(1,0);
  ledcWrite(2,pwm);
  ledcWrite(3,0);
}
void nothing(void){
  ledcWrite(0,0);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,0);
}
void back_slowly_left(uint32_t pwm) {
  ledcWrite(0,0);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,pwm);
}
void rapidly_right(uint32_t pwm) {
  ledcWrite(0,0);
  ledcWrite(1,pwm);
  ledcWrite(2,pwm);
  ledcWrite(3,0);
}
void back_slowly_right(uint32_t pwm) {
  ledcWrite(0,0);
  ledcWrite(1,pwm);
  ledcWrite(2,0);
  ledcWrite(3,0);
}
void backward(uint32_t pwm) {
  ledcWrite(0,0);
  ledcWrite(1,pwm);
  ledcWrite(2,0);
  ledcWrite(3,pwm);
}
void stop(void){
  ledcWrite(0,255);
  ledcWrite(1,255);
  ledcWrite(2,255);
  ledcWrite(3,255);
}
