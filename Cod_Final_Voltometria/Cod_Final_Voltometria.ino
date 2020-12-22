
// Code para o modulo de Cartao SD
#include <SD.h>
#include <SPI.h>
File myFile;
int pinCS = 10; // Pin 10  Arduino Uno = para o cartao sd
////////////////////----------////////




int a = 6; //a = porta onde vai variar a Tensao
int val = 0;  //val vai ser o valor de tensao q vai sair na porta a
float ct = A0; //ADC  ct = onde recebe a corrente
float c = 0; //vai ser a leitura de recebida na porta ct
int n = 0;
float Potstep = 0.0078; // fixed due to the DAC resolution
int vevals[] = {10,20,50,100,200,250,300}; //multiple scan rates values (mV/s)
int const count = 6;
long intervalos[count];


int a2 = 5; //a = porta onde vai variar a Tensao
int val2 = 0;  //val vai ser o valor de tensao q vai sair na porta a
float ct2 = A1; //ADC  ct = onde recebe a corrente
float c2 = 0; //vai ser a leitura de recebida na porta ct

void setup() {
  TCCR1B = TCCR1B & B11111000 | B00000001; //Set dividers to change PWM frequency
  Serial.begin(9600);
  pinMode(a,OUTPUT);
  pinMode(ct,INPUT);
////////////////////////////////Cartao SD//////////////////////
  pinMode(pinCS, OUTPUT);
  
  // inicializacao do cartao SD
  if (SD.begin())
  {
    Serial.println("SD esta pronto");
  } else
  {
    Serial.println("SD nao esta abrindo");
    return;
  }
  
}
void loop() {

  //Teste se um é maior q o outro:
  analogWrite(a,240);
  c = ((0.00195*(analogRead(ct))-1)*1000);
  analogWrite(a2,240);
  c2 = ((0.00195*(analogRead(ct2))-1)*1000);

  if(c > c2){
  //sal
  Serial.println("Sal");
  }
  if(c == c2){
  //agua
  Serial.println("Agua");
  }
  if(c < c2){
  //acucar  
  Serial.println("Acucar"); 
  } 
 ////////////////////////////////////////////////////////// 
  

  // Criando/ abrindo o arquivo 
  myFile = SD.open("Resultados.CSV", FILE_WRITE);

  
  /////////// Voltometria Ciclica   ///////////////
  for(int pos = 0; pos < count; pos++){
    intervalos[pos]=(1000000L/((vevals[pos])*128L));
  }
  for(int pos = 0; pos <= count; pos++){
    n = 0;
    while(n <= 1){
      //Scanner aumentando a tensao
      for(val = 0; val <= 255; val++){
        analogWrite(a,val);  //val vai ser o valor de tensao q vai sair na porta a
        Serial.print(val*Potstep);
        delay(intervalos[pos]);
        c = ((0.00195*(analogRead(ct))-1)*1000); // Leitura de corrente em uA!!!
        Serial.print(c);
        
        // se o arquivo abrir, escreva:
        if (myFile) {
          Serial.println("Writing to file...");
          // Escrevendo:
          myFile.println(val*Potstep +";");
          myFile.print(c +";");
        }
        // Se o arquivo n abrir, imprimir mensagem de erro:
        else {
          Serial.println("error ao abrir Resultados.CSV");
        }
      }
      //Scanner diminuindo a tensao
      for(val = 255; val >= 0; val--){
        analogWrite(a,val);
        Serial.print(val*Potstep);
        delay(intervalos[pos]);
        c = ((0.00195*(analogRead(ct))-1)*1000); // Leitura de corrente em uA!!!
        Serial.print(c);
        
        // se o arquivo abrir, escreva:
        if (myFile) {
          Serial.println("Writing to file...");
          // Escrevendo:
          myFile.println(val*Potstep +";");
          myFile.print(c +";");
        }
        // Se o arquivo n abrir, imprimir mensagem de erro:
        else {
          Serial.println("error ao abrir Resultados.CSV");
        }
      }
      n=n+1;
    }
  }
  myFile.close(); // fechando
          
} 
