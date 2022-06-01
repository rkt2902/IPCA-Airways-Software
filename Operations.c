/**
*  @file Operations.c
 * @author Henrique Azevedo
 * @email henrique.aazevedo29@gmail.com
 * @date 2022
 * @brief Trabalho Pratico
 *
 *	Operaçoes responsaveis pela Criação/Modificaçao da Estrutura Dinamica ligada às Operaçoes.

 * @bug bugs desconhecidos.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dados.h"




/**
* @brief Verifica se a operaçao existe. Se existir devolve Bool!
* @param [in] h		Inicio da Lista
* @param [in] order	código do Operation a procurar
* @return	True/False
*/
bool ExisteOperation(Operation* h, int order) {
	if (h == NULL) return false;
	Operation* aux = h;
	while (aux != NULL) {
		if (aux->order == order)
			return true;
		aux = aux->next;
	}
	return false;
}
/**
*	@brief Cria nova Operation.
*
*	Aloca memória necessária para armazenar um Operation em memória
*
*	@param order Ordem da Operation
*
*/
Operation* newOperation(int order, Machine* h) {

	Operation* new = (Operation*)malloc(sizeof(Operation));

	if (new == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	new->order = order;
	new->Machine = h;
	new->next = NULL;

	return new;
}
/**
* @brief Insere Operation no final da lista
* @param [in] h		Inicio da Lista
* @param [in] new	Nova Operation a inserir
* @return	Inicio da Lista
*/
Operation* InsertOperationEnd(Operation* h, Operation* new)
{
	if (ExisteOperation(h, new->order)) return h;

	if (h == NULL) {
		h = new;
	}
	else {
		Operation* aux = h;
		while (aux->next != NULL) {
			aux = aux->next;
		}

		aux->next = new;
	}
	return h;
}/**
* @brief Insere Operation no final da Lista dentro de um Job
* @param [in] h		Inicio da Lista de Jobs
* @param [in] hc	Inicio da Lista de Operaçoes
* @param [in] id	id do Jobs onde é desejado inserir operaçao
* @return	NULL
*/
Job* InsertOperationOnJob(Job* h, Operation* c, int id) {
	if (h == NULL) return NULL;
	if (c == NULL) return h;

	Job* aux = SearchJob(h, id);
	if (aux) {
		aux->operation = InsertOperationEnd(aux->operation, c);
		numoperations++;
	}
	return NULL;
}
/**
* @brief Altera tipo de Operation
* @param [in]	h	Apontador para inicio da Lista de Jobs
* @param [in]	order	Ordem da Operation a alterar
*  @param [in]	c	Apontador para inicio da Lista  Nova de Operaçoes que pretende alterar
* @return	Apontador para Lista de Jobs
*/
Job* ChangeOperation(Job* h, int order, Operation* new) {

	if (h == NULL) return NULL;
	if (new == NULL) return h;

	Job* aux = h;

	while (aux) {

		Operation* aux1 = aux->operation;

		while (aux1) {

			if (aux1->order == order) {

				aux1->order = new->order;
			}
			aux1 = aux1->next;
		}
		aux = aux->next;
	}

	return h;
}
/**
* @brief Remove Operation.
* @param [in]	h	Apontador para inicio da Lista de JObs
* @param [in]	c	Apontador para inicio da Lista de Operations
* @param [in]	id	Ordem do id do Job da Operation.
* @param [in]	order	Ordem do Operation a remover.
* @return	Apontador para Lista
*/
Job* RemoveOperation(Job* h, Operation* c, int id, int order) {


	if (h == NULL) return NULL;			//Lista vazia

	Operation* aux = h->operation;
	if (h->operation->order == order) {		//remove no inicio da lista
		
		h->operation = h->operation->next;
		numoperations--;
		free(aux);
	}
	else
	{
		Operation* auxAnt = aux;
		while (aux && aux->order != order) {	//procura para revover
			auxAnt = aux;
			aux = aux->next;

		}
		if (aux != NULL) {					//se encontrou, remove
			if (aux != NULL) {					//se encontrou, remove

				auxAnt->next = aux->next;
				numoperations--;
				free(aux);
			}
		}
		return h;


	}
}
/**
* @brief Procura operation
* @param [in]	h	Apontador para inicio da Lista
* @param [in]	order	Order do Operation a alterar
* @return	Apontador para Lista 
*/
Operation* SearchOperation(Operation* h, int order){
	if (h == NULL) return NULL;		//lista vazia
	else
	{
		Operation* aux = h;
		while (aux != NULL) {
			if (aux->order == order) {
				return (aux);		//encontrei
			}
			aux = aux->next;
		}
		return NULL;
	}
}


Operation* ChangeOperationMachine(Operation* op, int order, int machineid, int time) {
	Operation* aux = op;

	if (aux == NULL) {
		return  NULL;
	}

	while (aux) {
		if (order == aux->order) {

			Machine* aux2 = aux->Machine;
			while (aux2) {
				if (aux2->machineId == machineid) {
					aux2->time = time;
;				}
				aux2 = aux2->next;
			}
		}
		aux = aux->next;
	}
	return op;

}

/*
*@brief	Remover uma nova operação a uma linked list Operation
* @param	operations	Referência da head da linked list
* @param	operation	Operação a remover
* @return	Referência da head da linked list
*/
Operation * removeOperation(Operation * operations, int order) {

	if (operations == NULL) {
		return NULL;
	}
	if (operations->order == order) {
		Operation* aux = operations;
		operations = operations->next;

		free(aux);
	}
	else {
		Operation* aux = operations;
		Operation* previousaux = aux;

		while (aux && aux->order != order)
		{
			previousaux = aux;
			aux = aux->next;
		}
		if (aux != NULL) {
			previousaux->next = aux->next;
			free(aux);
		}

	}
	
	return operations;
}