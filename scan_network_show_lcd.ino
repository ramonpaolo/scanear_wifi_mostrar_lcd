
/*
*** Utilizado ESP32 ***
  Pinos LCD BackLight Green:
  - VCC - VIN
  - GND - GND
  - SCL - D22
  - SDA - D21
*/


#include <WiFi.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
//lcd(0x27, 16, 2);

const char* ssid = "dlink-D520";
const char* pass = "rvhvc24446";

int intensidadeSinal = -40;

void setup() {

  Serial.begin(9600);

  // Inicia o Wifi no modo Estação WiFi
  WiFi.mode();

  //Desconecta de algum WiFi conectado
  WiFi.disconnect();

  //Inicia o LCD
  lcd.init();
  lcd.backlight();
  lcd.print("Desejamos uma");
  lcd.setCursor(0, 1);
  lcd.print("rede com: -40");

  conectionWiFi();

}

void conectionWiFi() {

  //Devolve uma lista(array) com todos os WiFis
  int networks = WiFi.scanNetworks();

  if (networks == 0) {
    Serial.println("Nenhuma rede a vista");
  } else {
    for (int i = 0; i < networks; i++) {
      Serial.println(WiFi.SSID(i) + " : " + WiFi.RSSI(i));

      //Vê o sinal com a melhor intensidade
      if (abs(WiFi.RSSI(i)) < abs(intensidadeSinal)) {

        //Mostra no Monitor Serial
        Serial.println("Achamos o melhor WIFI");
        Serial.println(WiFi.SSID(i) + " com: " + WiFi.RSSI(i));

        //Limpa o LCD
        lcd.clear();

        //Posiciona o curso no 3 espaço
        lcd.setCursor(3, 0);
        //Escreve na primeira linha o nome do WiFi
        lcd.print(WiFi.SSID(i));

        //Posiciona o cursor na segunda linha no 5 espaço
        lcd.setCursor(5, 1);
        //Escreve na segunda linha a intensidade do sinal
        lcd.print(WiFi.RSSI(i));
      }
    }

    //Se conecta no WiFi(SSID, PASSWORD)
    WiFi.begin(ssid, pass);

    //Enquanto o WiFi não se conectar
    //Detalhe: Código 3 = Conectado
    while (WiFi.status() != 3) {
      Serial.println("...");
      delay(100);
    }

    //Mostra o endereço IP local
    Serial.println(WiFi.localIP());

  }
  Serial.println("");
}

void loop() {
  // put your main code here, to run repeatedly:
}
