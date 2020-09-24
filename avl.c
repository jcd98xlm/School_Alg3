#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

//Implementação das funçoes

// Funcao que inicializa uma arvore avl
void avl_initialization(avl_node *root)
{
	root->value = 0;
	root->left = NULL;
	root->right = NULL;
}

// Funcao que cria um novo no
avl_node *create_node(int key)
{
	avl_node *aux;
	aux = (avl_node *)malloc(sizeof(avl_node));
	aux->value = key;
	aux->left = NULL;
	aux->right = NULL;
	return aux;
}

// Funcao que insere um novo no na arvore
avl_node *avl_insert(avl_node *node, int key)
{
	// Insercao padrao de uma BST
	if(node == NULL)			// Caso nao exista um no alocado anteriormente
		return(create_node(key));
	if(key < node->value)		// Insere na subarvore da esquerda
		node->left = avl_insert(node->left,key);
	else if(key > node->value)		// Insere na subarvore da esquerda
		node->right = avl_insert(node->right,key);
	else						// Tentando inserir um valor existente
		return node;

		
	// Calculo do fator de balanceamento
	int balance = calculate_balancing_factor(node);

	// Ajustes necessarios para cada caso
	if(balance > 1 && key < node->left->value)	// Caso esquerda-esquerda
		node = rotate_right(node);				
	else if(balance < -1 && key > node->right->value) // Caso direita-direita
		node = rotate_left(node);				
	else if(balance > 1 && key > node->left->value)	// Caso esquerda-direita
	{
		node->left = rotate_left(node->left);
		node = rotate_right(node); 
	}
	else if(balance < -1 && key < node->right->value) // Caso direita-esquerda
	{
		node->right = rotate_right(node->right);
		node = rotate_left(node);
	}

	// Retornar o ponteiro que nao sofreu mudancas
	return node;
}

// Funcao que exclui um elemento da arvore
avl_node *avl_delete(avl_node *node, int key)
{
	// Exclusao padrao de uma BST
	if(node == NULL)
		return node;
	if(key < node->value)			// Desce pela subarvore esquerda
		node->left = avl_delete(node->left,key);
	else if(key > node->value)		// Desce pela subarvore direita
		node->right = avl_delete(node->right,key);
	else			// O no atual é aquele a ser removido
	{
		if((node->left == NULL) || (node->right == NULL))	// No com um unico filho ou nenhum
		{
			avl_node *aux = node->left ? node->left : node->right;
			
			if(aux == NULL)		// Caso onde nao ha filhos
			{
				aux = node;
				node = NULL;
			}
			else				// Caso um filho
				*node = *aux;
			free(aux);
		}
		else		// No com dois filhos
		{
			avl_node *aux = predecessor(node);	// Pega o antecessor
			node->value = aux->value;
			node->left = avl_delete(node->left,aux->value);	// Deletar o antecessor
		}	
	}
	if(node == NULL)		// Caso onde so havia um no na arvore
		return node;

	// calcula fator de balanceamento
	int balance = calculate_balancing_factor(node);
	
	// Trata os casos, se necessario
	if(balance > 1 && calculate_balancing_factor(node->left) >= 0)	// Caso esq-esq
		node = rotate_right(node);
	else if(balance > 1 && calculate_balancing_factor(node->left) < 0)	// Caso esq-dir
	{
		node->left = rotate_left(node->left);
		node = rotate_right(node);
	}
	else if(balance < -1 && calculate_balancing_factor(node->right) <= 0)  // Caso dir-dir
		node = rotate_left(node);
	else if(balance < -1 && calculate_balancing_factor(node->right) > 0)  // Caso dir-esq
	{
		node->right = rotate_right(node->right);
		node = rotate_left(node);
	}
	
	return node;
}

// Funcao que encontra o antecessor de um no
avl_node *predecessor(avl_node *node)
{
	avl_node *current = node->left;
	// Desce na arvore ate achar o antecessor
	while(current->right != NULL)
		current = current->right;

	return current;
}

// Funcao auxiliar que calcula o maior entre dois inteiros
int max(int x, int y)
{
	return (x > y)? x : y;
}

// Funcao que calcula a altura de uma subarvore avl a partir do ponto dado
int calculate_height(avl_node *node)
{
	if(node == NULL)
		return 0;
	int hl,hr;
	hl = calculate_height(node->left);
	hr = calculate_height(node->right);
	return (max(hl,hr)+1);
}

// Funcao que percoore e imprime os conteudos da arvore em pre-ordem
void preorder(avl_node *node)
{
	if(node != NULL)
	{
		printf("%d(",node->value);
		preorder(node->left);
		printf(",");
		preorder(node->right);
		printf(")");
	}
	else
		printf("*");
}

// Funcao que faz rotacao a direita de um no
avl_node *rotate_right(avl_node *node)
{
	avl_node *x = node->left;
	avl_node *y = x->right;

	// Faz a troca
	x->right = node;
	node->left = y;
	
	return x;
}

// Funcao que faz rotacao a esquerda de um no	
avl_node *rotate_left(avl_node *node)
{
	avl_node *x = node->right;
	avl_node *y = x->left;

	// Faz a troca
	x->left = node;
	node->right = y;

	return x;
}

// Funcao que calcula o fator de balnceamento de um no
int calculate_balancing_factor(avl_node *node)
{
	if(node == NULL)
		return 0;
	return (calculate_height(node->left) - calculate_height(node->right));
}

// Funcao que busca um determinado nodo na arvore avl
avl_node *avl_search(avl_node *node, int key)
{
	if(node == NULL)
		return NULL;
	else if(key == node->value)
		return node;
	else if(key < node->value)
		return(avl_search(node->left,key));
	else
		return(avl_search(node->right,key));
}

// Funcao que descobre a altura de um nodo na arvore avl a partir da raiz
int calculate_height_inverse(avl_node *node, avl_node *current)
{
	if(node == NULL)
		return 0;
	else if(node->value < current->value)
		return (calculate_height_inverse(node,current->left)+1);
	else if(node->value > current->value)
		return (calculate_height_inverse(node,current->right)+1);
	else
		return 0;
}

// Funcao que libera toda a memoria alocada na arvore avl
void avl_free(avl_node *node)
{
	if(node != NULL)
	{
		avl_free(node->left);
		avl_free(node->right);
		free(node);
	}
}
