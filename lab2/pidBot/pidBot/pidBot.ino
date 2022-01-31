#define E1 5 //left motor pwm
#define E2 6 //right motor pwm
#define M1 4 //left motor fwd/rev
#define M2 7 //right motor fwd/rev
#define sharp A2 //sharp sensor

int spdL = 100;
int spdR = 100;
bool mLfwd = true;
bool mRfwd = true;

void setup() {
  // put your setup code here, to run once:
  for(int i=4;i<=7;i++){pinMode(i,OUTPUT);}
  digitalWrite(E1,LOW);  
  digitalWrite(E2,LOW);  
  digitalWrite(M1,LOW);  
  digitalWrite(M2,LOW);
  pinMode(sharp, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(sharp));
  mvMotors(mLfwd,mRfwd,spdL,spdR);
}
