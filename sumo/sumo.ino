//------------------------------------------------------------------------------
// YAPIRA - SUMO 500g
//------------------------------------------------------------------------------

#define DIR 0
#define ESQ 1
#define RAPIDO  255
#define LENTO   128
#define MINPROX 200 // valor minimo de proximidade para que algo seja detectado

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
#define PWM       10  // valor 'analogico' da velocidade dos motores
#define motorDirF 12  // quando HIGH faz motor direito ir para frente
#define motorDirT 9   // quando HIGH faz motor direito ir para tras
#define motorEsqF 8
#define motorEsqT 7

//------------------------------------------------------------------------------
// Pinos dos sensores
//------------------------------------------------------------------------------
#define pinoProxDir   0
#define pinoProxEsq   0
#define pinoLinhaDir  0
#define pinoLinhaEsq  0

//------------------------------------------------------------------------------
// Variaveis de estado
//------------------------------------------------------------------------------
int dirOponente;          // ultima direcao em que o oponente foi visto
int proxDir, proxEsq;     // valores dos sensores de proximidade
int linhaDir, linhaEsq;   // valores dos sensores de linha

//------------------------------------------------------------------------------
void setup () {

  Serial.begin(9600);
  pinMode(motorDirF, OUTPUT);
  pinMode(motorDirT, OUTPUT);
  pinMode(motorEsqF, OUTPUT);
  pinMode(motorEsqT, OUTPUT);
  analogWrite(PWM, 191);
}

//------------------------------------------------------------------------------
// Controla direcao dos motores e velocidade
//------------------------------------------------------------------------------
void motor (int mov, int vel) {

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
  digitalWrite(motorDirF, df);
  digitalWrite(motorDirT, dt);
  digitalWrite(motorEsqF, ef);
  digitalWrite(motorEsqT, et);
  analogWrite(PWM, vel);
}

//------------------------------------------------------------------------------
// Le valores de todos os sensores e guarda em variaveis globais
//------------------------------------------------------------------------------
void lerSensores () {
  proxDir  = analogRead(pinoProxDir);
  proxEsq  = analogRead(pinoProxEsq);
  linhaDir = analogRead(pinoLinhaDir);
  linhaEsq = analogRead(pinoLinhaEsq);
}

void loop () {
  delay (5000);
  motor (andaF, RAPIDO);
}
