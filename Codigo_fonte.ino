// bibliotecas

#include <DHT.h>

#include <LiquidCrystal.h>


 
DHT dht(13, DHT22); // porta que está conectado o sensor de temperatura e umidade
 
// declarando as portas dos leds

#define ledverde  9

#define ledamarelo  8

#define ledvermelho  7
 
// definindo a porta do buzzer

#define buzzer 6
 
// definindo a porta do sensor de luz

#define sensorluz A5
 
// definindo as portas do display

LiquidCrystal lcd (12,11,10,5,4,3,2);
 
// contador de tempo

long tempo = 0;

// logotipo

byte name0x4[] = { B00000, B00000, B00001, B00010, B00010, B00010, B00001, B00000 };
byte name0x5[] = { B00111, B11000, B00000, B00000, B00011, B00100, B00100, B11100 };
byte name0x6[] = { B11111, B00000, B00000, B00000, B11000, B00000, B00011, B00100 };
byte name0x7[] = { B00000, B11000, B00100, B00010, B00010, B00010, B11100, B01000 };
byte name1x5[] = { B00011, B00000, B00000, B00000, B00000, B00000, B00000, B00000 };
byte name1x6[] = { B01000, B11101, B00011, B00000, B00000, B00000, B00000, B00000 };
byte name1x7[] = { B10000, B00000, B00000, B00000, B00000, B00000, B00000, B00000 };
 
void setup(){

  


  // configurando os objetos para OUTPUT(saida) ou INPUT(entrada)

  pinMode(ledverde,OUTPUT);

  pinMode(ledamarelo,OUTPUT);

  pinMode(ledvermelho,OUTPUT);

  pinMode(buzzer,OUTPUT);

  pinMode(sensorluz,INPUT);
 
  // aqui estamos inicializando o sensor de temperatura e umidade

  dht.begin();

  // aqui estamos inicializando o display e definindo sua largura e altura

  lcd.begin(16,2);

  logotipo();
  delay(5000);

  // aqui estamos inicializando o monitor serial

  Serial.begin(9600);

}
 
void loop(){


 
  // chamando a função ldr e definindo um delay de 1 segundo
  

  ldr();

  delay(5000);

  // chamando a função temp e definindo um delay de 1 segundo

  temp();

  delay(5000);

  // chamando a função umidade e defenindo um delay de 1 segundo

  umidade();

  delay(5000);

}
 
// criando funções para ligar e desligar os leds

void ligar_verde(){

    digitalWrite(ledverde,HIGH);

    digitalWrite(ledamarelo,LOW);

    digitalWrite(ledvermelho,LOW);

}

void ligar_amarelo(){

    digitalWrite(ledverde,LOW);

    digitalWrite(ledamarelo,HIGH);

    digitalWrite(ledvermelho,LOW);

}

void ligar_vermelho(){

    digitalWrite(ledverde,LOW);

    digitalWrite(ledamarelo,LOW);

    digitalWrite(ledvermelho,HIGH);

}

void ldr(){

  // estamos lendo a quantidade de luz e printando no monitor

  int qntd_luz0 = analogRead(sensorluz);

  int qntd_luz = map(qntd_luz0,0 ,1000, 0, 100);

  Serial.println("Quantidade de luz: ");

  Serial.println(qntd_luz);
 
  // criando uma condicional com a quantidade de luz
 
  // se o ambiente estiver escuro aparece uma mensagem de 'Luz ambiente boa!', acende o led verde e não toca o buzzer

  if (qntd_luz <=25){

    lcd.clear();

    lcd.setCursor(0,0);

    lcd.print("Luz ambiente boa!");

    ligar_verde();

    noTone(buzzer);

  }

  // se o ambiente estiver ficando claro o led amarelho acende o buzzer da um pequeno aviso e aparece a mensagem 'Quantidade de luz fora do ideal!'

  else if(qntd_luz > 25 && qntd_luz <=55 ){

    lcd.clear();

    lcd.setCursor(0,0);

    lcd.print("Ambiente a meia");

    lcd.setCursor(0,1);

    lcd.print("luz!");

    ligar_amarelo();

    tone(buzzer, 261);

    digitalWrite(buzzer,HIGH);

    delay(1000);

    noTone(buzzer);

    digitalWrite(buzzer,LOW);

  }

  // se estiver muito claro o led vermelho acende, o buzzer começa a tocar sem parar e aparece uma mensagem 'Quantidade de luz muito alta!'

  else if(qntd_luz > 55){

    lcd.clear();

    lcd.setCursor(0,0);

    lcd.print("Ambiente muito");

    lcd.setCursor(0,1);

    lcd.print("claro!");

    ligar_vermelho();

    tone(buzzer, 500);

    digitalWrite(buzzer,HIGH);

  }
}

