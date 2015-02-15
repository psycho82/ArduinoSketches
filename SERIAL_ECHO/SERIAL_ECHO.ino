String content = "";
char character;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Boot...");
}

void loop() {
  while(Serial.available()) {
      character = Serial.read();
      if (character == ';') {
        Serial.println(content);
        content = "";
      }else{
        content.concat(character);
      }
  }
}
