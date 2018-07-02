void segue (int dir, int tempo) {

  dirOponente = dir;
  frente(tempo);

  while (true) {
    
  }

}

void frente (int tempo) {

  for (int i = 0; i <= tempo; i++){
    lerSensores();
    if (proxDir > MINPROX || proxEsq > MINPROX || linhaDir > MINLINHA || linhaEsq > MINLINHA) break;
    motor(andaF, rapido);
    delay(5);
  }

}
