//------------------------------------------------------------------------------
// YAPIRA - SUMO 500g
//------------------------------------------------------------------------------

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
#define pinoProxDir   A3
#define pinoProxEsq   A0
#define pinoLinhaDir  A2
#define pinoLinhaEsq  A1

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
