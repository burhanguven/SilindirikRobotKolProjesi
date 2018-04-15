int motor1 = 6;
int motor2 = 8;
int motor3 = 11; 

int motorDelay = 800;


/* gripper */
int inputPins[] = {2, 3, 4, 5};
int duration = 3;
bool sequence[][4] = {{LOW, LOW, LOW, HIGH },
                      {LOW, LOW, HIGH, HIGH},
                      {LOW, LOW, HIGH, LOW },
                      {LOW, HIGH, HIGH, LOW},
                      {LOW, HIGH, LOW, LOW },
                      {HIGH, HIGH, LOW, LOW},
                      {HIGH, LOW, LOW, LOW },
                      {HIGH, LOW, LOW, HIGH}};

/* gripper end */


void motorSola(int motor){
  digitalWrite(motor + 2, LOW);
  digitalWrite(motor, LOW);
  
  for (int index = 0; index < 200; index++) {
    digitalWrite(motor + 1, HIGH);
    delayMicroseconds(motorDelay);
    digitalWrite(motor + 1, LOW);
    delayMicroseconds(motorDelay);
  }
}

void motorSaga(int motor){
  digitalWrite(motor + 2, LOW);
  digitalWrite(motor, HIGH);
  
  for (int index = 0; index < 200; index++) {
    digitalWrite(motor + 1, HIGH);
    delayMicroseconds(motorDelay);
    digitalWrite(motor + 1, LOW);
    delayMicroseconds(motorDelay);
  }
}

void gripper(bool dir) {
  int tempSecuenceNum = 0;
  if (!dir)
    tempSecuenceNum = 7;
  
  for (int step = 0; step < 10; step++) {
    for(int sequenceNum = tempSecuenceNum;  (dir) ? (sequenceNum < 8) : (sequenceNum >= 0); (dir) ? sequenceNum++ : sequenceNum--){
      for(int inputCount = 0; inputCount < 4; inputCount++){
          digitalWrite(inputPins[inputCount], sequence[sequenceNum][inputCount]);
      } 
      delay(duration);
    }
  }
}

void setup()
{
  pinMode(motor1, OUTPUT);
  pinMode(motor1 + 1, OUTPUT);
  pinMode(motor1 + 2, OUTPUT);

  pinMode(motor2, OUTPUT);
  pinMode(motor2 + 1, OUTPUT);
  pinMode(motor2 + 2, OUTPUT);

  pinMode(motor3, OUTPUT);
  pinMode(motor3 + 1, OUTPUT);
  pinMode(motor3 + 2, OUTPUT);
  
  digitalWrite(motor1 + 2, HIGH);
  digitalWrite(motor2 + 2, HIGH);
  digitalWrite(motor3 + 2, HIGH);

  Serial.begin(9600);

  //gripper
  for(int inputCount = 0; inputCount < 4; inputCount++) {
      pinMode(inputPins[inputCount], OUTPUT);
  }
}

void loop()
{
  if(Serial.available() > 0) {
    char data = Serial.read();      
    Serial.print(data);        
    Serial.print("\n");  

    if(data == '1')
      motorSola(motor1);
    else if(data == '2')
      motorSaga(motor1);
    else if(data == '3')
      motorSola(motor2);
    else if(data == '4')
      motorSaga(motor2);
    else if(data == '5')
      motorSola(motor3);
    else if(data == '6')
      motorSaga(motor3);
    else if(data == '7')     // gripper turn on     
      gripper(true);
    else if(data == '8')     // gripper turn off
      gripper(false);

    digitalWrite(motor1 + 2, HIGH);
    digitalWrite(motor2 + 2, HIGH);
    digitalWrite(motor3 + 2, HIGH);

    
  }
  

}
