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
long avg;
const int avgNum = 8;
long vals[avgNum];
long sum = 0;
int i=0;

/* PID */
int maxDist = 620;
int desiredDist = 350;
double deltaX = 0;
double Kp = 0.6;
double P = 0;
double Ki = 0.2;
double I = 0;
double Kd = 1;
double D = 0;
double output;
double err;
long currentTime = 0;
long prevTime = 0;
long lastAvg = 0;
long deltaAvg = 0;
long deltaT = 0;
double deriv;
double cumulErr;
int minI = -700;
int maxI = 700;

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
  currentTime = millis()/1000; // take clock input
  /* FILTER */
  vals[i] = abs(max(-analogRead(sharp) + 630.0,0.0)); // force closest possible distance to 0, farthest possible to 630
//  Serial.print("Data point taken at: ");
//  Serial.println(millis());
  for (int j=0;j<avgNum;j++){ sum = sum + vals[j]; }
  avg = abs(sum/avgNum);  sum = 0;
  i++; if(i%avgNum==0){i=0;}
  deltaAvg = avg - lastAvg;
  deltaT = currentTime - prevTime;
  deriv = deltaAvg / deltaT;

  

  /* PID */
  deltaX = (desiredDist - avg); //range from -280 to 350  
  err = deltaX;
  cumulErr = cumulErr + err*deltaT;
  cumulErr = constrain(cumulErr, minI, maxI);
  P = Kp * err;
  I = Ki * cumulErr;
  D = Kd * deriv;
  output = P + I + D;
  mvBoth(output);
  prevTime = currentTime; // store time from beginning of loop to compare
  lastAvg = avg;
  /*********/
  /* DEBUG */
  /*********/
//  Serial.println(analogRead(sharp));
//  Serial.print(" | Both Motor Speeds: ");
//  Serial.println(output); 
//  Serial.print("avg,");  
  Serial.print(avg);
  Serial.print("\t");  
  Serial.print(P);
  Serial.print("\t");  
  Serial.print(I);
  Serial.print("\t");  
  Serial.print(D);
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
