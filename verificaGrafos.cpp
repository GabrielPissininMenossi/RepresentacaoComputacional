#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define LINHA 100
#define COLUNA 100

// structs
typedef struct listaAdjacencia
{
    char vertice;
    int peso;
    struct listaAdjacencia *head, *tail;
} ListaAdjacencia;

// pequeno tad da lista adjacencia
ListaAdjacencia *novaCaixaLista(void)
{
    ListaAdjacencia *nova = (ListaAdjacencia *)malloc(sizeof(ListaAdjacencia));
    //memset(nova->vertice, '\0', sizeof(nova->vertice));
    nova->vertice = '0';
    nova->peso = 0;
    nova->head = nova->tail = NULL;
    return nova;
}

// protótipos
char grafoCompleto(char grafo[LINHA][COLUNA], int l, int c);
char grafoRegular(char grafo[LINHA][COLUNA], int l, int c);
char grafoOrientado(char grafo[LINHA][COLUNA], int l, int c);
char grafoNaoOrientado(char grafo[LINHA][COLUNA], int l, int c);

// funções
char grafoCompleto(char grafo[LINHA][COLUNA], int l, int c)
{
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (i == j)
            {
                if (grafo[i][j] == 1)
                    return 0;
            }
            else
            {
                if (grafo[i][j] == 0)
                    return 0;
            }
        }
    }
    return 1;
}

void verificaSimplesAdjacencia(int m[LINHA][COLUNA], int *simples, int v)
{
    // o 'v' -> vertices
    *simples = 0; // para nao depender de nenhum valor externo, pois pode ocorrer de nunca entrar no if
    for (int i = 0; i < v; i++)
        if (m[i][i] != 0)
            *simples = 1;
}

char grafoRegular(char grafo[LINHA][COLUNA], int l, int c)
{
    int soma = 0, somaLinha, linhaAtual;
    for (int i = 0; i < c; i++)
    {
        if (grafo[0][i] == 1)
            soma++;
    }
    linhaAtual = 1;
    somaLinha = 0;
    for (int i = 1; i < l; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (linhaAtual != i)
            {
                linhaAtual = i;
                if (somaLinha != soma)
                    return 0;
                somaLinha = 0;
            }
            if (grafo[i][j] == 1)
                somaLinha++;
        }
    }
    return 1;
}

// menus
int menuPrincipal()
{
    int opc;
    printf("*** MENU PRINCIPAL ***\n");
    printf("[1] Matriz Adjacencia\n");
    printf("[2] Matiz de Incidencia\n");
    printf("[3] Lista de Adjacencia\n");
    printf("[10] SAIR\nOpcao: ");
    scanf("%d", &opc);
    return opc;
}

int subMenuAdjacencia()
{
    int opc;
    printf("*** SUBMENU MATRIZ DE ADJACENCIA ***");
    printf("[1] - Simples\n");
    printf("[2] - Regular\n");
    printf("[3] - Completo\n");
    printf("[10] - SAIR\nOpcao: ");
    scanf("%d", &opc);
    return opc;
}

// converter matriz de adjacencia para lista de adjacencia
ListaAdjacencia **converterArquivoToLista(FILE *ptrArquivo)
{
    ListaAdjacencia *lista = novaCaixaLista();
    char charAtual, num[10];
    int quantVertices, indiceVertices, numTL;

    // pegar a quantidade de vertices na primeira linha
    quantVertices = 0;
    fseek(ptrArquivo, 0, 0);
    charAtual = getc(ptrArquivo);
    while (charAtual != '\n')
    {
        if (charAtual != ',')
        {
            quantVertices++;
        }
        charAtual = getc(ptrArquivo);
    }
    printf("Quantidade de vertices do grafo: %d\n", quantVertices);

    // criar o vetor contendo os vértices
    ListaAdjacencia *vertices[quantVertices];
    fseek(ptrArquivo, 0, 0);
    charAtual = getc(ptrArquivo);
    indiceVertices = 0;
    while (charAtual != '\n')
    {
        if (charAtual != ',')
        {
            vertices[indiceVertices] = (ListaAdjacencia *)malloc(sizeof(ListaAdjacencia));
            vertices[indiceVertices]->vertice = charAtual;
            indiceVertices++;
        }
        charAtual = getc(ptrArquivo);
    }
    printf("Indice vertices: %d\n", indiceVertices);

    // continuar a leitura do grafo para a criação da lista
    fseek(ptrArquivo, 0, 0);
    charAtual = getc(ptrArquivo);
    indiceVertices = 0;
    numTL = 0;
    memset(num, sizeof(num), '\0'); // inicializar a minha string com todas as posições contendo o final de string
    while (!feof(ptrArquivo))
    {
        // em cada linha pegar as ligações do no com os outros
        while (!feof(ptrArquivo) && charAtual != ',' && charAtual != '\n')
        {
            num[numTL] = charAtual; // vou compondo o meu número

            charAtual = getc(ptrArquivo);
        }
        // se verdade completei um número
        if (charAtual == ',')
        {
        }
        charAtual = getc(ptrArquivo);
    }

    return NULL; // temporario
}

