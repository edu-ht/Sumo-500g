//------------------------------------------------------------------------------
// YAPIRA - SUMO 500g
//------------------------------------------------------------------------------

#define DIR 0
#define ESQ 1
#define RAPIDO   192
#define LENTO    128

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
void setup () {

  Serial.begin(9600);
  pinMode (motorDirF, OUTPUT);
  pinMode (motorDirT, OUTPUT);
  pinMode (motorEsqF, OUTPUT);
  pinMode (motorEsqT, OUTPUT);
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

void loop () {

  motor (andaF, LENTO, RAPIDO);
  delay (500);
  motor (andaF, RAPIDO, LENTO);
  delay (500);
}
