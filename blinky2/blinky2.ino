void setup(){
	pinMode(13, OUTPUT);
	Serial.begin(9600);
}

void loop(){
	digitalWrite(13,HIGH);
	delay(1000);
	digitalWrite(13,LOW);
	delay(1000);
	Serial.println("Hello World");
	digitalWrite(13,HIGH);
	delay(200);
	digitalWrite(13,LOW);
	delay(200);
	digitalWrite(13,HIGH);
	delay(200);
	digitalWrite(13,LOW);
	delay(1000);
        Serial.println("sftp test mother fucker!");
}
