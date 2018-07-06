//------------------------------------------------------------------------------
// YAPIRA - SUMO 500g
//------------------------------------------------------------------------------

#include <IRremote.h> // Biblioteca do IR

#define DIR 0
#define ESQ 1

//------------------------------------------------------------------------------
// Configuracoes
//------------------------------------------------------------------------------
#define curvaFora   192
#define curvaDentro 128
#define RAPIDO   192
#define LENTO    128
#define MINPROX  200  // valor minimo pra que algo seja detectado
#define MINLINHA 400  // valor minimo pra que linha seja detectada
#define ESPERA   5000 // tempo de espera antes do comeco
#define delayFreioLinha 300
#define delayFreioGiro  200
#define delayFrente     1000

//------------------------------------------------------------------------------
// Direcoes de movimento
//------------------------------------------------------------------------------
#define andaD 0 // direita
#define andaE 1 // esquerda
#define andaF 2 // frente
#define andaT 3 // tras
#define giraD 4
#define giraE 5
#define freio 6

//------------------------------------------------------------------------------
// Pinos dos motores
//------------------------------------------------------------------------------
#define pwmEsq    3   // valor 'analogico' da velocidade dos motores
#define pwmDir    12  // valor 'analogico' da velocidade dos motores
#define motorDirF 7   // quando HIGH faz motor direito ir para frente
#define motorDirT 8   // quando HIGH faz motor direito ir para tras
#define motorEsqF 5
#define motorEsqT 6

//------------------------------------------------------------------------------
// Pinos dos sensores
//------------------------------------------------------------------------------
#define pinoProxDir   0
#define pinoProxEsq   3
#define pinoLinhaDir  2
#define pinoLinhaEsq  1

//------------------------------------------------------------------------------
// IR
//------------------------------------------------------------------------------
#define RECV_PIN 2
IRrecv irrecv(RECV_PIN);
decode_results results;

//------------------------------------------------------------------------------
// Variaveis de estado
//------------------------------------------------------------------------------
int proxDir, proxEsq;     // valores dos sensores de proximidade
int linhaDir, linhaEsq;   // valores dos sensores de linha

//------------------------------------------------------------------------------
void setup () {

  Serial.begin(9600);
  irrecv.enableIRIn();         // Inicia o receiver do IR
  pinMode (motorDirF, OUTPUT);
  pinMode (motorDirT, OUTPUT);
  pinMode (motorEsqF, OUTPUT);
  pinMode (motorEsqT, OUTPUT);
  pinMode (2, INPUT);
  analogWrite (pwmEsq, RAPIDO);
  analogWrite (pwmDir, RAPIDO);
}

//------------------------------------------------------------------------------
// Controla direcao dos motores e velocidade
//------------------------------------------------------------------------------
void motor (int mov, int velEsq, int velDir) {

  uint8_t df,dt,ef,et; // valores dos pinos dos motores

  switch (mov) {
    case andaD: df = LOW;   dt = LOW;   ef = HIGH;  et = LOW;
      break;
    case andaE: df = HIGH;  dt = LOW;   ef = LOW;   et = LOW;
      break;
    case andaF: df = HIGH;  dt = LOW;   ef = HIGH;  et = LOW;
      break;
    case andaT: df = LOW;   dt = HIGH;  ef = LOW;   et = HIGH;
      break;
    case giraD: df = LOW;   dt = HIGH;  ef = HIGH;  et = LOW;
      break;
    case giraE: df = HIGH;  dt = LOW;   ef = LOW;   et = HIGH;
      break;
    case freio: df = HIGH;  dt = HIGH;  ef = HIGH;  et = HIGH;
      break;
  }
  digitalWrite (motorDirF, df);
  digitalWrite (motorDirT, dt);
  digitalWrite (motorEsqF, ef);
  digitalWrite (motorEsqT, et);
  analogWrite (pwmEsq, velEsq);
  analogWrite (pwmDir, velDir);
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

//------------------------------------------------------------------------------
// Le valores de todos os sensores e guarda em variaveis globais
//------------------------------------------------------------------------------
void lerSensores () {
  proxDir  = analogRead (pinoProxDir);
  proxEsq  = analogRead (pinoProxEsq);
  linhaDir = analogRead (pinoLinhaDir);
  linhaEsq = analogRead (pinoLinhaEsq);
}

void loop () {

  switch (IR_read()) {

    // movimentacao teste
    case  2: motor (andaF, LENTO, LENTO);       break;
    case  4: motor (andaD, LENTO, LENTO);       break;
    case  8: motor (andaE, LENTO, LENTO);       break;
    case  9: motor (andaF, 0, 0);               break;
    case  6: motor (andaT, LENTO, LENTO);       break;

    // estrategias
    case 11: delay (ESPERA); segue (ESQ, delayFrente); break;
    case 13: delay (ESPERA); segue (DIR, delayFrente); break;
    case 14: delay (ESPERA); segue (ESQ, 0); break;
    case 16: delay (ESPERA); segue (DIR, 0); break;
  }
}
