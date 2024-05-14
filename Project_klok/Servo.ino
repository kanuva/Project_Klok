String ServoState = "Initialize"; //Possible states: RunClock, Idle or Initialize (all to 0)
Pwm pwm = Pwm();

//                          min Ones, Min Tens, Hour Ones,  Hour Tens
// pos:                     0        1          2           3
const int ServoPins [4] = { 3,       2,         1,          0};
int curPosition [4] = {     0,       0,         0,          0};
int NewPosition [4] = {     0,       0,         0,          0};

void HandleDigits(){
  if(ServoState == "RunClock"){
    NewPosition[0] = (rtc.getMinute() % 10) * 20;       //Minute Ones
    NewPosition[1] = (rtc.getMinute() / 10) * 20;       //Minute tens
    NewPosition[2] = (rtc.getHour(true) % 10) * 20;       //Hour Ones
    NewPosition[3] = (rtc.getHour(true) / 10) * 20;       //Hour tens
    for (int i = 0; i < 4; i++){
      if(curPosition[i] != NewPosition[i]){
        moveServo(i);
      }
    }
  }
  else if (ServoState == "Initialize"){ //set all servo's to state 0
    for (int i = 0; i < 4; i++){
      curPosition[i] = pwm.read(ServoPins[i]);
      NewPosition[i] = 0;
      if(curPosition[i] != NewPosition[i]){
        moveServo(i);
      }
    }
    ServoState = "Idle";  //reset back to Idle
  }
}

void moveServo(int i) {
  int increment = 1; 
  int delayTime = 10;

  if (curPosition[i] < NewPosition[i]) {
    for (int pos = curPosition[i]; pos < NewPosition[i]; pos += increment) {
      pwm.writeServo(ServoPins[i], pos);
      delay(delayTime); 
    }
  } else if (curPosition[i] > NewPosition[i]) {
    for (int pos = curPosition[i]; pos > NewPosition[i]; pos -= increment) {
      pwm.writeServo(ServoPins[i], pos);
      delay(delayTime); 
    }
  }
  curPosition[i] = NewPosition[i];
}