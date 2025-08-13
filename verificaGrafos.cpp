#include<stdio.h>
#include<string.h>
#include<math.h>

#define LINHA 100
#define COLUNA 100

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
    printf("[3] SAIR\n");
    scanf("%d", &opc);
    return opc;
}

int manuAdjacencia(){
    return 0;//temporario
}

int main(){
    //o grafo será representado pela matriz de adjacência
    int grafo[LINHA][COLUNA] = {}, TLLin, TLCol;
    printf("Ola mundo!!\n");

    return 0;
}
