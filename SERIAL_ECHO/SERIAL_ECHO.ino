String content = "";
char character;
char endChar = ';'; //carattere di fine stringa

void setup() {
  Serial.begin(9600);
  Serial.println("Boot...");
}

void loop() {
  while(Serial.available()) {
      character = Serial.read();
      if (character == endChar) {
        Serial.println(content);
        content = "";
      }else{
        content.concat(character);
      }
  }
}
