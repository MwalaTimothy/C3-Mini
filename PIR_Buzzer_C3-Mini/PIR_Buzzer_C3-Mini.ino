bool isToneOn = false;
int frequency = 500;

void setup() {
  //here is our PIR sensor
  pinMode(7, INPUT);
  //here is our buzzer
  pinMode(2, OUTPUT);

}

void loop() {
  //when PIR sensor gives us HIGH it means that it detects movement
  if(digitalRead(2) == HIGH){
    //we will turn on alarm for 15 seconds
    //we are using tone() so we can control frequency of our beep sound
    //to turn tone off we have to use noTone()
    //if you want to change frequency of tone you can do it in the variable
    //on the top of the code
    for(int a = 0; a < 30; a++){
      if(isToneOn){
        noTone(3);  
        isToneOn = false;  
      }else{
        //3 means our pin where buzzer is connected
      tone(3, frequency);
      //we have to change this variable to true, we have to know
      //when to turn buzzer on and when to turn it on
      isToneOn = true;  
      }
      //delay 0.5 second, you can change this value so it will 
      //beep slower or faster
      delay(500);
    }
  }
}