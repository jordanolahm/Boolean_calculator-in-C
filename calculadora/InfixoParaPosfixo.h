#ifndef INFIXOPARAPOSFIXO_H_INCLUDED
#define INFIXOPARAPOSFIXO_H_INCLUDED
#include <string.h>
#include "PilhaDinamica.h"

int EhOperador(char C);
int EhOperando(char C);
char* InfixoParaPosfixo(char* expressao);

#endif // INFIXOPARAPOSFIXO_H_INCLUDED
