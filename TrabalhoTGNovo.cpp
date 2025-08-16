#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>

#define L 50
#define C 50

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
void verificarOrientadoAdjacencia(int m[L][C], int l, int c,int *grafo)
{
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (m[i][j] != m[j][i]) // orientado (nao simetrico)
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
			cont++;
			
		}
		if (cont != v - 1) 
			*completo = 1;
	}
	
}
void exibirVerticesAdjacencia(char vertices[C])
{
	for(int i = 0; i < strlen(vertices); i++)
		printf("%c ", vertices[i]);
	
}
void exibirMatrizAdjacencia(int m[L][C], int qtdeLinhas, int qtdeColunas)
{
	for (int i = 0; i < qtdeLinhas; i++)
	{
		for (int j = 0; j < qtdeColunas; j++)
		{
			printf ("%d ", m[i][j]);
		}
		printf("\n");
	}
	
}
char menu (void)
{
	printf("\n[A] - Matriz de Adjacencia\n");
	printf("[B] - Matriz de Incidencia\n");
	printf ("[ESC] - Sair\n");
	
	return toupper(getch());
}
char submenu(void)
{
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
		
		int grafo = 0, simples = 0, regular = 0, completo;
		int m[L][C], qtdeVertices = 0, qtdeLinhas = 0, qtdeColunas = 0;
		char vertices[C];

		clrscr();
		op = menu();
		switch(op)
		{
			case 'A':
				lerTxTMatrizAdjacencia(m, &qtdeVertices, &qtdeLinhas, &qtdeColunas, vertices);
				do
				{
					clrscr();
					exibirVerticesAdjacencia(vertices);
					printf("\n");
					exibirMatrizAdjacencia(m, qtdeLinhas,qtdeColunas);
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
							
						getch();
						break;
						case 'B':
						verificarRegularAdjacencia(m, qtdeLinhas, qtdeColunas, &regular);
						if (regular == 1)
							printf ("\nNao Regular\n");
						else
							printf ("\nRegular\n");
						getch();	
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
						
					
						getch();
						break;
						
					}
				}while(op2 != 27);
			break;
			case 'B':
				do
				{	clrscr();
					op2 = submenu();
					switch(op2)
					{
						case 'A':
						printf("grafo orientado incidencia\n");
						getch();
						break;
					}
				}while(op2 != 27);
			break;
		
		}
		
	}while(op != 27);
	
	
}
int main(void)
{
	executar();
	return 0;
}
