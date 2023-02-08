#include <ESP8266WiFi.h>

#define SSID "AloiTech"
#define PASSWD "papajoao23"
#define SOCK_PORT 124

WiFiServer sockServer(SOCK_PORT);

void setup(){
    Serial.begin(115200);
    delay(1000);
    WiFi.begin(SSID,PASSWD);
    while (WiFi.status() != WL_CONNECTED){delay(100);}

    Serial.println("");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    sockServer.begin(); //abre a porta 123
}

void loop(){
    WiFiClient client = sockServer.available();
    if (client){
        //Serial.println("Iniciou uma conexao!");
        unsigned int vezes = 1000;
        unsigned int vezesDeBaixo = 100000;
        while (client.connected() && --vezes > 0){
            delay(200);
            String treeWayBuffer = String();
            bool hasData = false;
            while (client.available() > 0 && --vezesDeBaixo > 0){
              //if (treeWayBuffer.length() < 255) {
                treeWayBuffer.concat((char)client.read());
              //}
              hasData = true;
            }
            if (hasData) {
              Serial.println(treeWayBuffer);
              if (treeWayBuffer.equals("SYN")) {
                client.print("SYN-ACK");
              }
            }
        }
        //client.flush();
        client.stop(); //acabou a leitura dos dados. Finaliza o client.
        //Serial.println("Terminou uma conexao!");
        delay(10);
    }
}
