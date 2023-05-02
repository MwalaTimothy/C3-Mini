bool isToneOn = false;
int frequency = 500;

void setup() {
  pinMode(7, INPUT);
  pinMode(2, OUTPUT);
}

void loop() {
  if(digitalRead(7) == HIGH){
    for(int a = 0; a < 30; a++){
      if(isToneOn){
        noTone(2);  
        isToneOn = false;  
      }else{
        tone(2, frequency);
        isToneOn = true;  
      }
      delay(500);
    }
    noTone(2); // Turn off the buzzer after the loop is finished
  }
}
