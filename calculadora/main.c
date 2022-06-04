#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utilitarios.h"
#include "InfixoParaPosfixo.h"

int ExpressaoCorreta(char *expressao)
{
    int ap = 0, fp = 0, i = 0;

    if(expressao[0] == '\0') //se a express�o estiver vazia, j� retorna como errada
        return 0;

    for(i = 0; expressao[i] != '\0'; i++) //� executado at� atingir o fim da expressao
    {
        if(expressao[i] == '(') //verifica se � abertura de parenteses, se sim, aumenta seu respectivo contador
            ap++;
        if(expressao[i] == ')') //verifica se � fechamento de parenteses, se sim, aumenta seu respectivo contador
            fp++;

        if(!EhOperador(expressao[i]) && !EhOperando(expressao[i]) && expressao[i] != '(' && expressao[i] != ')') //verifica se h� somente caracteres v�lidos
            return 0;

        if(EhOperando(expressao[i]) && EhOperando(expressao[i+1]) && expressao[i+1] != '\0') //verifica se h� dois operandos consecutivos
            return 0;
        else if(expressao[i] == '~' && EhOperando(expressao[i-1]))//verifica se antes da nega��o � um operando
            return 0;
        else if(EhOperador(expressao[i]) && expressao[i+1] == ')') //verifica se depois de um operador n�o h� um fechamento de parenteses
            return 0;
        if(EhOperador(expressao[i]) && EhOperador(expressao[i+1]) && expressao[i+1] != '\0')
        {
            //verifica se h� dois operadores consecutivos e se o segundo n�o � uma nega��o
            if(expressao[i+1] != '~')
                return 0;
            else if(EhOperando(expressao[i]) && EhOperador(expressao[i+1]) && !EhOperando(expressao[i+2]) && expressao[i+2] != '(' && expressao[i+1] != '\0' && expressao[i+2] != '\0')
            {
                //verifica se depois de um operador n�o h� um operando ou abertura de parenteses
                return 0;
            }
        }
    }

    if(ap == fp) //verifica se os contadores de abertura e fechamento de parenteses s�o iguais pra determinar se a expressao � v�lida ou n�o
        return 1;
    else
        return 0;
}

char* ResolveExpressao(char* expressao)
{
    int i = 0;
    PilhaDinamica pAux;
    CriaPilha(&pAux, -1, NULL);

    //printf("1 - Expressao: %s   Expressao[%d]: %c\n", expressao, i, expressao[i]);
    //printf("1 - Expressao: %s   Expressao[%d]: %c\n", expressao, i, expressao[i]);

    for(i = 0; expressao[i] != '\0'; i++)//realiza as opera��es at� atingir o fim da expressao
    {
        //printf("2 - Expressao: %s   Expressao[%d]: %c\n", expressao, i, expressao[i]);
        if(EhOperando(expressao[i]))//se for um operando, ele � simplesmente empilhado
        {
            //printf("3 - Expressao: %s   Expressao[%d]: %c\n", expressao, i, expressao[i]);
            Empilha(&pAux, expressao[i]);
            //printf("4 - Expressao: %s   Expressao[%d]: %c\n", expressao, i, expressao[i]);
        }
        else if(expressao[i] == '~')
        {
            //se o caracter for uma nega��o, ele desempilha o caracter do topo, faz a nega��o dele e o retorna para a pilha
            char a;
            a = Desempilha(&pAux);

            if(a == '0')
                Empilha(&pAux, '1');
            if(a == '1')
                Empilha(&pAux, '0');
        }
        else if(expressao[i] == '^')
        {
            /*se for uma conjun��o, ele desempilha os dois ultimos operandos e retorna o resultado da conjun��o entre eles*/
            char a, b;
            a = Desempilha(&pAux);
            b = Desempilha(&pAux);

            if(a == '1' && b == '1')
                Empilha(&pAux, '1');
            else if(a == '1' && b == '0')
                Empilha(&pAux, '0');
            else if(a == '0' && b == '1')
                Empilha(&pAux, '0');
            else if(a == '0' && b == '0')
                Empilha(&pAux, '0');
        }
        else if(expressao[i] == 'v')
        {
            /*se for uma conjun��o, ele desempilha os dois ultimos operandos e retorna o resultado da disjun��o inclusiva entre eles*/
            char a, b;
            a = Desempilha(&pAux);
            b = Desempilha(&pAux);

            if(a == '1' && b == '1')
                Empilha(&pAux, '1');
            else if(a == '1' && b == '0')
                Empilha(&pAux, '1');
            else if(a == '0' && b == '1')
                Empilha(&pAux, '1');
            else if(a == '0' && b == '0')
                Empilha(&pAux, '0');
        }
        else if(expressao[i] == '_')
        {
            /*se for uma conjun��o, ele desempilha os dois ultimos operandos e retorna o resultado da disjun��o exclusiva entre eles*/
            char a, b;
            a = Desempilha(&pAux);
            b = Desempilha(&pAux);

            if(a == '1' && b == '1')
                Empilha(&pAux, '0');
            else if(a == '1' && b == '0')
                Empilha(&pAux, '1');
            else if(a == '0' && b == '1')
                Empilha(&pAux, '1');
            else if(a == '0' && b == '0')
                Empilha(&pAux, '0');
        }
        else if(expressao[i] == '>')
        {
            /*se for uma conjun��o, ele desempilha os dois ultimos operandos e retorna o resultado do condicional entre eles*/
            char a, b;
            a = Desempilha(&pAux);
            b = Desempilha(&pAux);

            if(b == '1' && a == '1')
                Empilha(&pAux, '1');
            else if(b == '1' && a == '0')
                Empilha(&pAux, '0');
            else if(b == '0' && a == '1')
                Empilha(&pAux, '1');
            else if(b == '0' && a == '0')
                Empilha(&pAux, '1');
        }
        else if(expressao[i] == '|')
        {
            /*se for uma conjun��o, ele desempilha os dois ultimos operandos e retorna o resultado do bicondicional entre eles*/
            char a, b;
            a = Desempilha(&pAux);
            b = Desempilha(&pAux);

            if(a == '1' && b == '1')
                Empilha(&pAux, '1');
            else if(a == '1' && b == '0')
                Empilha(&pAux, '0');
            else if(a == '0' && b == '1')
                Empilha(&pAux, '0');
            else if(a == '0' && b == '0')
                Empilha(&pAux, '1');
        }
        //printf("5 - Expressao: %s   Expressao[%d]: %c\n", expressao, i, expressao[i]);
    }

    return Desempilha(&pAux); //retorna o resultado final da express�o
}

