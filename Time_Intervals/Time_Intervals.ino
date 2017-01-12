int anl = 5;
int dig = 13;
int dig_read;
int anl_read;
int start_time = -1;
int end_time;
int error;
int background = 22;
int code[100];
int new_code[100];
int t = 1;
int mult[3] = {1, 1, 2};
int divi[3] = {1, 2, 4};
int delta;
int i;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(anl, INPUT);
  pinMode(dig, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  anl_read = analogRead(anl);
  end_time = millis();
  if(anl_read > background && start_time == -1){
    Serial.println("Started");
    start_time = end_time;
  }
  else if(anl_read > background && end_time - start_time > 50){
    Serial.println(end_time - start_time);
    start_time = end_time;
  }
}

void write_new(){
  //defines a new array
  //copys knocking pattern to array three times
  //if copying is successful overwrites old password
  
  //clear new_code
  i = 0;
  while(i < 100){
    new_code[i] = 0;
  }

  //play start noise
  start_beep();
  
  //run through each recording cycle
  i = 0;
  while(i < 3){
    int knock = 0;

    //run through the entire 
    while(true){

      //gather data
      anl_read = analogRead(anl);
      end_time = millis();

      //check for sound
      
      //first sound detected
      if(anl_read > background && start_time == -1){
        start_time = end_time;
      }//end of first sound
      
      //subsequent sounds detected
      else if(anl_read > background && end_time - start_time > 50){
        delta = end_time - start_time;

        //check if similar enough to accept
        if(abs(delta - new_code[knock]) < 50 || new_code[knock] == 0){
          new_code[knock] = (delta*mult[i] + new_code[knock])/divi[i];
          knock ++;
          start_time = end_time;
        }
        //if not similar enough, break
        else{
          error_beep();
          return;
        }
      }//end of subsequent sounds

      //if there's a long delay
      else if(end_time - start_time > 2000){
        if(new_code[knock] == 0){
          new_code[knock] = -1;
          break;
        }
        if(new_code[knock] == -1){
          break;
        }
        else{
          error_beep();
          return;
        }
      }//end of delay loop
    }//end of data gathering
    i++;
  }//end of 3 cycle while loop

  //if the code gets here, all data has successfully been collected
  memcpy(code, new_code, 100);
  end_beep;
}//end of write_new()

void start_beep(){
  //play starting beep
}

void end_beep(){
  //play end beep
}

void error_beep(){
  //play error noise
}

