#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

#define LINHA 100
#define COLUNA 100

//structs
typedef struct listaAdjacencia{
    char vertice;
    int peso;
    struct listaAdjacencia *prox;
} ListaAdjacencia;

//pequeno tad da lista adjacencia
ListaAdjacencia* novaCaixaLista(){
    ListaAdjacencia * nova = (ListaAdjacencia*)malloc(sizeof(ListaAdjacencia));
    nova->vertice = '0';
    nova->peso = 0;
    nova->prox = NULL;
    return nova;
} 

//protótipos
char grafoSimples(char grafo[LINHA][COLUNA], int l, int c);
char grafoCompleto(char grafo[LINHA][COLUNA], int l, int c);
char grafoRegular(char grafo[LINHA][COLUNA], int l, int c);
char grafoOrientado(char grafo[LINHA][COLUNA], int l, int c);
char grafoNaoOrientado(char grafo[LINHA][COLUNA], int l, int c);

//funções
char grafoCompleto(char grafo[LINHA][COLUNA], int l, int c){
    for(int i=0; i<l; i++){
        for(int j=0; j<c; j++){
            if(i==j){
                if(grafo[i][j]==1)
                    return 0;
            }
            else{
                if(grafo[i][j]==0)
                    return 0;
            }
        }
    }
    return 1;
}

char grafoSimples(char grafo[LINHA][COLUNA], int l, int c){
    for(int i=0; i<l; i++){
        if(grafo[i][i]==1)
            return 0;
    }
    return 1;
}

char grafoRegular(char grafo[LINHA][COLUNA], int l, int c){
    int soma=0, somaLinha, linhaAtual;
    for(int i=0; i<c; i++){
        if(grafo[0][i] == 1)
            soma++;
    }
    linhaAtual = 1;
    somaLinha = 0;
    for(int i=1; i<l; i++){
        for(int j=0; j<c; j++){
            if(linhaAtual != i){
                linhaAtual = i;
                if(somaLinha != soma)
                    return 0;
                somaLinha = 0;
            }
            if(grafo[i][j]==1)
                somaLinha++;
        }
    }
    return 1;
}

//menus
int menuPrincipal(){
    int opc;
    printf("*** MENU PRINCIPAL ***\n");
    printf("[1] Matriz Adjacencia\n");
    printf("[2] Matiz de Incidencia\n");
    printf("[10] SAIR\nOpcao: ");
    scanf("%d", &opc);
    return opc;
}

int menuAdjacencia(){
    int opc;
    printf("*** MENU MATRIZ DE ADJACENCIA ***\n");
    printf("[1] Converter Matriz para Lista\n");
    printf("[2] Verificar tipo de grafo");
    printf("[10] SAIR\nOpcao: ");
    scanf("%d", &opc);
    return opc;
}

//converter matriz de adjacencia para lista de adjacencia
ListaAdjacencia** converterMatrizToLista(FILE * ptrArquivo){
    ListaAdjacencia * lista = novaCaixaLista();
    char charAtual, num[10];
    int quantVertices, indiceVertices, numTL;

    //pegar a quantidade de vertices na primeira linha
    quantVertices = 0;
    fseek(ptrArquivo,0,0);
    charAtual = getc(ptrArquivo);
    while(charAtual != '\n'){
        if(charAtual!=','){
            quantVertices++;
        }
        charAtual = getc(ptrArquivo);
    }
    printf("Quantidade de vertices do grafo: %d\n", quantVertices);

    //criar o vetor contendo os vértices
    ListaAdjacencia * vertices[quantVertices];
    fseek(ptrArquivo,0,0);
    charAtual = getc(ptrArquivo);
    indiceVertices = 0;
    while(charAtual != '\n'){
        if(charAtual!=','){
            vertices[indiceVertices] = (ListaAdjacencia*)malloc(sizeof(ListaAdjacencia));
            vertices[indiceVertices]->vertice = charAtual;
            indiceVertices++;
        }
        charAtual = getc(ptrArquivo);
    }
    printf("Indice vertices: %d\n", indiceVertices);

    //continuar a leitura do grafo para a criação da lista
    fseek(ptrArquivo,0,0);
    charAtual = getc(ptrArquivo);
    indiceVertices = 0;
    numTL = 0;
    memset(num,sizeof(num),'\0'); //inicializar a minha string com todas as posições contendo o final de string
    while(!feof(ptrArquivo)){
        //em cada linha pegar as ligações do no com os outros
        while(!feof(ptrArquivo) && charAtual != ',' && charAtual != '\n'){
            num[numTL] = charAtual; //vou compondo o meu número

            charAtual = getc(ptrArquivo);
        }
        //se verdade completei um número
        if(charAtual == ','){
            
        }
        charAtual = getc(ptrArquivo);
    }

    return vertices; //temporario
}

int main(){
    //o grafo será representado pela matriz de adjacência
    int grafo[LINHA][COLUNA] = {}, TLLin, TLCol;

    //teste da leitura do arquivo
    char charAtual;
    FILE * ptr = fopen("entrada.txt","r");
    charAtual = getc(ptr);
    while(!feof(ptr)){
        printf("%c",charAtual);
        charAtual = getc(ptr);
    }

    //exibir apenas a primeira linha
    printf("\n\nPrimeira linha apenas:\n");
    fseek(ptr,0,0);
    charAtual = getc(ptr);
    while(charAtual!='\n'){
        printf("%c", charAtual);
        charAtual = getc(ptr);
    }

    converterMatrizToLista(ptr);

    return 0;
}
