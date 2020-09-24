#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "input_reader.h"

int main()
{
	avl_node *root = NULL;
	list_type *list = (list_type *)malloc(sizeof(list_type));
	FILE *arq_input;
	FILE *arq_output;

	// Abertura do arquivo de entrada para leitura
	arq_input = stdin;
	arq_output = stdout;
	if(arq_input == NULL || arq_output == NULL)
	{
		printf("ERRO: Nao foi possivel abrir um dos arquivos necessarios\n");
		exit(0);
	}

	// Inicializacoes
	list_initialization(list);
		
	// Leitura do arquivo
	read_input(arq_input,&root,list);

	// Ordena a lista em vetor
	shellsort(list->vector,list->final);
	
	// Salva lista ordenada no arquivo
	save_output(arq_output,&root,list);
	preorder(root);

	// Libera a memoria alocada
	free(list);
	avl_free(root);
	return 0;
}
