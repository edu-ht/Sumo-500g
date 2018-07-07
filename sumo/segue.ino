//------------------------------------------------------------------------------
// Procura o oponente comecando pela direcao 'dir', segue ele quando encontrado.
// Pode avancar pra frente por determinado 'tempo', em ms, antes da procura.
//------------------------------------------------------------------------------
void segue (int dir, int tempo) {

  //frente(tempo);

  //digitalWrite (motorDirF, HIGH);
  //digitalWrite (motorDirT, LOW);
  //digitalWrite (motorEsqF, HIGH);
  //digitalWrite (motorEsqT, LOW);

  while (true) {

    lerSensores();
    //linha(dir);

    // gira na ultima direcao vista do oponente
    // quando o encontra vai pra frente
    // quando o detecta no sensor do lado oposto muda de direcao
    switch (dir) {
      case DIR:
        if (proxDir > MINPROX && proxEsq > MINPROX) {
          // frente
          Serial.println("Dir: FRENTE1");
          motor (andaF, 255, 255);
          //analogWrite (pwmEsq, 128);
          //analogWrite (pwmDir, 128);
          digitalWrite (13, HIGH);
        } else if (proxEsq > MINPROX) {
          // esq
          Serial.println("Dir: ESQ1");
          dir = ESQ;
        } else {
          // dir
          Serial.println("Dir: DIR1");
          motor (andaF, 191, 90);
          //analogWrite (pwmEsq, 128);
          //analogWrite (pwmDir, 0);
          digitalWrite (13, LOW);
        } break;
      case ESQ:
        if (proxDir > MINPROX && proxEsq > MINPROX) {
          // frente
          Serial.println("Dir: FRENTE2");
          motor (andaF, 255, 255);
          //analogWrite (pwmEsq, 128);
          //analogWrite (pwmDir, 128);
          digitalWrite (13, HIGH);
        } else if (proxDir > MINPROX) {
          // dir
          Serial.println("Dir: DIR2");
          dir = DIR;
        } else {
          // esq
          Serial.println("Dir: ESQ2");
          motor (andaF, 90, 191);
          //analogWrite (pwmEsq, 90);
          //analogWrite (pwmDir, 191);
          digitalWrite (13, LOW);
        } break;
    }
    //imprimir_sensores();
    delay (10);
  }

}

//------------------------------------------------------------------------------
// Avancar para frente por um periodo de tempo
//------------------------------------------------------------------------------
void imprimir_sensores()
{
  Serial.print("proxDir: ");  Serial.println(proxDir);
  Serial.print("proxEsq: ");  Serial.println(proxEsq);
  Serial.print("linhaDir: "); Serial.println(linhaDir);
  Serial.print("linhaEsq: "); Serial.println(linhaEsq);
  Serial.println("--------------------------------------------------------------------");
}

//------------------------------------------------------------------------------
// Avancar para frente por um periodo de tempo
//------------------------------------------------------------------------------
void frente (int tempo) {

  motor(andaF, 255, 255);
  //Serial.println("Frente");

  // delay por tempo delimitado
  for (int i = 0; i <= tempo; i++){
    lerSensores();

    // se detectou qualquer coisa sai da funcao
    if (proxDir > MINPROX || proxEsq > MINPROX ||
        linhaDir > MINLINHA || linhaEsq > MINLINHA) break;
    delay(1);
  }

}
