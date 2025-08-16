#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define L 4
#define C 4

// funcoes
void verificarOrientadoAdjacencia(int m[L][C], int *grafo)
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
void verificaSimplesAdjacencia(int m[L][C], int *simples)
{
	*simples = 0;
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (j == i && m[i][j] != 0)
				*simples = 1;
		}
	}
}
void verificarRegularAdjacencia(int m[L][C], int *regular)
{
	int cont, aux = 0;
	for (int i = 0; i < L; i++)
	{
		cont = 0;
		for (int j = 0; j < C; j++)
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
void verificarCompletoAdjacencia(int m[L][C], int *completo, int v)
{
	int cont;
	for (int i = 0; i < L; i++)
	{
		cont = 0;
		for (int j = 0; j < C; j++)
		{
			cont++;
		}
		if (cont != v - 1)
			*completo = 1;
	}
}
void exibirMatriz(int m[L][C])
{
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < C; j++)
		{
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
}
char menu(void)
{
	printf("\n[A] - Matriz de Adjacencia\n");
	printf("[B] - Matriz de Incidencia\n");
	printf("[ESC] - Sair\n");

	return toupper(getchar());
}
char submenu(void)
{
	printf("\n[A] - Simples\n");
	printf("[B] - Regular\n");
	printf("[C] - Completo\n");
	printf("[ESC] - Voltar\n");

	return toupper(getchar());
}
void executar(void)
{
	int m[L][C];
	m[0][0] = 0;
	m[0][1] = 1;
	m[0][2] = 1;
	m[0][3] = 0;

	m[1][0] = 0;
	m[1][1] = 0;
	m[1][2] = 0;
	m[1][3] = 1;

	m[2][0] = 1;
	m[2][1] = 0;
	m[2][2] = 0;
	m[2][3] = 1;

	m[3][0] = 0;
	m[3][1] = 1;
	m[3][2] = 1;
	m[3][3] = 0;
	char op, op2;
	do
	{
		int grafo = 0, simples = 0, regular = 0, completo;
		// clrscr();
		exibirMatriz(m);
		verificarOrientadoAdjacencia(m, &grafo);
		if (grafo == 1)
			printf("\nGrafo Orientado (Digrafo)\n");
		else
			printf("\nGrafo Nao Orientado (Grafo)\n");
		op = menu();
		switch (op)
		{
		case 'A':
			do
			{
				// clrscr();
				exibirMatriz(m);
				verificarOrientadoAdjacencia(m, &grafo);
				if (grafo == 1)
					printf("\nGrafo Orientado (Digrafo)\n");
				else
					printf("\nGrafo Nao Orientado (Grafo)\n");
				op2 = submenu();
				switch (op2)
				{

				case 'A':
					verificaSimplesAdjacencia(m, &simples);
					if (simples == 1)
						printf("\nNao eh simples");
					else
						printf("\nEh simples");

					getchar();
					break;
				case 'B':
					verificarRegularAdjacencia(m, &regular);
					if (regular == 1)
						printf("\nNao Regular\n");
					else
						printf("\nRegular\n");
					getchar();
					break;
				case 'C':
					if (regular == 0 && simples == 0) // tem q ser regular e simples, para ser completo
					{
						verificarCompletoAdjacencia(m, &completo, 4);
						if (completo == 1) // nao eh completo
							printf("\nNao eh completo\n");
						else
							printf("\nCompleto\n");
					}
					else
						printf("\nNao eh completo\n");

					getchar();
					break;
				}
			} while (op2 != 27);
			break;
		case 'B':
			do
			{
				// clrscr();
				op2 = submenu();
				switch (op2)
				{
				case 'A':
					printf("grafo orientado incidencia\n");
					getchar();
					break;
				}
			} while (op2 != 27);
			break;
		}

	} while (op != 27);
}
int main(void)
{

	executar();
	return 0;
}
