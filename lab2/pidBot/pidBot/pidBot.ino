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
double avg;
const int avgNum = 8;
double vals[avgNum];
double sum = 0;
int i=0;

/* PID */
int maxDist = 620;
int desiredDist = 350;
double deltaX = 0;
double Kp = 1;
double P = 0;
double Ki = 1;
double I = 0;
double Kd = 1;
double D = 0;
double output;
double err;

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
  vals[i] = abs(max(-analogRead(sharp) + 630.0,0.0)); // force closest possible distance to 0, farthest possible to 630
  for (int j=0;j<avgNum;j++){ sum = sum + vals[j]; }
  avg = abs(sum/avgNum);  sum = 0;
  i++; if(i%avgNum==0){i=0;}

  /* PID */
  deltaX = (desiredDist - avg); //range from -280 to 350  
  err = deltaX;
  P = Kp * err;
  output = P*Kp + I*Ki + D*Kd;
  mvBoth(output);

  /*********/
  /* DEBUG */
  /*********/
//  Serial.println(analogRead(sharp));
//  Serial.print(" | Both Motor Speeds: ");
  Serial.println(output); 
//  Serial.print(" | Avg: ");  Serial.println(avg);
//  mvMotors(mLfwd,mRfwd,spdL,spdR);
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
} // END VOID LOOP

/*************/
/* GRAVEYARD */
/*************/
  //dXscaled = map(deltaX, -280, 350, -155, 155)
  //want range from -155 to 155
//  if (deltaX >=0) {
//    //motorScaled = map(deltaX, 0, 350, 100, 255);
//  }
//  else {
//    //motorScaled = map(deltaX, -280, 0, -255, -100);
//  }
