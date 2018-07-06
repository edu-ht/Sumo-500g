//------------------------------------------------------------------------------
// Procura o oponente comecando pela direcao 'dir', segue ele quando encontrado.
// Pode avancar pra frente por determinado 'tempo', em ms, antes da procura.
//------------------------------------------------------------------------------
void segue (int dir, int tempo) {

  frente(tempo);

  while (true) {

    lerSensores();
    //linha(dir);

    // gira na ultima direcao vista do oponente
    // quando o encontra vai pra frente
    // quando o detecta no sensor do lado oposto muda de direcao
    switch (dir) {
      case DIR:
        if (linhaDir > MINPROX && linhaEsq > MINPROX) {
          // frente
          Serial.println("Dir: FRENTE");
          motor (andaF, 255, 255);
        } else if (linhaEsq > MINPROX) {
          // esq
          Serial.println("Dir: ESQ");
          dir = ESQ;
        } else {
          // dir
          Serial.println("Dir: DIR");
          motor (andaF, curvaFora, curvaDentro);
        }
      case ESQ:
        if (linhaDir > MINPROX && linhaEsq > MINPROX) {
          // frente
          Serial.println("Dir: FRENTE");
          motor (andaF, 255, 255);
        } else if (linhaDir > MINPROX) {
          // dir
          Serial.println("Dir: DIR");
          dir = DIR;
        } else {
          // esq
          Serial.println("Dir: ESQ");
          motor (andaF, curvaDentro, curvaFora);
        }
    }
    delay (5);
  }

}

//------------------------------------------------------------------------------
// Avancar para frente por um periodo de tempo
//------------------------------------------------------------------------------
void frente (int tempo) {

  motor(andaF, 255, 255);

  // delay por tempo delimitado
  for (int i = 0; i <= tempo; i++){
    lerSensores();

    // se detectou qualquer coisa sai da funcao
    if (proxDir > MINPROX || proxEsq > MINPROX ||
        linhaDir > MINLINHA || linhaEsq > MINLINHA) break;
    delay(1);
  }

}
