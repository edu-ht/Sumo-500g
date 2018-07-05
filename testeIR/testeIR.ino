//------------------------------------------------------------------------------
// YAPIRA - SUMO 500g
//------------------------------------------------------------------------------

#include <IRremote.h> // Biblioteca do IR

//------------------------------------------------------------------------------
// IR
//------------------------------------------------------------------------------
#define RECV_PIN 2
IRrecv irrecv(RECV_PIN);
decode_results results;

//------------------------------------------------------------------------------
void setup () {

  Serial.begin(9600);
  irrecv.enableIRIn();         // Inicia o receiver do IR
}

//------------------------------------------------------------------------------
// Recebe informação sobre a estratégia a utilizar e da partida
//------------------------------------------------------------------------------
int IR_read () {

  int leitura;
  if (irrecv.decode(&results)) {
    leitura = results.value, HEX;
    Serial.println(leitura,HEX);
    switch (leitura){
      case 0xFF629D: Serial.println("UP");    return 2;  break; //frente
      case 0xFF02FD: Serial.println("OK");    return 9;  break; //parar
      case 0xFFA857: Serial.println("DOWN");  return 6;  break; //ré
      case 0xFF22DD: Serial.println("LEFT");  return 8;  break; //girar esquerda
      case 0xFFC23D: Serial.println("RIGHT"); return 4;  break; //girar direita
      case 0xFF6897: Serial.println("ONE");   return 11; break;
      case 0xFF9867: Serial.println("TWO");   return 12; break;
      case 0xFFB04F: Serial.println("THREE"); return 13; break;
      case 0xFF30CF: Serial.println("FOUR");  return 14; break;
      case 0xFF18E7: Serial.println("FIVE");  return 15; break;
      case 0xFF7A85: Serial.println("SIX");   return 16; break;
      case 0xFF10EF: Serial.println("SEVEN"); return 17; break;
      case 0xFF38C7: Serial.println("EIGHT"); return 18; break;
      case 0xFF5AA5: Serial.println("NINE");  return 19; break;
    }
    delay(150);
    irrecv.resume();  // Recebe próximo valor
    delay(150);
  }
  return 0;
}

void loop () {

  IR_read();
}
