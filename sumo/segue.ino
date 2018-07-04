//------------------------------------------------------------------------------
// Procura o oponente comecando pela direcao 'dir', segue ele quando encontrado.
// Pode avancar pra frente por determinado 'tempo', em ms, antes da procura.
//------------------------------------------------------------------------------
void segue (int dir, int tempo) {

  frente(tempo);

  while (true) {

    lerSensores();
    // if (linhaDir > MINLINHA || linhaEsq > MINLINHA) linha();

    // gira na ultima direcao vista do oponente
    // quando o encontra vai pra frente
    // quando o detecta no sensor do lado oposto muda de direcao
    switch (dir) {
      case DIR:
        if (linhaDir > MINPROX && linhaEsq > MINPROX) {
          // frente
          motor (andaF, RAPIDO);
        } else if (linhaEsq > MINPROX) {
          // esq
          dir = ESQ;
        } else {
          // dir
          motor (andaD, LENTO);
        }
      case ESQ:
        if (linhaDir > MINPROX && linhaEsq > MINPROX) {
          // frente
          motor (andaF, RAPIDO);
        } else if (linhaDir > MINPROX) {
          // dir
          dir = DIR;
        } else {
          // esq
          motor (andaE, LENTO);
        }
    }
  }

}

//------------------------------------------------------------------------------
// Avancar para frente por um periodo de tempo
//------------------------------------------------------------------------------
void frente (int tempo) {

  motor(andaF, RAPIDO);

  // delay por tempo delimitado
  for (int i = 0; i <= tempo; i++){
    lerSensores();

    // se detectou qualquer coisa sai da funcao
    if (proxDir > MINPROX || proxEsq > MINPROX ||
        linhaDir > MINLINHA || linhaEsq > MINLINHA) break;
    delay(1);
  }

}
