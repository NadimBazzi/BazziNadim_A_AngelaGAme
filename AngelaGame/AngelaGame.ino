#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);   //16 colonne, 2 righe

int meta = 30;
bool primavolta = true;
int mossagiocata = 0;
bool giocatore1 = false;//da sistemare sulle funzioni per capire che è stato l'ultimo a cliccare
int somma = 0;
String mosse = "123456";
void setup() {
  for (int i = 0; i < 7; i++) {
    mosse[i] = i + 1;
  }
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  lcd.init();
  lcd.backlight();
}



void loop() {
  if (primavolta) {
    contatore();
    lcd.clear();
  }
  else {
    Serial.println("Else");
    Serial.println("sM");
    
    RiempiStringa(mossagiocata);
    IniziaGiocatore1();
    
    somma = somma + mossagiocata;
    ScriviMeta();
    VediChiHaVinto();
    IniziaGiocatore2();
    somma = somma + mossagiocata;
    ScriviMeta();
    VediChiHaVinto();
  }
}

void ScriviMeta()
{
  if (meta == 100){
    lcd.setCursor(13, 0);
  lcd.print(/*somma + "/" + */meta);
  lcd.setCursor(10, 0);
lcd.print(somma);
  }
  else{
    lcd.setCursor(14, 0);
  lcd.print(/*somma + "/" + */meta);
  lcd.setCursor(11, 0);
  lcd.print(somma);
  }
}

void contatore() {
  primavolta = false;
  int flag = 0;


  while (flag == 0) {
    lcd.setCursor(0, 0);
    lcd.print("meta:");
    lcd.setCursor(6, 0);
    lcd.print(meta);
    if (digitalRead(A3) == LOW) {
      meta++;
      delay(250);
      lcd.setCursor(6, 0);
      lcd.print(meta);
      Serial.println("piu");
    }


    if (digitalRead(A1) == LOW) {
      meta--;
      delay(250);
      lcd.setCursor(6, 0);
      lcd.print(meta);
      Serial.println("meno");
    }

    if (meta == 101) {
      meta = 100;
      lcd.setCursor(6, 0);
      lcd.print(meta);
    }
    if (meta == 29) {
      meta = 30;
      lcd.setCursor(6, 0);
      lcd.print(meta);
    }

    if (digitalRead(A2) == LOW) {
      flag = 1;
      lcd.setCursor(6, 0);
      lcd.print("");
    }
  }
}

void IniziaGiocatore1() {
  lcd.setCursor(0, 0);
  lcd.print("G1:");
  giocatore1 = true;
  String mosseDaFare = RiempiStringa(mossagiocata);
  Serial.print("mosseDaFare:");
  Serial.println(mosseDaFare);
  Serial.println("sei entrato su CambiaNumero");
  delay(500);
  int ind = 0;
  int flag = 0;

  lcd.setCursor(5, 0);
      lcd.print(String(mosseDaFare[0]).toInt());

  while (flag == 0) {
    if (digitalRead(A3) == LOW) {
      while(digitalRead(A3) == LOW){}
      ind++;
      Serial.println("sei su mosse[ind] inizio = false");
      
      if (ind >= mosseDaFare.length()) {
        ind = 0;
      }
      Serial.println(String(mosseDaFare[ind]).toInt());
      lcd.setCursor(5, 0);
      lcd.print(String(mosseDaFare[ind]).toInt());
      
    }
    if (digitalRead(A1) == LOW) {
      while(digitalRead(A1) == LOW){}
      ind--;
      Serial.println("sei su mosse[ind] inizio = true");

      if (ind < 0) {
        ind = mosseDaFare.length()-1;
      }
      Serial.println(String(mosseDaFare[ind]).toInt());
      lcd.setCursor(5, 0);
      lcd.print(String(mosseDaFare[ind]).toInt());
      
    }
    if (digitalRead(A2) == LOW) {
      mossagiocata = String(mosseDaFare[ind]).toInt();
      Serial.println(mossagiocata);
      flag = 1;
      lcd.setCursor(6, 0);
      lcd.print("");
    }
  }

}




void IniziaGiocatore2() {
  lcd.setCursor(0, 0);
  lcd.print("G2:");
  giocatore1 = false;
  String mosseDaFare = RiempiStringa(mossagiocata);
  Serial.print("mosseDaFare:");
  Serial.println(mosseDaFare);
  delay(500);
  int ind = 0;
  int flag = 0;
  lcd.setCursor(5, 0);
      lcd.print(String(mosseDaFare[0]).toInt());
  while (flag == 0) {

    if (digitalRead(A3) == LOW) {
      while(digitalRead(A3) == LOW){}
      ind++;
      Serial.println("sei su mosse[ind] inizio = true");

      if (ind >= mosseDaFare.length()) {
        ind = 0;
      }
      Serial.println(String(mosseDaFare[ind]).toInt());
      lcd.setCursor(5, 0);
      lcd.print(String(mosseDaFare[ind]).toInt());
      
    }

    if (digitalRead(A1) == LOW) {
      while(digitalRead(A1) == LOW){}
      ind--;
      Serial.println("sei su mosse[ind] inizio = true");

      if (ind < 0) {
        ind = mosseDaFare.length()-1;
      }
      Serial.println(String(mosseDaFare[ind]).toInt());
      lcd.setCursor(5, 0);
      lcd.print(String(mosseDaFare[ind]).toInt());
      
    }
    if (digitalRead(A2) == LOW) {
      mossagiocata = String(mosseDaFare[ind]).toInt();
      Serial.println(mossagiocata);
      lcd.clear();
      return;
    }
  }
}

String RiempiStringa(int n){
  Serial.println("sei su RiempiStringa");
  String mossetolte = "    ";
  String mossetot = "      ";
  if (n == 1 || n == 6){
    mossetolte[0] = '2';
    mossetolte[1] = '3';
    mossetolte[2] = '4';
    mossetolte[3] = '5';
    return mossetolte;
    }
  if (n == 2 || n == 5){
    mossetolte[0] = '1';
    mossetolte[1] = '3';
    mossetolte[2] = '4';
    mossetolte[3] = '6';
    return mossetolte;
    }
  if (n == 3 || n == 4){
    mossetolte[0] = '1';
    mossetolte[1] = '2';
    mossetolte[2] = '5';
    mossetolte[3] = '6';
    return mossetolte;
    }
    if(n == 0){
    mossetot[0] = '1';
    mossetot[1] = '2';
    mossetot[2] = '3';
    mossetot[3] = '4';
    mossetot[4] = '5';
    mossetot[5] = '6';
    Serial.println("n == 0");
    Serial.println(String(mossetot.length()));
    return mossetot;
    }
}


void VediChiHaVinto()
{
  if (somma == meta){
    if(giocatore1){
      //Serial.print("somma=meta");
      lcd.setCursor(0, 0);
      lcd.print("G1 vince");
      primavolta = true;
    }
    else{
      //Serial.print("somma=meta");
      lcd.setCursor(0, 0);
      lcd.print(" G2 vince");
      primavolta = true;
    }
  }
  if (somma > meta){
     if(giocatore1){
      //Serial.print("somma>meta");
      lcd.setCursor(0, 0);
      lcd.print("G2 vince");
      primavolta = true;
    }
    else{
      //Serial.print("somma>meta");
      lcd.setCursor(0, 0);
      lcd.print("G1 vince");
      primavolta = true;
    }
  }
}
