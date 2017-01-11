int anl = 5;
int dig = 13;
int dig_read;
int anl_read;
int start_time = -1;
int end_time;
int error;
int background = 22;
int code[100];


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
