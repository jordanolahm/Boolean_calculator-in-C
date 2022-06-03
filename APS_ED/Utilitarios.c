#include <stdio.h>

#include "Utilitarios.h"

void limpaBufferTeclado()
{
    int ch;

    do
        ch = fgetc(stdin);
    while(ch != EOF && ch != '\n' );
}
