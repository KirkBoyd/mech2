#define E1 5 //left motor pwm
#define E2 6 //right motor pwm
#define M1 4 //left motor fwd/rev
#define M2 7 //right motor fwd/rev
#define sharp A2 //sharp sensor

/* MOTOR */
int maxSpd = 255;
int minSpd = 100;
int spdL = maxSpd;
int spdR = spdL;
bool mLfwd = !true;
bool mRfwd = !true;
int motorScaled;

/* FILTER */
int avg;
const int avgNum = 16;
int vals[avgNum];
int sum = 0;
int i=0;

/* PID */
int maxDist = 620;
int desiredDist = 350;
int deltaX = 0;

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
  
  

  /* FILTER */
  vals[i] = analogRead(sharp);
  for (int j=0;j<avgNum;j++){ sum = sum + vals[j]; }
  avg = sum/avgNum;  sum = 0;
  Serial.print(" | Avg: ");  Serial.print(avg);
  i++; if(i%avgNum==0){i=0;}

  /* PID */
  deltaX = (desiredDist - avg);
//  mvMotors(-spdL,-spdR);
  Serial.print(" | deltaX: ");  Serial.print(deltaX);
//  if(deltaX > 0){ mLfwd = true; mRfwd = true; }
//  else{ mLfwd = false; mRfwd = false; }
  if (deltaX >=0) {
    motorScaled = map(deltaX, 0, 350, 100, 255);
  }
  else {
    motorScaled = map(deltaX, -280, 0, -255, -100);
  }
//  motorScaled = map(deltaX, -280, 350, -255, 255);
  mvMotors(-motorScaled, -motorScaled);
  Serial.print(" | Both Motor Speeds: ");
  Serial.println(motorScaled); 
}

/* DEBUG */
//mvMotors(mLfwd,mRfwd,spdL,spdR);
//Serial.println(analogRead(sharp));
//  Serial.print("i: ");
//  Serial.print(i);
//  Serial.print(" | Raw: ");
//  Serial.print(vals[i]);
//    Serial.print(" | Sum: ");
//    Serial.print(sum);
//  digitalWrite(M1, mLfwd);
//  digitalWrite(M2, mRfwd);
//  analogWrite(E1, spdL);
//  analogWrite(E2, spdR);
