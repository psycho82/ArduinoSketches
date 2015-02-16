#include <SPI.h>
//opcodes 2
#define DATAOUT 11//MOSI
#define DATAIN  12//MISO 
#define SPICLOCK  13//sck
#define SLAVESELECT 10//ss


#define WREN  6
#define WRDI  4
#define RDSR  5
#define WRSR  1
#define READ  3
#define WRITE 2

byte eeprom_output_data;
byte eeprom_input_data=0;
byte clr;
int address=0;
char buffer [128]; //buffer dei dati
// SPCR = 01010000
//interrupt disabled,spi enabled,msb 1st,master,clk low when idle,
//sample on leading edge of clk,system clock/4 rate (fastest)
SPCR = (1<<SPE)|(1<<MSTR);



String content = "";
char character;
char endChar = ';'; //carattere di fine stringa

void setup() {
  Serial.begin(9600);
  Serial.println("Boot...");
  pinMode(DATAOUT, OUTPUT);
  pinMode(DATAIN, INPUT);
  pinMode(SPICLOCK,OUTPUT);
  pinMode(SLAVESELECT,OUTPUT);
  digitalWrite(SLAVESELECT,HIGH); //disable device 
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
