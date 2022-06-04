#include "InfixoParaPosfixo.h"


int PesoDoOperador(char op) //determina o peso do operador passado no parâmetro de acordo com sua precedência
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
    case '_': //disjunção exclusiva
        peso = 3;
        break;
    case 'v': //disjunção inclusiva
        peso = 4;
        break;
    case '^': //conjunção
        peso = 5;
        break;
    case '~': //negação
        peso = 6;
        break;
    }

	return peso;
}

int TemMaiorPrecedencia(char op1, char op2) //verifica se o operador 1 (op1) tem maior precedência que o operador 2 (op2)
{
	int op1Peso = PesoDoOperador(op1);
	int op2Peso = PesoDoOperador(op2);

	return op1Peso > op2Peso ?  1 : 0;
}

int EhOperador(char C) //verifica se o caracter passado no parâmetro é um operador válido
{
	if(C == '~' || C == '^' || C == 'v' || C == '_' || C == '>' || C == '|')
		return 1;

	return 0;
}

int EhOperando(char C) //verifica se o caracter passado no parâmetro é um operando válido
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
		if(EhOperador(expressao[i])) //verifica se o caracter na posição i é um operador e realiza as operações abaixo
		{
		    if(expressao[i] == '~' && expressao[i-1] == '(' && EhOperando(expressao[i+1]))
            {
                /*caso o operador em questão for uma negação,
                o caracter for a abertura de parenteses e o proximo caracter for um operando,
                ele coloca o operando da posicao [i+1] no fim da saída pósfixa e
                depois coloca a negação logo em seguida no fim da saída pósfixa,
                depois ele vai pra próxima posição do vetor e inicia todas as verificações novamente*/
                posfixo[strlen(posfixo)] = expressao[i+1];
                posfixo[strlen(posfixo)] = expressao[i];
                i++;
                continue;
            }

			while(!Vazia(&S) && Topo(&S) != '(' && TemMaiorPrecedencia(Topo(&S),expressao[i]))
			{
			    /*se a pilha não estiver vazia, o topo da pilha não for uma abertura de parenteses e
			    o operador na posição i tiver menor precedencia em relação ao operador no topo da pilha,
			    o operador que estiver no topo será jogado para o fim da saída pósfixa e será desempilhado*/
				posfixo[strlen(posfixo)] = Topo(&S);
				Desempilha(&S);
			}

			Empilha(&S, expressao[i]); //empilha o operador atual
		}
		else if(EhOperando(expressao[i]))//se o caracter na posicao i for um operando, ele é jogado direto no fim da saída pósfixa
		{
			posfixo[strlen(posfixo)] = expressao[i];
		}
		else if (expressao[i] == '(')//caso for uma abertura de parenteses, ele é empilhado
		{
			Empilha(&S, expressao[i]);
		}
		else if(expressao[i] == ')')
		{
		    /*caso o caracter na posicao i for um fechamento de parenteses,
		    é verificado se a pilha não está vazia e se o topo da pilha não é uma abertura de parenteses*/
			while(!Vazia(&S) && Topo(&S) !=  '(') {
                //coloca o operador que estiver no topo no fim da saída pósfixa e o retira da pilha;
				posfixo[strlen(posfixo)] = Topo(&S);
				Desempilha(&S);
			}

			//como agora o caracter do topo é uma abertura de parenteses, ele é retirado da pilha
			Desempilha(&S);
		}
	}

	while(!Vazia(&S))//enquanto a pilha não estiver vazia, ele vai colocando cada operador no fim da saída pósfixa e vai desempilhando
    {
		posfixo[strlen(posfixo)] = Topo(&S);
		Desempilha(&S);
	}

	return posfixo; //retorna o resultado da saída pósfixa
}