void converteArquivoToMatrizAdj(FILE *ptr, int grafo[LINHA][COLUNA], int *vert)
{
    char charAtual, numExtenso[10];
    int extensoTL = 0, lin = 0, col = 0;
    memset(numExtenso, '\0', sizeof(numExtenso));

    // passa a primeira linha e verifica os vertices do grafo
    *vert = 0;
    fseek(ptr, 0, 0);
    charAtual = getc(ptr);
    while (!feof(ptr) && charAtual != '\n')
    {
        if (charAtual != ',')
        {
            (*vert)++;
        }
        charAtual = getc(ptr);
    }
    printf("Exibir o vert: %d\n", *vert);

    // preencher a matriz
    charAtual = getc(ptr); // para n chegar verificando o '\n'
    while (!feof(ptr))
    {
        while (!feof(ptr) && charAtual != '\n')
        {
            if (charAtual == ',')
            {
                printf("Exibicao do Atoi: %d\n", atoi(numExtenso));
                grafo[lin][col++] = atoi(numExtenso);
                memset(numExtenso, '\0', sizeof(numExtenso)); // limpo o numero em extenso
                // extensoTL = 0; //zero o tl do numero em extenso
            }
            else
            {
                numExtenso[strlen(numExtenso)] = charAtual;
            }
            charAtual = getc(ptr);
        }
        printf("Exibicao do Atoi: %d\n", atoi(numExtenso));
        grafo[lin][col] = atoi(numExtenso);
        lin++;
        col = 0;
        memset(numExtenso, '\0', sizeof(numExtenso));
        charAtual = getc(ptr);
    }
    printf("oi\n");

    // printar a minha matriz para saber se realmente está correta:
    printf("\n\nExibicao da matriz depois de extraido do arquivo:\n");
    for (int i = 0; i < *vert; i++)
    {
        for (int j = 0; j < *vert; j++)
        {
            printf("[%d]", grafo[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    // o grafo será representado pela matriz de adjacência
    int grafo[LINHA][COLUNA] = {}, vert = 0, opc, opcInterno, simples;
    FILE *ptr = fopen("entrada.txt", "r");

    do
    {
        opc = menuPrincipal();
        switch (opc)
        {
        case 1:
        {
            // se entrou aqui é porque vou utilizar matriz de adjacencia
            converteArquivoToMatrizAdj(ptr, grafo, &vert);
            opcInterno = subMenuAdjacencia();
            switch (opcInterno)
            {
            case 1:
            {
                // tratar se o grafo eh simples
                verificaSimplesAdjacencia(grafo, &simples, vert);
                if (simples == 1)
                    printf("Nao eh um grafo simples!!\n");
                else
                    printf("Eh um grafo simples!\n");

                break;
            }
            case 2:
            {
                // tratar se o grafo eh regular

                break;
            }
            case 3:
            {
                // tratar se o grafo eh completo

                break;
            }
            default:
            {
                printf("Digite um valor valido ou '10' para sair!!\n");
            }
            }

            break;
        }
        case 2:
        {

            break;
        }
        case 3:
        {

            break;
        }
        default:
        {
            printf("Digite um valor valido ou '10' para sair!!\n");
        }
        }
    } while (opc != 10);

    // TESTES
    //  converterArquivoToLista(ptr);
    // converteArquivoToMatrizAdj(ptr, grafo, &vert);

    return 0;
}
