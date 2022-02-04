void mvMotors(int speedL, int speedR){ //pass negative values of speed to reverse motor direction
  bool dirL;
  bool dirR;
  if(speedL>=0){dirL=true;}
  else{dirL=false;}
  if (speedR>=0){dirR = true;}
  else{dirR = false;}
  digitalWrite(M1, dirL);
  digitalWrite(M2, dirR);
  analogWrite(E1, abs(speedL));
  analogWrite(E2, abs(speedR));
}
