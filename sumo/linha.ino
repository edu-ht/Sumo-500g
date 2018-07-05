//------------------------------------------------------------------------------
// Detecta linha e evita saida da arena
//------------------------------------------------------------------------------
void linha (int dir) {

  // se nao detectou linha sai da funcao
  if (linhaDir > MINLINHA && linhaEsq > MINLINHA) return;

  motor (andaT, 255, 255);
  delay (delayFreioLinha);
  switch (dir) {
    case DIR: motor (giraD, RAPIDO, RAPIDO);
    case ESQ: motor (giraE, RAPIDO, RAPIDO);
  }
  delay (delayFreioGiro);
}
