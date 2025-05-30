#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

const int analogInPin = A0;
int sensorValue = 0;

boolean isPlaying = false;

void setup() {
  // declare pin 9 to be an output:
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  Serial.begin(9600);

  mySoftwareSerial.begin(9600);
  Serial.begin(9600);

  delay(1000);
  
   if (!myDFPlayer.begin(mySoftwareSerial)) {
        Serial.println("Unable to begin:");
        Serial.println("1.Please recheck the connection!");
        Serial.println("2.Please insert the SD card!");
        while (true);
    }
    Serial.println(F("DFPlayer Mini online."));

     myDFPlayer.setTimeOut(500);

    //----Set volume----
    myDFPlayer.volume(10); //Set volume value (0~30).
    //myDFPlayer.volumeUp(); //Volume Up
    //myDFPlayer.volumeDown(); //Volume Down

    //----Set different EQ----
    myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
    //  myDFPlayer.EQ(DFPLAYER_EQ_POP);
    //  myDFPlayer.EQ(DFPLAYER_EQ_ROCK);
    //  myDFPlayer.EQ(DFPLAYER_EQ_JAZZ);
    //  myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);
    //  myDFPlayer.EQ(DFPLAYER_EQ_BASS);

    myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
}

// the loop routine runs over and over again forever:
void loop() {
  sensorValue = analogRead(analogInPin);
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\n");
  delay(2);
  if((sensorValue>=100)&&(sensorValue<=600)){
    digitalWrite(2,HIGH);
    delay(100);
    }
  else if((sensorValue>=601)&&(sensorValue<=625)){
   digitalWrite(3,HIGH);
   delay(100);
    }  
  else if((sensorValue>=626)&&(sensorValue<=700)){
    digitalWrite(4,HIGH);
    myDFPlayer.play(1); //Play the first song
    isPlaying = true;
    Serial.println("Playing..");
    }
  else{
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    delay(100);
    }
}
