void mvMotors(bool dirL, bool dirR, int speedL, int speedR){
  digitalWrite(M1, dirL);
  digitalWrite(M2, dirR);
  analogWrite(E1, speedL);
  analogWrite(E2, speedR);
}
