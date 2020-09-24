#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input_reader.h"
#include "avl.h"

// Funcao que faz a leitura do arquivo de entrada .txt
void read_input(FILE *arq, avl_node **node, list_type *list)
{
	char str[20];
	char *token1, *token2;
	const char *delim = " ";
	int j = 0;
	if(arq != NULL)
	{
		do
		{
			fgets(str,20,arq);		// Pega frase do arquivo
			token1 = strtok(str,delim);		// Pega primeiro token
			if(!strcmp(token1,"i"))	// Se for uma inclusao
			{
				token2 = strtok(NULL,delim);
				if(token2 != NULL)
				{
					j = list_insert(list,atoi(token2));
					*node = avl_insert(*node,j);
				}
			}
			else if(!strcmp(token1,"r"))	// Se for uma exclusao
			{
				token2 = strtok(NULL,delim);
				if(token2 != NULL)
				{
					j = list_remove(list,atoi(token2));
					*node = avl_delete(*node,j);
				}
			}
			if(strcmp(token1,"i") && strcmp(token1,"r"))
			{
				token2 = strtok(NULL,delim);
				if(token2 == NULL)
					break;
			}
			printf("DEBUG da AVL:\n");
			preorder(*node);
			printf("\n----------------------\n");
		}while(token1 != NULL && token2 != NULL);
	}
}

// Funcao que salva a saida em arquivo
void save_output(FILE *arq, avl_node **node, list_type *list)
{
	if(arq != NULL)
	{
		int content, i, aux;
		avl_node *temp;
		for(i=1;i<list->final;i++)
		{
			content = list->vector[i];
			temp = avl_search(*node,content);
			aux = calculate_height_inverse(temp,*node);
			fprintf(arq,"%d,%d\n",content,aux);
		}
	}
}

// Funcao que inicializa a lista em vetor
void list_initialization(list_type *list)
{
	list->final = 1;
}

// Funcao que insere um elemento na lista em vetor
int list_insert(list_type *list, int data)
{
	if(list->final <= TAMMAX)
	{
		list->vector[list->final] = data;
		list->final++;
		return data;
	}
	exit(0);	// Caso nao seja posivel inserir 
}

// Funcao que remove um elemento da lista em vetor
int list_remove(list_type *list, int data)
{
	int aux,i,position;
	position = list_search(list,data);
	if((position >= list->final) || (list->final == 1))
		exit(0);
	else
	{
		aux = list->vector[position];
		for(i=position;i<=(list->final - 2);i++)	// Faz ajuste no vetor 
			list->vector[i] = list->vector[i+1];
		list->final--;
		return aux;
	} 
}

// Funcao que busca um elemento na lista em vetor
int list_search(list_type *list, int data)
{
	int i = 1;
	do
	{
		i++;
	}while((list->vector[i] != data) && (i < list->final));
	if(i == list->final)	// Nao estava na lista
		return 0;
	return i;				// devolve a posicao do elemento
}

// Funcao que implementa o algoritmo de ordenacao shellsort
void shellsort(int vector[], int limit)
{
	int i,j,aux,gap=1;
	while(gap<=limit)
	{
		gap = 3*gap+1;
	}
	while(gap > 1)
	{
		gap = gap/3;
		for(i=gap;i<limit;i++)
		{
			aux = vector[i];
			j = i;
			while(vector[j-gap] > aux && j>=gap)
			{
				vector[j] = vector[j-gap];
				j = j - gap;
				if(j<=gap)
					break;				
			}
			vector[j] = aux;
		}
	}
}
