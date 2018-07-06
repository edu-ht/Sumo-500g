//------------------------------------------------------------------------------
// YAPIRA - SUMO 500g
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Pinos dos sensores
//------------------------------------------------------------------------------
#define pinoProxDir   0
#define pinoProxEsq   3
#define pinoLinhaDir  1
#define pinoLinhaEsq  2

//------------------------------------------------------------------------------
// Variaveis de estado
//------------------------------------------------------------------------------
int proxDir, proxEsq;     // valores dos sensores de proximidade
int linhaDir, linhaEsq;   // valores dos sensores de linha

void setup () {

  Serial.begin(9600);
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
  lerSensores();
  imprimir_sensores();
  delay(500);
}
