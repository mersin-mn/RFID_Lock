/* 
 * Created by: Emerson Medeiros Noberto
 * 22/07/2023
 * 
 * PINAGEM RFID
 * SDA - 10
 * SCK - 13
 * MOSI - 11
 * MISO - 12
 * RST - 9
 * 
 * PINAGEM(OUTROS)
 * Servo - 5
 * Led vermelho - 7
 * Led verde - 6
 * Botão - 3
 */

#include <SPI.h>
#include <MFRC522.h>
#include <VarSpeedServo.h>
#define SS_PIN 10
#define RST_PIN 9
VarSpeedServo Servolock;
MFRC522 mfrc522(SS_PIN, RST_PIN);
char st[20];
int ledvm = 7;
int ledvd = 6;
int desblo = LOW;
int Servodesblo = LOW;
 
void setup() 
{
  Serial.begin(9600);
  SPI.begin();
  Servolock.attach(5);
  mfrc522.PCD_Init();
  Serial.println("Start...");
  Serial.println();
  pinMode(ledvm, OUTPUT);
  pinMode(ledvd, OUTPUT);
  Servolock.slowmove(180, 50); 
}
/*
void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("usuário tag:");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  conteudo.toUpperCase();
//-----------------------------------------------------------------------
//------------------------------Cadastros--------------------------------
  if (conteudo.substring(1) == "60 57 FF A7") //tag 1 usuario:Emerson #1
  {
    Serial.println("Acesso OK");
    if (desblo == LOW){
      desblo = HIGH;
    } else {
      desblo = LOW;
    }
  }
  
//-----------------------------------------------------------------------
  else {
    Serial.println("Acesso Negado");
    digitalWrite (ledvm, HIGH);
    delay(100);
    digitalWrite (ledvm, LOW);
    delay(100);
    digitalWrite (ledvm, HIGH);
    delay(100);
    digitalWrite (ledvm, LOW);
    delay(100);
    digitalWrite (ledvm, HIGH);
    delay(100);
    digitalWrite (ledvm, LOW);
    delay(100);
  }
  if (desblo == HIGH)
    {
      digitalWrite (ledvm, LOW);
      digitalWrite (ledvd, HIGH);
    }
    else if (desblo == LOW)
    {
      digitalWrite (ledvm, HIGH);
      digitalWrite (ledvd, LOW);
    }
    if(digitalRead(3) == HIGH)
      {
        Serial.println("Servo");
        myservo.write(180);
    delay(2000);
    myservo.write(0);
      }
   delay(1000);
} 
*/
void loop() 
{
  // Verifica se há uma nova tag RFID presente no leitor
  if (mfrc522.PICC_IsNewCardPresent()) 
  {
    // Realiza a leitura do UID da tag
    if (mfrc522.PICC_ReadCardSerial()) 
    {
      Serial.print("usuário tag:");
      String conteudo = "";
      for (byte i = 0; i < mfrc522.uid.size; i++) 
      {
        conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      conteudo.toUpperCase();

      // Verifica o UID da tag para realizar ações específicas
      if (conteudo.substring(1) == "60 57 FF A7") //tag 1 usuario:Mersin #1
      {
        Serial.println("Acesso OK");
        if (desblo == LOW)
        {
          desblo = HIGH;
        }
        else
        {
          desblo = LOW;
        }
      }
      if (conteudo.substring(1) == "E0 50 54 A8") //tag 2 usuario:Mylli #2
      {
        Serial.println("Acesso OK");
        if (desblo == LOW)
        {
          desblo = HIGH;
        }
        else
        {
          desblo = LOW;
        }
      }
      if (conteudo.substring(1) == "F0 5E 85 89") //tag 3 usuario:Mylli #3
      {
        Serial.println("Acesso OK");
        if (desblo == LOW)
        {
          desblo = HIGH;
        }
        else
        {
          desblo = LOW;
        }
      }
      // Mais condições de cadastros podem ser adicionadas aqui

      // Fim das verificações de cartão RFID, finaliza a leitura
      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();
    }
  }

  // Verifica o valor de "desblo" e realiza ações de acordo com o estado
  if (desblo == HIGH)
  {
    digitalWrite(ledvm, LOW);
    digitalWrite(ledvd, HIGH);
//---------------------------------
    if (digitalRead(3) == HIGH)
{
  if (Servodesblo == LOW)
  {
    Servodesblo = HIGH;
  }
  else
  {
    Servodesblo = LOW;
  }

  if (Servodesblo == HIGH)
  {
    Servolock.slowmove(100, 50);
  }
  else // Usamos "else" aqui, já que apenas duas opções possíveis: HIGH ou LOW
  {
    Servolock.slowmove(180, 50);
  }
}

//---------------------------------
  }
  else if (desblo == LOW)
  {
    digitalWrite(ledvm, HIGH);
    digitalWrite(ledvd, LOW);
    Servolock.slowmove(180, 50);
  }




  
  if (digitalRead(4) == HIGH)
{
  if (Servodesblo == LOW)
  {
    Servodesblo = HIGH;
  }
  else
  {
    Servodesblo = LOW;
  }

  if (Servodesblo == HIGH)
  {
    Servolock.slowmove(100, 50);
    delay(500);
  }
  else // Usamos "else" aqui, já que apenas duas opções possíveis: HIGH ou LOW
  {
    Servolock.slowmove(180, 50);
  }
}

  // Resto do código do loop e outras tarefas podem ser adicionadas aqui
Serial.println(Servodesblo);
  delay(300); // Pequena pausa para evitar loop muito rápido
}
