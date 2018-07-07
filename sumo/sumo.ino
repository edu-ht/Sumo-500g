//------------------------------------------------------------------------------
// YAPIRA - SUMO 500g
//------------------------------------------------------------------------------

#include <IRremote.h> // Biblioteca do IR

#define DIR 0
#define ESQ 1

//------------------------------------------------------------------------------
// Configuracoes
//------------------------------------------------------------------------------
#define curvaFora   128
#define curvaDentro 70
#define RAPIDO   192
#define LENTO    128
#define MINPROX  200  // valor minimo pra que algo seja detectado
#define MINLINHA 400  // valor minimo pra que linha seja detectada
#define ESPERA   3350 // tempo de espera antes do comeco
#define delayFreioLinha 300
#define delayFreioGiro  200
#define delayFrente     50

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
#define pwmEsq    9   // valor 'analogico' da velocidade dos motores
#define pwmDir    3   // valor 'analogico' da velocidade dos motores
#define motorDirF 8   // quando HIGH faz motor direito ir para frente
#define motorDirT 7   // quando HIGH faz motor direito ir para tras
#define motorEsqF 6
#define motorEsqT 5

//------------------------------------------------------------------------------
// Pinos dos sensores
//------------------------------------------------------------------------------
#define pinoProxDir   A0
#define pinoProxEsq   A3
#define pinoLinhaDir  A2
#define pinoLinhaEsq  A1

//------------------------------------------------------------------------------
// Variaveis de estado
//------------------------------------------------------------------------------
int proxDir, proxEsq;     // valores dos sensores de proximidade
int linhaDir, linhaEsq;   // valores dos sensores de linha

const unsigned int NUM_MODOS = 3;
__attribute__((section(".noinit"))) unsigned int modo; // guarda modo apos reset

//------------------------------------------------------------------------------
void setup () {

  if (++modo > NUM_MODOS) modo = 0; // troca de modo ao inicializar
  Serial.begin(9600);
  pinMode (motorDirF, OUTPUT);
  pinMode (motorDirT, OUTPUT);
  pinMode (motorEsqF, OUTPUT);
  pinMode (motorEsqT, OUTPUT);
  pinMode (pwmDir, OUTPUT);
  pinMode (pwmEsq, OUTPUT);
  analogWrite (9, 128);
  analogWrite (3, 128);
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
// Le valores de todos os sensores e guarda em variaveis globais
//------------------------------------------------------------------------------
void lerSensores () {
  proxDir  = analogRead (pinoProxDir);
  proxEsq  = analogRead (pinoProxEsq);
  linhaDir = analogRead (pinoLinhaDir);
  linhaEsq = analogRead (pinoLinhaEsq);
}

void loop () {

  switch (modo) {

    case 0: digitalWrite (13, HIGH); delay(500); break;
    case 1: digitalWrite (13, LOW); delay (ESPERA); segue (ESQ, delayFrente); break;
    case 2: digitalWrite (13, HIGH); delay (500); digitalWrite (13, LOW); delay (500); break;
    case 3: digitalWrite (13, LOW); delay (ESPERA); segue (DIR, delayFrente); break;
  }

//  switch (IR_read()) {
//
//    // movimentacao teste
//    case  2: motor (andaF, LENTO, LENTO);       break;
//    case  4: motor (andaD, LENTO, LENTO);       break;
//    case  8: motor (andaE, LENTO, LENTO);       break;
//    case  9: motor (andaF, 0, 0);               break;
//    case  6: motor (andaT, LENTO, LENTO);       break;
//
//    // estrategias
//    case 11: delay (ESPERA); segue (ESQ, delayFrente); break;
//    case 13: delay (ESPERA); segue (DIR, delayFrente); break;
//    case 14: delay (ESPERA); segue (ESQ, 0); break;
//    case 16: delay (ESPERA); segue (DIR, 0); break;
//  }
}
