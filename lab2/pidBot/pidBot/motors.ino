void mvMotors(int speedL, int speedR){ //pass negative values of speed to reverse motor direction
  bool dirL;
  bool dirR;
  // actually send to motors
  if(speedL>=0){dirL=true;}
  else{dirL=false;}
  if (speedR>=0){dirR = true;}
  else{dirR = false;}
  digitalWrite(M1, dirL);
  digitalWrite(M2, dirR);
  analogWrite(E1, abs(speedL));
  analogWrite(E2, abs(speedR));
}

void mvBoth(int spd){ //pass negative values of speed to reverse motor direction
  bool dir;

  // bring out immobile range
  if(spd<0){ 
    spd = constrain(map(spd, 0, -255, -135, -255),-255,0); 
  }// scrunch values to valid motor range
  else{ 
    spd = constrain(map(spd, 0, 255, 135, 255),0,255);
  } // scrunch values to valid motor range
  Serial.print(spd); Serial.print("\t");
  // actually send to motors
  if(spd>=0){dir=true;}
  else{dir=false;}
  digitalWrite(M1, dir);
  digitalWrite(M2, dir);
  analogWrite(E1, abs(spd));
  analogWrite(E2, abs(spd));
}
