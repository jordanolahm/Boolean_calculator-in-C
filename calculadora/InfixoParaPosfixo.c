#include "InfixoParaPosfixo.h"


int PesoDoOperador(char op) //determina o peso do operador passado no par�metro de acordo com sua preced�ncia
{
	int peso = -1;
    switch(op)
    {
    case '|': //bicondicional
        peso = 1;
        break;
    case '>': //condicional
        peso = 2;
        break;
    case '_': //disjun��o exclusiva
        peso = 3;
        break;
    case 'v': //disjun��o inclusiva
        peso = 4;
        break;
    case '^': //conjun��o
        peso = 5;
        break;
    case '~': //nega��o
        peso = 6;
        break;
    }

	return peso;
}

int TemMaiorPrecedencia(char op1, char op2) //verifica se o operador 1 (op1) tem maior preced�ncia que o operador 2 (op2)
{
	int op1Peso = PesoDoOperador(op1);
	int op2Peso = PesoDoOperador(op2);

	return op1Peso > op2Peso ?  1 : 0;
}

int EhOperador(char C) //verifica se o caracter passado no par�metro � um operador v�lido
{
	if(C == '~' || C == '^' || C == 'v' || C == '_' || C == '>' || C == '|')
		return 1;

	return 0;
}

int EhOperando(char C) //verifica se o caracter passado no par�metro � um operando v�lido
{
	if(C == '0' || C == '1')
        return 1;

	return 0;
}

char* InfixoParaPosfixo(char* expressao)
{
	PilhaDinamica S;
	CriaPilha(&S, -1, NULL);
	char posfixo[256];
	memset(posfixo, NULL, 256);
	int i;
	for(i = 0; i < strlen(expressao);i++)
    {
		if(EhOperador(expressao[i])) //verifica se o caracter na posi��o i � um operador e realiza as opera��es abaixo
		{
		    if(expressao[i] == '~' && expressao[i-1] == '(' && EhOperando(expressao[i+1]))
            {
                /*caso o operador em quest�o for uma nega��o,
                o caracter for a abertura de parenteses e o proximo caracter for um operando,
                ele coloca o operando da posicao [i+1] no fim da sa�da p�sfixa e
                depois coloca a nega��o logo em seguida no fim da sa�da p�sfixa,
                depois ele vai pra pr�xima posi��o do vetor e inicia todas as verifica��es novamente*/
                posfixo[strlen(posfixo)] = expressao[i+1];
                posfixo[strlen(posfixo)] = expressao[i];
                i++;
                continue;
            }

			while(!Vazia(&S) && Topo(&S) != '(' && TemMaiorPrecedencia(Topo(&S),expressao[i]))
			{
			    /*se a pilha n�o estiver vazia, o topo da pilha n�o for uma abertura de parenteses e
			    o operador na posi��o i tiver menor precedencia em rela��o ao operador no topo da pilha,
			    o operador que estiver no topo ser� jogado para o fim da sa�da p�sfixa e ser� desempilhado*/
				posfixo[strlen(posfixo)] = Topo(&S);
				Desempilha(&S);
			}

			Empilha(&S, expressao[i]); //empilha o operador atual
		}
		else if(EhOperando(expressao[i]))//se o caracter na posicao i for um operando, ele � jogado direto no fim da sa�da p�sfixa
		{
			posfixo[strlen(posfixo)] = expressao[i];
		}
		else if (expressao[i] == '(')//caso for uma abertura de parenteses, ele � empilhado
		{
			Empilha(&S, expressao[i]);
		}
		else if(expressao[i] == ')')
		{
		    /*caso o caracter na posicao i for um fechamento de parenteses,
		    � verificado se a pilha n�o est� vazia e se o topo da pilha n�o � uma abertura de parenteses*/
			while(!Vazia(&S) && Topo(&S) !=  '(') {
                //coloca o operador que estiver no topo no fim da sa�da p�sfixa e o retira da pilha;
				posfixo[strlen(posfixo)] = Topo(&S);
				Desempilha(&S);
			}

			//como agora o caracter do topo � uma abertura de parenteses, ele � retirado da pilha
			Desempilha(&S);
		}
	}

	while(!Vazia(&S))//enquanto a pilha n�o estiver vazia, ele vai colocando cada operador no fim da sa�da p�sfixa e vai desempilhando
    {
		posfixo[strlen(posfixo)] = Topo(&S);
		Desempilha(&S);
	}

	return posfixo; //retorna o resultado da sa�da p�sfixa
}
