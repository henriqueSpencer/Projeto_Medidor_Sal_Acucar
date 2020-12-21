float agua = A4;
float prova = A5;

float ag;
float pr;
  
void setup()
{
  Serial.begin(9600);
  pinMode(agua,INPUT);
  pinMode(prova,INPUT);
  
}

void loop()
{
  
  ag = analogRead(agua);
  pr = analogRead(prova);
  
  if(ag < pr){
  //sal
  Serial.println("Sal");
  }
  if(ag == pr){
  //agua
  Serial.println("Agua");
  }
  if(ag > pr){
  //acucar  
  Serial.println("Acucar"); 
  }  
}
