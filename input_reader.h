#ifndef __READER__
#define __READER__

#include "avl.h"
#define TAMMAX 50

// Definiçoes de tipos
struct list_type
{
	int vector[TAMMAX];
	int final;	
};

typedef struct list_type list_type; 

// Prototipos das funçoes de lista
void list_initialization(list_type *list);
int list_insert(list_type *list, int data);
int list_remove(list_type *list, int data);
int list_search(list_type *list, int data);

// Prototipos das demais funcoes
void read_input(FILE *arq, avl_node **node, list_type *list);
void save_output(FILE *arq, avl_node **node, list_type *list);
void shellsort(int vector[], int limit);

#endif
