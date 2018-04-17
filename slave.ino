// Define used pins
const byte buttonPin = 2;
const byte micPin = 0;

// Variables for the button handling
volatile int buttonState = LOW;
unsigned long debounceLimit = 1000;

// Variables for the mic handling
boolean audio;
boolean lastAudio = false;
unsigned int audioVolumeLimit = 450;
unsigned long audioTimeLimit = 1000;

// Common variables 
unsigned long lastAction = 0;
unsigned long tmpTime = 0; 

void setup() {
  Serial.begin(9600); 
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), pushed, RISING);
}

void loop() {
  tmpTime = millis();
  
  if (analogRead(micPin) > audioVolumeLimit) {
    audio = true;    
  } else {
    audio = false;
  }  
  
  if (audio && !lastAudio && tmpTime - lastAction > audioTimeLimit) {
    Serial.print("Sound \n");
    lastAction = tmpTime;  
  }

  lastAudio = audio;
}


// Interrupt routine
void pushed() {
  buttonState = digitalRead(buttonPin);  
  tmpTime = millis();
  
  if(tmpTime - lastAction > debounceLimit && buttonState == HIGH) {
    Serial.print("Pushed \n");
    lastAction = tmpTime;
  }
  
}



