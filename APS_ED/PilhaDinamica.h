#ifndef PILHADINAMICA_H_INCLUDED
#define PILHADINAMICA_H_INCLUDED

typedef struct NoPilhaPilha
{
    char      *ptrElemento;
    struct NoPilha *ptrProx;
}NoPilha;

typedef struct
{
    int qtdeElementos;
    int maxElementos;
    NoPilha  *ptrTopo;

    int (*ptrFncCopia)  (char *ptrDestino , char *ptrOrigem);
} PilhaDinamica;

void CriaPilha(PilhaDinamica *ptrPilha, int _maxElementos,
               int (*_ptrFncCopia)   (char*, char*) );
PilhaDinamica* CriaPilha2(int _maxElementos,
            int (*_ptrFncCopia)  (char*, char*) );

int Empilha     (PilhaDinamica *ptrPilha, char *ptrElemento);
char* Desempilha(PilhaDinamica *ptrPilha);
int ConsultaPilha    (PilhaDinamica *ptrPilha, char *ptrElementoSaida);
int AlteraPilha      (PilhaDinamica *ptrPilha, char *ptrNoPilhavo);
int Vazia       (PilhaDinamica *ptrPilha);
char* Topo      (PilhaDinamica *ptrPilha);

#endif // PILHADINAMICA_H_INCLUDED
