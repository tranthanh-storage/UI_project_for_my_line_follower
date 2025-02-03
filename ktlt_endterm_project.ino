#include <WiFi.h>
#include <WebServer.h>

#define left_ir 28
#define mid_ir 27
#define right_ir 32

const char* ssid = "Trang Thanh";
const char* password = "trangthanh9003";

WebServer server(80);

int inA1 = 21;
int inA2 = 22;
int inB1 = 18;
int inB2 = 17; 
int ena = 19;
int enb = 16;
int speed = 150;
// HC-SR04 Sensor Pins
const int trigPin = 25;
const int echoPin = 26;

long duration;
int distance;

void handleDistance() {
  // Send the distance as a response
  server.send(200, "text/plain", String(distance));
}


void handleRoot() {
  server.send(200, "text/plain", "Mannual control direction");
}
void event_goStraight () {
  goStraight ();
  Serial.println("di thang");
  server.send(200,"text/plain","go straight ... " + String(speed));
}
void event_turnLeft () {
  turnLeft ();
  Serial.println("re trai");
  server.send(200,"text/plain","turn left ... " + String(speed));
}
void event_turnRight () {
  turnRight ();
  Serial.println("re phai");
  server.send(200,"text/plain","turn right ... " + String (speed)); 
}
void event_goBack () {
  goBack ();
  Serial.println("lui");
  server.send(200,"text/plain","go back ... " + String(speed)); 
}
void event_stop () {
  stop ();
  Serial.println("dung lai");
  server.send(200,"text/plain","stop ... "); 
}
void lowSpeedHandle () {
  speed = 110;
  server.send(200,"text/plain","speed changed ... ");
}
void midSpeedHandle () {
  speed = 150;
  server.send(200,"text/plain","speed changed ... ");
}
void highSpeedHandle () {

  speed = 250;
  server.send(200,"text/plain","speed changed ... ");
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(left_ir, INPUT);
  pinMode(mid_ir, INPUT);
  pinMode(right_ir, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(inA1, OUTPUT);
  pinMode(inA2, OUTPUT);
  pinMode(inB1, OUTPUT);
  pinMode(inB2, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  // analogWrite(ena,speed);
  // analogWrite(enb,speed);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  server.on("/distance", handleDistance);
  server.on("/", handleRoot);
  server.on("/goStraight", goStraight);
  server.on("/turnLeft", turnLeft);
  server.on("/turnRight", turnRight);
  server.on("/goBack", goBack);
  server.on("/stop", stop);
  server.on("/lowSpeed",lowSpeedHandle);
  server.on("/midSpeed",midSpeedHandle);
  server.on("/highSpeed",highSpeedHandle);
  server.on("/automode",autoMode);

  server.begin();
  Serial.println("HTTP server started");

}

void loop() {
  analogWrite(ena,speed);
  analogWrite(enb,speed);
  // put your main code here, to run repeatedly:
  server.handleClient();
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  if (distance < 6) {
      stop();
  }
  delay(200);
}
void goStraight () {
  digitalWrite(inA1,LOW);
  digitalWrite(inA2,HIGH);
  digitalWrite(inB1,LOW);
  digitalWrite(inB2,HIGH);
}
void turnLeft () {
  digitalWrite(inA1,LOW);
  digitalWrite(inA2,HIGH);
  digitalWrite(inB1,LOW);
  digitalWrite(inB2,LOW);
}
void turnRight () {
    digitalWrite(inA1,LOW);
    digitalWrite(inA2,LOW);
    digitalWrite(inB1,LOW);
    digitalWrite(inB2,HIGH);
}
void goBack () {
  digitalWrite(inA1,HIGH);
    digitalWrite(inA2,LOW);
    digitalWrite(inB1,HIGH);
    digitalWrite(inB2,LOW);
}
void stop () {
  digitalWrite(inA1,LOW);
    digitalWrite(inA2,LOW);
    digitalWrite(inB1,LOW);
    digitalWrite(inB2,LOW);
}
void autoMode () {
  if (digitalRead(left_ir) > 0 && digitalRead(mid_ir)==0 && digitalRead(right_ir)==0  ) {
    turnLeft();
  } else if (digitalRead(right_ir) > 0 && digitalRead(left_ir)==0 && digitalRead(mid_ir)==0) {
    turnRight();
  } else if (digitalRead(mid_ir) > 0 && digitalRead(left_ir)==0 && digitalRead(right_ir)==0) {
    goStraight();
  } else {
    stop();
  }
  server.send(200,"text/plain","invalid line ... ");
}
