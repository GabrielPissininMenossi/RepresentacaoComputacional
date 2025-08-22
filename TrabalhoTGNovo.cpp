#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>

#define L 50
#define C 50

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

void lerTxTMatrizAdjacencia(int m[L][C], int *qtdeVertices, int *qtdeLinhas, int *qtdeColunas, char vertices[C])
{

	int j = 0, num, linhas = 0, colunas = 0;
	char linha[50], aux[50];
	FILE * Ptr = fopen("entradaMA.txt", "r");
	rewind(Ptr); // joga o ponteiro para o inicio
	fgets(linha, sizeof(linha), Ptr); // le a primeira linha, contendo todos meus vertices
	for (int i = 0; i < strlen(linha);i++)
	{
		if (linha[i] != ' ' && linha[i] != '\n')
		{
			vertices[j] = linha[i];
			*qtdeVertices = *qtdeVertices + 1;
			j++;
		}
		//printf("%c", linha[i]);
	}
	// ler a matriz
	
	while(fgets(linha, sizeof(linha), Ptr))
	{
		j = 0;
		colunas = 0;
		for(int i = 0; i < strlen(linha); i++)
		{
			if(linha[i] != ' ' && linha[i] != '\n')
			{
				aux[j] = linha[i];
				j++;
			}
			else
			{
				aux[j] = '\0';
				num = atoi(aux);
				m[linhas][colunas] = num;
				j = 0;
				colunas++;
			}
		
			
		}
		if (j > 0)
		{
			
			aux[j] = '\0';
			num = atoi(aux);
			m[linhas][colunas] = num;

		}
		if (colunas > *qtdeColunas)
			*qtdeColunas = colunas;
		linhas++;
	}
	*qtdeLinhas = linhas;
	
	fclose(Ptr);
}
void lerTxTMatrizIncidencia(int m[L][C], int *qtdeVertices, int *qtdeArestas, int *qtdeLinhas, int *qtdeColunas, char vertices[C], char arestas[C])
{

	int j = 0, num, linhas = 0, colunas = 0;
	char linha[50], aux[50];
	FILE * Ptr = fopen("entradaMI.txt", "r");
	rewind(Ptr); // joga o ponteiro para o inicio
	fgets(linha, sizeof(linha), Ptr); // le a primeira linha, contendo todos meus vertices
	for (int i = 0; i < strlen(linha);i++)
	{
		if (linha[i] != ' ' && linha[i] != '\n')
		{
			vertices[j] = linha[i];
			*qtdeVertices = *qtdeVertices + 1;
			j++;
		}
		//printf("%c", linha[i]);
	}
	// ler as arestas
	j = 0;
	fgets(linha, sizeof(linha), Ptr);
	for(int i = 0; i < strlen(linha);i++)
	{
		
		if (linha[i] != ' ' && linha[i] != '\0')
		{
			aux[j] = linha[i];
			j++;
		}
		else
		{
			aux[j] = ' ';
			j++;
			aux[j] = '\0';
			strcat(arestas, aux);
			*qtdeArestas = *qtdeArestas + 1;
			j = 0;
		}
		//printf("%c", linha[i]);
	}
	if (j > 0)
	{
		
		aux[j] = '\0';
		strcat(arestas, aux);
		*qtdeArestas = *qtdeArestas + 1;

	}
	while(fgets(linha, sizeof(linha), Ptr))
	{
		j = 0;
		colunas = 0;
		for(int i = 0; i < strlen(linha); i++)
		{
			if(linha[i] != ' ' && linha[i] != '\n')
			{
				aux[j] = linha[i];
				j++;
			}
			else
			{
				aux[j] = '\0';
				num = atoi(aux);
				m[linhas][colunas] = num;
				j = 0;
				colunas++;
			}
		
			
		}
		if (j > 0)
		{
			
			aux[j] = '\0';
			num = atoi(aux);
			m[linhas][colunas] = num;

		}
		if (colunas > *qtdeColunas)
			*qtdeColunas = colunas;
		linhas++;
	}
	*qtdeLinhas = linhas;
	fclose(Ptr);
}

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
				if(atual == ' '){//j� tenho o peso
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
		printf("Vertice: %c | ",auxVert->vertice);
		auxHori = auxVert->tail;
		while(auxHori != NULL){
			printf("%c,%d || ",auxHori->vertice,auxHori->peso);
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
	ListaAdjacencia *auxHori;
	
	//achar o vertice de origem
	while(lista != NULL && lista->vertice != origem)
		lista = lista->head;
	if(lista == NULL) //nao existe essa vertice, nao existe essa aresta
		return 0;
	else{
		auxHori = lista->tail;
		while(auxHori != NULL && auxHori->vertice != destino)
			auxHori = auxHori->tail;
		if(auxHori == NULL) //nao existe essa origem
			return 0;
	}
	return 1; //nao entrou em nenhum return falso
}

void verificarOrientadoListaAdjacencia(ListaAdjacencia *lista, int *grafo){
	ListaAdjacencia *auxHori;
	
	*grafo = 0;
	while(lista != NULL && *grafo == 0){ //andar na vertical
		auxHori = lista->tail;
		while(auxHori != NULL && !*grafo){
			if(existeOrigemDestinoLista(lista,auxHori->vertice,lista->vertice) == 0){ //nao existe
				*grafo = 1;
			}
			auxHori = auxHori->tail;
		}
		lista = lista->head;
	}
}

void verificarOrientadoAdjacencia(int m[L][C], int l, int c,int *grafo)
{
	
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if (m[i][j] != m[j][i]) // orientado (nao simetrico)
				*grafo = 1;
		
		}
		
	}
	
}
void verificarOrientadoIncidencia(int m[L][C], int l, int c, int *grafo)
{

	for (int i = 0; i < l; i++) // vertices
	{
		for(int j = 0; j < c; j++) // arestas
		{
			if (m[i][j] < 0) // digrafo
				*grafo = 1;
			
		}
	}
	
}
void verificaSimplesAdjacencia(int m[L][C],int l, int c, int *simples)
{
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if (j == i && m[i][j] != 0)			
				*simples = 1;
		}
	}
	
}
void verificaSimplesIncidenciaGrafo(int m[L][C], int l, int c, int *multi, int *laco)
{
	int cont, linha1, linha2;
	for(int j = 0; j < c; j++)
	{
		cont = 0;
		for(int i = 0; i < l; i++)
		{
			if(m[i][j] != 0) 
			{
				cont++;
				if (cont == 1)
					linha1 = i;
				if (cont == 2)
					linha2 = i;
			}
		
		}
		if (cont == 2)
		{
			for(int k=j+1; k < c; k++)
			{
				if (m[linha1][k] != 0 && m[linha2][k] != 0) // multiplas arestas
					*multi = 1;
						
			}
			
		}
	}
	for (int j = 0; j < c; j++)
	{
		cont = 0;
		for (int i = 0; i < l; i++)
		{
			
			if(m[i][j] != 0) 
				cont++;
		}
		if (cont == 1)
			*laco = 1;
	}
}
void verificarSimplesIncidenciaDigrafo(int m[L][C], int l, int c, int *multi)
{
	int par[2], cont, linha1, linha2; 
	for (int j = 0; j < c; j++) // pra cada coluna, preciso ver se ha o mesmo par(origem, destino)
	{
		cont = 0;
		for(int i = 0; i < l; i++)
		{
			if (m[i][j] != 0)
			{
				cont++;
				if (cont == 1)
				{
					par[0] = m[i][j];
					linha1 = i;
				}
				else
				if (cont == 2)
				{
					par[1] = m[i][j];
					linha2 = i;
				}
			}
		}
		if (cont == 2)
		{
			for(int k = j+1; k < c; k++)
			{
				
				if((m[linha1][k] < 0 && par[0] < 0 || m[linha1][k] > 0 && par[0] > 0)  && (m[linha2][k] > 0 && par[1] > 0 || m[linha2][k] < 0 && par[1] < 0))
					*multi = 1;
				
			}
			 	
		}
		
		
	}
		
}
void verificaRegularIncidenciaGrafo(int m[L][C], int l, int c, int *regular, int *grau)
{
	int aux = 0;
	for (int i = 0; i < l; i++)
	{
		*grau = 0;
		for (int j = 0; j < c; j++)
		{
			if (m[i][j] != 0)
				*grau = *grau + 1;
				
		}
		if (aux == 0) // primeira linha
			aux = *grau;
		else
		if (*grau != aux)
			*regular = 1; // nao é regular
	}
	
	
}
void verificarRegularIncidenciaDigrafo(int m[L][C], int l, int c, int *regular, int *regularEmissao, int *regularRecepcao,  int *grau,char vertices[C])
{
	int contE, contR, total, grauE = -1, grauR = -1, grauTotal = -1;
	for (int i = 0; i < l; i++)
	{
		contE = 0;
		contR = 0;
		total = 0;
		printf ("\nVertice: %c\n", vertices[i]);
		for(int j = 0; j < c; j++)
		{
			if (m[i][j] > 0) // recpeção
				contR++;
			else
			if(m[i][j] < 0)
				contE++;	
			
		}
		if (grauE == -1) // definir o grau
			grauE = contE;
		else
		if (contE != grauE) // nao regular por emissao
			*regularEmissao = 1;
		
		if (grauR == -1)
			grauR = contR;
		else
		if (contR != grauR)
			*regularRecepcao = 1;
			
		total = contE + contR;
		if (grauTotal == -1)
			grauTotal = total;
		else
		if(total != grauTotal)
			*regular = 1;
		
		printf ("Grau de Emissao: %d\n", contE);
		printf ("Grau de Recepcao: %d\n", contR);
		printf ("Grau Total: %d\n", total);
		if (contE == 0 && contR != 0)
			printf ("Sumidouro");
		else
		if(contR == 0 && contE != 0)
			printf ("Fonte");
		*grau = grauTotal;
	}	
	
}
void verificarRegularAdjacencia(int m[L][C], int l, int c,int *regular)
{
	int cont, aux = 0;
	for (int i = 0; i < l; i++)
	{
		cont = 0;
		for (int j = 0; j < c; j++)
		{
			if (m[i][j] != 0)
				cont++;		
		}
		if (aux == 0) // primeira linha
		{
			aux = cont;
		}
		else
		{
			if (cont != aux) // nem todas as vertices sao regulares
				*regular = 1;
			
		}
	}
	
}
void verificarCompletoAdjacencia(int m[L][C], int l, int c, int *completo, int v)
{
	int cont;
	for (int i = 0; i < l; i++)
	{
		cont = 0;
		for (int j = 0; j < c; j++)
		{
			if (m[i][j] != 0)
				cont++;
		}
		if (cont != v - 1) 
			*completo = 1;
	}
	
}
void verificaCompletoIncidenciaGrafo(int m[L][C], int l, int c, int qtdeArestas, int qtdeVertices, int *completo, int *n)
{
	//printf ("Qtde Arestas: %d\n", qtdeArestas);
	//printf ("Qtde Vertices: %d\n", qtdeVertices);
	*n = qtdeVertices*(qtdeVertices-1)/2;
	if (qtdeArestas != *n)
		*completo = 1; // nao é completo
	else
	{
		int grau;
		for (int i = 0; i < l; i++)
		{
			grau = 0;
			for (int j = 0; j < c; j++)
			{
				if(m[i][j] != 0)
					grau++;
				
			}
			if (grau != qtdeVertices - 1)
				*completo = 1; // nao é completo
		}
		
	}

}
void verificarCompletoIncidenciaDigrafo(int m[L][C], int l, int c, int qtdeArestas,int qtdeVertices,int *completo, int *n)
{
	*n = qtdeVertices * (qtdeVertices - 1); // qtde esperada de arestas
	if (qtdeArestas != *n)
		*completo = 1;
		
}
void exibirMatrizAdjacenciaComVertices(int m[L][C], char vertices[C], int qtdeLinhas, int qtdeColunas)
{
    printf("MA "); 
    for (int j = 0; j < qtdeColunas; j++)
	{
        printf("%c ", vertices[j]);
    }
    printf("\n");
    for (int i = 0; i < qtdeLinhas; i++)
	{
        printf("%c ", vertices[i]);
        for (int j = 0; j < qtdeColunas; j++)
		{
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}
void exibirMatrizIncidenciaComVertices(int m[L][C], char vertices[C], char arestas[C], int qtdeLinhas, int qtdeColunas, int qtdeArestas)
{
    char aux[50];
    int pos = 0;

    printf("MI  ");

    for (int k = 0; k < qtdeArestas; k++)
    {
        int j = 0;
        while (arestas[pos] != ' ' && arestas[pos] != '\0')
		{
            aux[j++] = arestas[pos++];
        }
        aux[j] = '\0';
        pos++; 

        printf("%s ", aux);
    }
    printf("\n");

    for (int i = 0; i < qtdeLinhas; i++)
    {
        printf("%c  ", vertices[i]);
        for (int j = 0; j < qtdeColunas; j++)
        {
            printf("%d  ", m[i][j]);
        }
        printf("\n");
    }
}

void continuar(){
	printf("\n\nPressione qualquer tecla para continuar...");
	getch();
}

char menu (void)
{
	clrscr();
	printf("\n[A] - Matriz de Adjacencia\n");
	printf("[B] - Matriz de Incidencia\n");
	printf("[C] - Lista de Adjacencia\n");
	printf ("[ESC] - Sair\n");
	
	return toupper(getch());
}
char submenu(void)
{
	clrscr();
	printf("\n[A] - Simples\n");
	printf("[B] - Regular\n");
	printf("[C] - Completo\n");
	printf ("[ESC] - Voltar\n");
	
	return toupper(getch());
}
void executar(void)
{

	char op, op2;
	do
	{	
		
		int grafo = 0, simples = 0, regular = 0, regularEmissao = 0, regularRecepcao = 0, completo = 0, laco = 0, multi = 0, grau = 0, n;
		int m[L][C], qtdeVertices = 0, qtdeLinhas = 0, qtdeColunas = 0, qtdeArestas = 0;
		char vertices[C], arestas[C];
		ListaAdjacencia * lista = NULL;
		arestas[0] = '\0';
		//clrscr();
		
		op = menu();
		switch(op)
		{
			case 'A':{
				lerTxTMatrizAdjacencia(m, &qtdeVertices, &qtdeLinhas, &qtdeColunas, vertices);
				do
				{
					//clrscr();
					exibirMatrizAdjacenciaComVertices(m, vertices,qtdeLinhas,qtdeColunas);
					verificarOrientadoAdjacencia(m, qtdeLinhas, qtdeColunas ,&grafo);
					if (grafo == 1)
						printf ("\nGrafo Orientado (Digrafo)\n");
					else
						printf ("\nGrafo Nao Orientado (Grafo)\n");
					op2 = submenu();
					switch(op2)
					{
					
						case 'A':
						verificaSimplesAdjacencia(m, qtdeLinhas, qtdeColunas,&simples);
						if (simples == 1)
							printf("\nNao eh simples");
						else
							printf("\nEh simples");
							
						getchar();
						break;
						case 'B':
						verificarRegularAdjacencia(m, qtdeLinhas, qtdeColunas, &regular);
						if (regular == 1)
							printf ("\nNao Regular\n");
						else
							printf ("\nRegular\n");
						getchar();	
						break;
						case 'C':
						if (regular == 0 && simples == 0) // tem q ser regular e simples, para ser completo
						{
							verificarCompletoAdjacencia(m, qtdeLinhas, qtdeColunas, &completo, qtdeVertices);
							if (completo == 1) // nao eh completo
								printf ("\nNao eh completo\n");
							else
								printf ("\nCompleto\n");
						}
						else
							printf ("\nNao eh completo\n");
						
					
						getchar();
						break;
						
					}
				}while(op2 != 27);
				break;
			}
			case 'B':{
				lerTxTMatrizIncidencia(m, &qtdeVertices, &qtdeArestas, &qtdeLinhas, &qtdeColunas, vertices, arestas);
				do
				{	
					//clrscr();
					exibirMatrizIncidenciaComVertices(m, vertices,arestas,qtdeLinhas,qtdeColunas, qtdeArestas);
					verificarOrientadoIncidencia(m, qtdeLinhas, qtdeColunas ,&grafo);
					if (grafo == 1)
						printf ("\nGrafo Orientado (Digrafo)\n");
					else
						printf ("\nGrafo Nao Orientado (Grafo)\n");
					op2 = submenu();
					switch(op2)
					{
						case 'A':
						if (grafo == 1) // digrafo
							verificarSimplesIncidenciaDigrafo(m, qtdeLinhas, qtdeColunas, &multi);
						else
							verificaSimplesIncidenciaGrafo(m, qtdeLinhas, qtdeColunas, &multi, &laco);
						if (multi == 1 && laco == 1)
							printf("\nNao eh simples\n\nHa multiplas arestas e laco");
						else
						if (multi == 1)
							printf ("\nNao eh simples\n\nHa multiplas arestas");
						else
						if (laco == 1)
							printf ("\nNao eh simples\n\nHa laco");
						else
							printf("\nEh simples");
						getchar();
						break;
						case 'B':
						if(grafo == 1)
							verificarRegularIncidenciaDigrafo(m, qtdeLinhas, qtdeColunas, &regular, &regularEmissao, &regularRecepcao, &grau,vertices);
						else
							verificaRegularIncidenciaGrafo(m, qtdeLinhas, qtdeColunas, &regular, &grau);
						if (regular == 1) // nao é regular
							printf ("\nNao Regular\n");
						else
						{
							printf ("\n\nRegular\n");
							printf ("Grau: %d\n", grau);
						}
						getchar();
						break;
						case 'C':
						if (regular == 0 && simples == 0) // tem q ser regular e simples, para ser completo
						{
							if (grafo == 1) // digrafo
								verificarCompletoIncidenciaDigrafo(m, qtdeLinhas, qtdeColunas, qtdeArestas, qtdeVertices, &completo, &n);
							else
								verificaCompletoIncidenciaGrafo(m, qtdeLinhas, qtdeColunas, qtdeArestas, qtdeVertices,&completo, &n);
							if (completo == 1)
							{
								printf ("\nNao eh completo\n");
								if (n != qtdeArestas)
									printf ("\nNao houve o numero esperado de arestas\nTotal: %d\nEsperado: %d", qtdeArestas, n);
								else
									printf ("\nNem todas as vertices possuem o grau de n-1");
							}
							else
								printf ("\nCompleto");
						}
						else
							printf ("\nNao eh completo\n");
						getchar();
						break;
					}
				}while(op2 != 27);
				break;
			}
			case 'C':{
				//lista de adjacencia
				lerTxtListaAdjacencia(&lista);
				exibirListaAdjacencia(lista);
				continuar();
				
				//menu
				do
				{
					clrscr();
					//exibirMatrizAdjacenciaComVertices(m, vertices,qtdeLinhas,qtdeColunas);
					verificarOrientadoListaAdjacencia(lista,&grafo); //colocar os parametros
					if (grafo == 1)
						printf ("\nGrafo Orientado (Digrafo)\n");
					else
						printf ("\nGrafo Nao Orientado (Grafo)\n");
					continuar();
					op2 = submenu();
					switch(op2)
					{
					
						//feito, NAO TESTADO
						case 'A':{
							verificaSimplesListaAdjacencia(lista,&simples); //colocar os parametros
							if (simples == 1)
								printf("\nNao eh simples");
							else
								printf("\nEh simples");
							continuar();
							break;
						}
						
						//feito, NAO TESTADO
						case 'B':{
							verificarRegularListaAdjacencia(lista,&regular); //colocar os parametros
							if (regular == 1)
								printf ("\nNao Regular\n");
							else
								printf ("\nRegular\n");
							continuar();
							break;
						}
						
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
						
					}
				} while(op2 != 27);

				break;
			}
			default:{
				printf("Opcao Invalida, digite ESC para SAIR!!\n");
			}
		}
		
	}while(op != 27);

}
int main(void)
{
	executar();
	return 0;
}
