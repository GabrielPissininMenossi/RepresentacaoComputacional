#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>

// structs
typedef struct listaAdjacencia
{
    char vertice;
    int peso;
    struct listaAdjacencia *head, *tail;
} ListaAdjacencia;

// pequeno tad da lista adjacencia
ListaAdjacencia *novaCaixaVazia(void)
{
    ListaAdjacencia *nova = (ListaAdjacencia *)malloc(sizeof(ListaAdjacencia));
    //memset(nova->vertice, '\0', sizeof(nova->vertice));
    nova->vertice = '0';
    nova->peso = 0;
    nova->head = nova->tail = NULL;
    return nova;
}

ListaAdjacencia *novaCaixaLista(char vertice)
{
    ListaAdjacencia *nova = (ListaAdjacencia *)malloc(sizeof(ListaAdjacencia));
    //memset(nova->vertice, '\0', sizeof(nova->vertice));
    nova->vertice = vertice;
    nova->peso = 0;
    nova->head = nova->tail = NULL;
    return nova;
}

//metodos de verificacao
//metodo para inserir o primeiro
void inserirLista(ListaAdjacencia**lista, char vertice){
	*lista = novaCaixaLista(vertice);
}

void inserirListaPeso(ListaAdjacencia**lista, char origem, char vertice, int peso){
	ListaAdjacencia * nova, *aux, *ant;

	//se lista vazia
	if(*lista == NULL){
		inserirLista(&(*lista),origem);
	}
	else{
		//procurar o vertice origem
		aux = ant = *lista;
		while(aux != NULL && origem != aux->vertice){
			ant = aux;
			aux = aux->head;
		}
		//se nao existe eu crio o vertice origem
		if(aux == NULL){ //entao nao existe esse vertice origem
			ant->head = novaCaixaLista(origem);
		}
		else{
			//fazer a busca na horizontal, buscar o vertice de destino
			ant = aux;
			aux = aux->tail;
			while(aux != NULL && vertice != aux->vertice){
				ant = aux;
				aux = aux->tail;
			}
			//nao existe o vertice para o destino
			if(aux == NULL){
				nova = novaCaixaLista(vertice);
				nova->peso = peso;
				ant->tail = nova;
			}
		}
	}
}

void lerTxtListaAdjacencia(ListaAdjacencia **lista){
	FILE * ptr = fopen("entradaLA.txt", "r");
	ListaAdjacencia * caixa;
	char atual, peso[10], vertice, verLinha;
	
	//inicializar o peso
	memset(peso,'\0',sizeof(peso));

	while(!feof(ptr)){
		atual = getc(ptr); //o vertice da linha
		verLinha = atual; //pegar o vertice do inicio da linha
		inserirListaPeso(&(*lista),verLinha,' ',0);
		atual = getc(ptr); //pegar o espaco em branco
		atual = getc(ptr); //pegar o proximo vertice para comecar a tratar

		//ate o final da linha
		while(!feof(ptr) && atual!='\n'){
			if(atual > 47 && atual < 58){
				//coletar o peso
				peso[strlen(peso)] = atual;
			}
			else{
				if(atual == ' '){//já tenho o peso
					inserirListaPeso(&(*lista),verLinha,vertice,atoi(peso));
					memset(peso,'\0',sizeof(peso));
				}
				else{
					if(atual != ','){ //quer dizer que eu agora possou o meu vertice
						vertice = atual;
					}
				}
			}
			atual = getc(ptr);
		}
		inserirListaPeso(&(*lista),verLinha,vertice,atoi(peso));
		memset(peso,'\0',sizeof(peso));
	}
}

void exibirListaAdjacencia(ListaAdjacencia * lista){
	ListaAdjacencia *auxVert, *auxHori;
	auxVert = lista;
	//descer verticalmente
	while(auxVert != NULL){
		printf("Vertice: %c -> ",auxVert->vertice);
		auxHori = auxVert->tail;
		while(auxHori != NULL){
			if(auxHori->tail == NULL){
				printf("%c,%d",auxHori->vertice,auxHori->peso);	
			}
			else{
				printf("%c,%d || ",auxHori->vertice,auxHori->peso);
			}
			auxHori = auxHori->tail;
		}
		printf("\n");
		auxVert = auxVert->head;
	}
}

void verificaSimplesListaAdjacencia(ListaAdjacencia * lista, int *simples){
	ListaAdjacencia *auxHori;
	*simples = 0;
	
	while(lista != NULL && *simples == 0){ //andar verticalmente
		//vertice = lista->vertice; //primeiro vertice da minha lista
		auxHori = lista->tail;
		while(*simples == 0 && auxHori != NULL){
			if(auxHori->vertice == lista->vertice)
				*simples = 1; //o grafo nao eh simples	
			auxHori = auxHori->tail;
		}
		lista = lista->head;
	}
}