void RemoveQuebraDeLinha(char* expressao)//utilizada para retirar o '\n' do vetor expressao
{
    int i = 0;
    for(i = 0; i < strlen(expressao); i++)
    {
        if(expressao[i] == '\n')
        {
            expressao[i] = '\0';
            return;
        }
    }
}

int main()
{
    char expressao[256];
    int i = 55;

    while(1)
    {
        printf("1 - Digitar a expressao\n2 - Ler as expressoes do arquivo (\"expressoes.txt\")\n0 - Finalizar aplicacao\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &i);
        limpaBufferTeclado();

        system("cls"); //limpa a tela ap�s a op��o escolhida

        switch(i)
        {
        case 1://expressao inserida diretamente no console
        {
            printf("Digite a expressao:\n");
            gets(expressao);
            limpaBufferTeclado();
            RemoveQuebraDeLinha(expressao);

            if(ExpressaoCorreta(expressao))//verifica se a expressao est� correta
            {
                //faz a convers�o da express�o e j� a resolve retornando seu resultado
                char posfixo[256];
                memset(posfixo, 0, 256);
                strcpy(posfixo, InfixoParaPosfixo(expressao));
                char resp = ResolveExpressao(posfixo);
                printf("Resultado: %c\n", resp);
            }
            else
                printf("Expressao Incorreta!\n");

            memset(expressao, 0, 256); //coloca o valor 0 em todas as posi��es do vetor expressao
            break;
        }
        case 2://expressoes lidas do arquivo
        {
            FILE* in = fopen("expressoes.txt", "r");//abre o arquivo de expressoes em modo somente leitura
            FILE* out = fopen("resultados.txt", "w");//abre o arquivo de resultados em modo somente escrita (sobreescreve o arquivo atual)

            if(!in)//caso o arquivo de leitura n�o consiga ser aberto, a opera��o toda � cancelada
            {
                printf("Erro na abertura do arquivo de expressoes!\n");
                fclose(in);
                fclose(out);
                break;
            }

            while(!feof(in))
            {
                /*enquanto o fim do arquivo n�o � atingido, � lido cada linha, removido a quebra de linha de cada linha
                verificado se a express�o da linha atual est� correta, se sim, ela � resolvida e seu resultado � colocado
                no arquivo de sa�da, caso n�o estiver correta, � colocado uma mensagem de erro no arquivo de sa�da*/
                fgets(expressao, 256, in);
                RemoveQuebraDeLinha(expressao);

                if(ExpressaoCorreta(expressao))
                {
                    char posfixo[256];
                    memset(posfixo, 0, 256);
                    strcpy(posfixo, InfixoParaPosfixo(expressao));
                    char resp = ResolveExpressao(posfixo);
                    fprintf(out, "%c\n", resp);
                }
                else
                    fprintf(out, "Expressao Incorreta!\n");

                memset(expressao, 0, 256);//coloca o valor 0 em todas as posi��es do vetor expressao
            }

            //fecha os arquivos de entrada e sa�da
            fclose(in);
            fclose(out);

            break;
        }
        case 0://sai da aplica��o
        {
            exit(EXIT_SUCCESS);
            break;
        }
        default://avisa o usu�rio que a op��o escolhida � inv�lida
        {
            printf("Opcao invalida\n");
            break;
        }
        }
    }

    /*char expressao[] = "0~";
    char resp = ResolveExpressao(expressao);

    printf("%c", resp);*/

    return 0;
}
