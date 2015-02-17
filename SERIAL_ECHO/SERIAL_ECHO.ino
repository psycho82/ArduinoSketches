String readData = ""; //string contenente i dati letti dalla seriale
char endChar = ';'; //carattere di fine stringa

void setup() {
  Serial.begin(9600);
  Serial.println("Booting...");
}

void loop() {
  readFromSerial(readData,endChar);
  writeToSerial(readData);
}

//resta in ascolto sulla seriale, legge dalla seriale e termina la lettura appena riceve il carattere di fine stringa (endChar). Svuota la stringa str passata per riferimento,
void readFromSerial(String &str, char &endC){
  char lastChar = '\0';
  str = "";
  while(lastChar!=endC) {
    if(Serial.available()){
      lastChar = Serial.read();//legge e svuota il buffer di lettura (1byte alla volta)
      if(lastChar != endC){
        str.concat(lastChar);
      }
    }
  }
}

//Scrive sulla seriale
void writeToSerial(String &str){
  Serial.println(str);
  Serial.flush();//Attende che dall'altra parte vengano letti tutti i dati presenti in uscita.
}
