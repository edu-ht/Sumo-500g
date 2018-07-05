//------------------------------------------------------------------------------
// YAPIRA - SUMO 500g
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Pinos dos motores
//------------------------------------------------------------------------------
#define pwmEsq    9   // valor 'analogico' da velocidade dos motores
#define pwmDir    3   // valor 'analogico' da velocidade dos motores
#define motorDirF 12  // quando HIGH faz motor direito ir para frente
#define motorDirT 9   // quando HIGH faz motor direito ir para tras
#define motorEsqF 8
#define motorEsqT 7

//------------------------------------------------------------------------------
// Pinos dos sensores
//------------------------------------------------------------------------------
#define pinoProxDir   3
#define pinoProxEsq   0
#define pinoLinhaDir  2
#define pinoLinhaEsq  1

//------------------------------------------------------------------------------
// Variaveis de estado
//------------------------------------------------------------------------------
int proxDir, proxEsq;     // valores dos sensores de proximidade
int linhaDir, linhaEsq;   // valores dos sensores de linha

void setup () {

  Serial.begin(9600);
  pinMode(motorDirF, OUTPUT);
  pinMode(motorDirT, OUTPUT);
  pinMode(motorEsqF, OUTPUT);
  pinMode(motorEsqT, OUTPUT);
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

//------------------------------------------------------------------------------
// Imprime valor dos sensores na tela
//------------------------------------------------------------------------------
void imprimir_sensores()
{
  Serial.print("proxDir: ");  Serial.println(proxDir);
  Serial.print("proxEsq: ");  Serial.println(proxEsq);
  Serial.print("linhaDir: "); Serial.println(linhaDir);
  Serial.print("linhaEsq: "); Serial.println(linhaEsq);
  Serial.println("--------------------------------------------------------------------");
}

void loop() {
  testar_sensores();
  imprimir_sensores();
  delay(500);
}
