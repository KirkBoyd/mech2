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
int raw;
double avg;
const int avgNum = 4;
double vals[avgNum];
double sum = 0;
int i=0;

/* PID */
double desiredDist = 10.0;
double Kp = 25;
double P = 0;
double Ki = 0;
double I = 0;
double Kd = 0;
double D = 0;
double output;
double err;
unsigned long currentTime = 0;
unsigned long prevTime = 0;
double lastAvg = 0;
double deltaAvg = 0;
double deltaT = 0;
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
  Serial.begin(115200);
}

void loop() {
  /* FILTER */
  raw = analogRead(sharp);
  vals[i] = sharp_calib(raw);
  for (int j=0; j<avgNum; j++) {
    sum = sum + vals[j];
  }
  avg = sum/double(avgNum);
  sum = 0;
  i++;
  if (i%avgNum == 0) {
    i=0;
  }

  /* PID */
  err = (desiredDist - avg);

  cumulErr = cumulErr + err*deltaT;
  cumulErr = constrain(cumulErr, minI, maxI);

  deltaAvg = avg - lastAvg;
  currentTime = millis();
  deltaT = double(currentTime-prevTime)/1000.0;
  prevTime = currentTime;
  deriv = deltaAvg / deltaT;

  P = Kp * err;
  I = Ki * cumulErr;
  D = Kd * deriv;
  output = P + I + D;
  mvBoth(int(output));
  prevTime = currentTime; // store time from beginning of loop to compare
  lastAvg = avg;
  delay(1);

  Serial.print(P);Serial.print('\t');
  Serial.print(I);Serial.print('\t');
  Serial.print(D);Serial.print('\t');
  Serial.print(avg);Serial.print('\t');
  Serial.print(desiredDist);Serial.print('\t');
  Serial.println();
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


/********************/
/* HELPER FUNCTIONS */
/********************/

// Calibration function mapping the analog input to a distance in inches.
// Params:
//  raw - (int) direct reading from analogRead() of sharp sensor
// Returns:
//  (double) estimated distance in inches
double sharp_calib(int raw) {
  // obtained these constants by collecting data and using scipy's curve_fit()
  static const double CALIB_A = 2.37092463e+03;
  static const double CALIB_B = -1.39181488e+00;

  return CALIB_A/double(raw) + CALIB_B;
}