void verificarRegularListaAdjacencia(ListaAdjacencia * lista, int *regular){
	ListaAdjacencia * auxHori;
	*regular = 0;
	int somaPri = 0, soma;
	
	//realizar a soma da primeira fileira
	auxHori = lista->tail;
	while(auxHori != NULL){
		auxHori = auxHori->tail;
		somaPri++;
	}
	
	//agora realizar a soma das fileiras e comparar com a soma inicial
	lista = lista->head;
	while(lista != NULL && *regular==0){ //andar verticalmente
		auxHori = lista->tail;
		soma = 0;
		while(auxHori != NULL){ //andar na horizontal
			auxHori = auxHori->tail;
			soma++;
		}
		if(soma != somaPri)
			*regular = 1;
		lista = lista->head;
	}
}

int verificarCompletoListaAdjacencia(ListaAdjacencia * lista, int *completo){
	ListaAdjacencia *auxHori, *auxVert = lista;
	int n = 0, k, cont;
	
	//andar na horizontal para contar os meus vertices
	while(auxVert != NULL){
		n++;
		auxVert = auxVert->head;
	}
	
	k = n*(n-1);
	
	//contar todas as arestas
	auxVert = lista;
	cont=0;
	while(auxVert != NULL){ //andar na vertical
		auxHori = auxVert->tail;
		while(auxHori != NULL){ //andar na horizontal
			cont++;
			auxHori = auxHori->tail;
		}
		auxVert = auxVert->head;
	}
	if(cont == k)
		*completo = 0;
	else
		*completo = 1;
		
	return n; //quantidade de arestas
}

char existeOrigemDestinoLista(ListaAdjacencia * lista, char origem, char destino){
	ListaAdjacencia *auxHori, *auxVert = lista;
	
	//achar o vertice de origem
	while(auxVert != NULL && auxVert->vertice != origem)
		auxVert = auxVert->head;
	if(auxVert == NULL) //nao existe essa vertice, nao existe essa aresta
		return 0;
	
	auxHori = auxVert->tail;
	while(auxHori != NULL && auxHori->vertice != destino)
		auxHori = auxHori->tail;
	if(auxHori == NULL) //nao existe essa origem
		return 0;
		
	//printf("Retornei! Origem: %c -> Destino: %c\n",origem, destino);
	return 1; //nao entrou em nenhum return falso
}


void verificarOrientadoListaAdjacencia(ListaAdjacencia *lista, int *grafo){
	ListaAdjacencia *auxHori, *auxVert = lista;
	
	*grafo = 0;
	while(auxVert != NULL && *grafo == 0){ //andar na vertical
		auxHori = auxVert->tail;
		while(auxHori != NULL && *grafo == 0){
			//printf("oi\n");
			if(existeOrigemDestinoLista(lista, auxHori->vertice, auxVert->vertice) == 0){ //nao existe
				*grafo = 1;
			}
			auxHori = auxHori->tail;
		}
		auxVert = auxVert->head;
	}
}

//outros metodos
void continuar(){
	printf("\n\nPressione qualquer tecla para continuar...");
	getch();
}

char submenu(void)
{
	clrscr();
	printf("\n[A] - Simples\n");
	printf("[B] - Regular\n");
	printf("[C] - Completo\n");
	printf("[D] - EXIBIR LISTA\n");
	printf ("[ESC] - Voltar\n");
	
	return toupper(getch());
}

int main(){
	ListaAdjacencia * lista = NULL;
	char op, op2;
	int grafo, simples, regular, completo;
	
	//lista de adjacencia
	lerTxtListaAdjacencia(&lista);
	exibirListaAdjacencia(lista);
	continuar();
	
	//menu
	do
	{
		clrscr();
		verificarOrientadoListaAdjacencia(lista,&grafo);
		if (grafo == 1)
			printf ("\nGrafo Orientado (Digrafo)\n");
		else
			printf ("\nGrafo Nao Orientado (Grafo)\n");
		continuar();
		op2 = submenu();
		
		switch(op2)
		{
		
			//simples
			case 'A':{
				verificaSimplesListaAdjacencia(lista,&simples); //colocar os parametros
				if (simples == 1)
					printf("\nNao eh simples");
				else
					printf("\nEh simples");
				continuar();
				break;
			}
			
			//regular
			case 'B':{
				verificarRegularListaAdjacencia(lista,&regular); //colocar os parametros
				if (regular == 1)
					printf ("\nNao Regular\n");
				else
					printf ("\nRegular\n");
				continuar();
				break;
			}
			
			//completo
			case 'C':{
				//pre requisitos para a verificacao se eh completo ou n
				verificaSimplesListaAdjacencia(lista,&simples);
				verificarRegularListaAdjacencia(lista,&regular);
				
				if (regular == 0 && simples == 0) // tem q ser regular e simples, para ser completo
				{
					verificarCompletoListaAdjacencia(lista,&grafo);//colocar os parametros
					if (completo == 1) // nao eh completo
						printf ("\nNao eh completo\n");
					else
						printf ("\nCompleto\n");
				}
				else
					printf ("\nNao eh completo\n");
				continuar();
				break;
			}
			
			//exibicao
			case 'D':{
				exibirListaAdjacencia(lista);
				continuar();
				break;
			}
			
			default:{
				clrscr();
				continuar();
				break;
			}
		}
	} while(op2 != 27);
	
	return 0;
}
