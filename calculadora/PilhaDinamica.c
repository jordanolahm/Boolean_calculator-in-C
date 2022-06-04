#include <stdlib.h>

#include "PilhaDinamica.h"

NoPilha* CriaNoPilha(char *_ptrElemento)
{
    NoPilha *ptrNoPilhavo = (NoPilha *) malloc(sizeof(NoPilha));
    if ( !ptrNoPilhavo )
        return NULL;

    ptrNoPilhavo->ptrElemento = _ptrElemento;
    ptrNoPilhavo->ptrProx     = NULL;

    return ptrNoPilhavo;
}
void CriaPilha(PilhaDinamica *ptrPilha, int _maxElementos,
               int (*_ptrFncCopia)   (char*, char*) )
{
    // inicializa valores da Pilha
    ptrPilha->qtdeElementos = 0;
    ptrPilha->maxElementos  = _maxElementos;

    ptrPilha->ptrTopo = NULL;

    ptrPilha->ptrFncCopia = _ptrFncCopia;
}
PilhaDinamica* CriaPilha2(int _maxElementos,
            int (*_ptrFncCopia)(char*, char*) )
{
    // tenta criar a Pilha
    PilhaDinamica *ptrPilha = (PilhaDinamica *) malloc(sizeof(PilhaDinamica));

    // testa se a Pilha NAO foi criada
    if ( !ptrPilha )
        return NULL;

    // inicializa valores da Pilha
    ptrPilha->qtdeElementos = 0;
    ptrPilha->maxElementos  = _maxElementos;

    ptrPilha->ptrTopo = NULL;

    ptrPilha->ptrFncCopia   = _ptrFncCopia;

    // retorna Pilha construida
    return ptrPilha;
}
int Empilha(PilhaDinamica *ptrPilha, char *ptrElemento)
{
    // verifica se ha espaco para o novo elemento
    if (ptrPilha->maxElementos  != -1 &&
        ptrPilha->qtdeElementos == ptrPilha->maxElementos)
        return 0;
    // posiciona novo elemento na Pilha
    NoPilha *ptrNoPilhavo = CriaNoPilha( ptrElemento );
    if ( !ptrNoPilhavo )
        return -1;

    ptrNoPilhavo->ptrProx  = ptrPilha->ptrTopo;
    ptrPilha->ptrTopo = ptrNoPilhavo;
    // incrementa contador de elementos
    ptrPilha->qtdeElementos++;
    return 1;
}
char* Desempilha(PilhaDinamica *ptrPilha)
{
    // testa se a pilha esta vazia
    if ( !ptrPilha->qtdeElementos )
        return NULL;

    // salva referencia para NoPilha e Elemento/dado
    NoPilha   *ptrNoPilha       = ptrPilha->ptrTopo;
    void *ptrElemento = ptrNoPilha->ptrElemento;

    // exlcui elemento da pilha
    ptrPilha->ptrTopo = ptrPilha->ptrTopo->ptrProx;

    // libera memoria do NoPilha
    free( ptrNoPilha );

    // decrementa contador de elementos
    ptrPilha->qtdeElementos--;
    return ptrElemento;
}
int ConsultaPilha(PilhaDinamica *ptrPilha, char *ptrElementoSaida)
{
    // verifica se ha elementos na Pilha
    if ( !ptrPilha->qtdeElementos )
        return 0;

    return ptrPilha->ptrFncCopia(ptrElementoSaida, ptrPilha->ptrTopo->ptrElemento);
}
int AlteraPilha(PilhaDinamica *ptrPilha, char *ptrNoPilhavo)
{
    // verifica se ha elementos na Pilha
    if ( !ptrPilha->qtdeElementos )
        return 0;

    return ptrPilha->ptrFncCopia(ptrPilha->ptrTopo->ptrElemento, ptrNoPilhavo);
}
int Vazia(PilhaDinamica *ptrPilha)
{
    if(!ptrPilha->ptrTopo)
        return 1;
    else
        return 0;
}
char* Topo(PilhaDinamica *ptrPilha)
{
    if(!ptrPilha->qtdeElementos)
        return NULL;

    return ptrPilha->ptrTopo->ptrElemento;
}
