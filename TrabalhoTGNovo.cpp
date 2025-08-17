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
		
		int grafo = 0, simples = 0, regular = 0, regularEmissao = 0, regularRecepcao = 0, completo = 0, laco = 0, multi = 0, grau = 0, n;
		int m[L][C], qtdeVertices = 0, qtdeLinhas = 0, qtdeColunas = 0, qtdeArestas = 0;
		char vertices[C], arestas[C];
		arestas[0] = '\0';
		clrscr();
		op = menu();
		switch(op)
		{
			case 'A':
				lerTxTMatrizAdjacencia(m, &qtdeVertices, &qtdeLinhas, &qtdeColunas, vertices);
				do
				{
					clrscr();
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
				lerTxTMatrizIncidencia(m, &qtdeVertices, &qtdeArestas, &qtdeLinhas, &qtdeColunas, vertices, arestas);
				do
				{	
					clrscr();
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
						getch();
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
						getch();
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