void temp(){

  // criando variavel para ler a temperatura e printando no monitor
  float temp_soma = 0;
  float temperatura = dht.readTemperature(); // Lemos a temperatura

  if(millis() >= tempo + 1000){ // Esperamos um pouco
    for (int i = 0; i < 5; i++) { // Fazemos isso 5 vezes
      temp_soma += temperatura; // e somamos a temperatura
      delay(1000); // Esperamos mais um pouco
    }
  }
  float temp_media = temp_soma / 5; // Tiramos a média
  float tempe = dht.readTemperature(); // Lemos a temperatura de novo
  Serial.print("Temperatura = ");
  Serial.println(temp_media); // e printamos a temperatura média 

  // criando uma condicional com a temperatura

  // se a temperatura estiver entre 10 e 15 graus o led verde liga e aparece a mensagem 'temp OK!'

  if(temp_media >= 10 && temp_media <= 15){

    lcd.clear();

    lcd.setCursor(0,0);

    lcd.print("temp OK!");

    lcd.setCursor(0,1);

    lcd.print("temp : ");

    lcd.print(temp_media);

    lcd.print("°C");

    ligar_verde();

    noTone(buzzer);

  }

  // se a temperatura for maior que 15 o led vermelho liga, o buzzer toca sem parar e aparece a mensagem 'temp alta'

  else if(temp_media > 15){

    lcd.clear();

    lcd.setCursor(0,0);

    lcd.print("temp Alta!");

    lcd.setCursor(0,1);

    lcd.print("temp = ");

    lcd.print(temp_media);

    lcd.print("°C");

    ligar_amarelo();

    tone(buzzer, 500);

    digitalWrite(buzzer,HIGH);

  }

  // se a temperatura for menor que 10 o led vermelho liga, o buzzer toca sem parar e aparece a mensagem 'temp Baixa'

  else{

    lcd.clear();

    lcd.setCursor(0,0);

    lcd.print("temp Baixa!");

    lcd.setCursor(0,1);

    lcd.print("temp = ");

    lcd.print(temperatura);

    lcd.print("°C");

    ligar_amarelo();

    tone(buzzer, 500);

    digitalWrite(buzzer,HIGH);

  }

}

void umidade(){

  // criando a variavel para ler a umidade e printando no monitor

  float umidade_soma = 0;
  float umidade = dht.readHumidity(); // Lemos a umidade.

  if(millis() >= tempo + 1000){ // Esperamos um pouco.
    for (int i = 0; i < 5; i++) { // Fazemos isso 5 vezes...
      umidade_soma += umidade; // ...e somamos a umidade.
      delay(1000); // Esperamos mais um pouco.
    }
  }
  float umi_media = umidade_soma / 5; // Tiramos a média.
  float umid = dht.readHumidity(); // Lemos a umidade de novo.
  Serial.print("Umidade = ");
  Serial.println(umi_media); // Mais mensagens para o computador.

  // criando uma condicional com a umidade

  // se a umidade estiver entre 50% e 70% o led verde liga e aparece a mensagem 'umidade OK!'

  if(umi_media >= 50 && umi_media <= 70){

    lcd.clear();

    lcd.setCursor(0,0);

    lcd.print("Umidade OK!");

    lcd.setCursor(0,1);

    lcd.print("Umidade :");

    lcd.print(umi_media);

    ligar_verde();

    noTone(buzzer);

  }

  // se for maior que 70% o led vermelho liga, o buzzer não para de tocar e aparece a mensagem 'umidade alta'

  else if(umi_media > 70){

    lcd.clear();

    lcd.setCursor(0,0);

    lcd.print("Umidade Alta!");

    lcd.setCursor(0,1);

    lcd.print("Umidade :");

    lcd.print(umi_media);

    ligar_vermelho();

    tone(buzzer,500);

    digitalWrite(buzzer,HIGH);

  }

  // se for menor que 50% o led vermelho liga, o buzzer não para de tocar e aparece a mensagem 'umidade baixa'

  else{

    lcd.clear();

    lcd.setCursor(0,0);

    lcd.print("Umidade Baixa!");

    lcd.setCursor(0,1);

    lcd.print("Umidade :");

    lcd.print(umi_media);

    ligar_vermelho();

    tone(buzzer,500);

    digitalWrite(buzzer,HIGH);

  }

}

void logotipo(){
  // logotipo
  
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("BYTE    BRAINS!!");

  lcd.createChar(0, name0x4);
  lcd.setCursor(4, 0);
  lcd.write(byte(0));
  
  lcd.createChar(1, name0x5);
  lcd.setCursor(5, 0);
  lcd.write(byte(1));
  
  lcd.createChar(2, name0x6);
  lcd.setCursor(6, 0);
  lcd.write(byte(2));
  
  lcd.createChar(3, name0x7);
  lcd.setCursor(7, 0);
  lcd.write(byte(3));
  
  lcd.createChar(5, name1x5);
  lcd.setCursor(5, 1);
  lcd.write(byte(5));
  
  lcd.createChar(6, name1x6);
  lcd.setCursor(6, 1);
  lcd.write(byte(6));
  
  lcd.createChar(7, name1x7);
  lcd.setCursor(7, 1);
  lcd.write(byte(7));

}
 
 
 
