/**
*  @file Jobs.c
 * @author Henrique Azevedo
 * @email henrique.aazevedo29@gmail.com
 * @date 2022
 * @brief Trabalho Pratico
 *
 *	Operaçoes responsaveis pela Criação/Modificaçao da Estrutura Dinamica ligada às Maquinas.

 * @bug bugs desconhecidos.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dados.h"


/**
* @brief Verifica se a maquina existe. Se existir devolve Bool!
* @param [in] h		Inicio da Lista
* @param [in] machineId	código do job a procurar
* @return	True/False
*/
bool ExisteMachine(Machine* h, int machineId) {
	if (h == NULL) return false;
	Machine* aux = h;
	while (aux != NULL) {
		if (aux->machineId == machineId)
			return true;
		aux = aux->next;
	}
	return false;
}
/**
*	@brief Cria nova Machine.
*
*	Aloca memória necessária para armazenar uma Machine em memória
*
*	@param machineId Ordem da Machine
*
*/
Machine* newMachine(int machineId, int time) {

	Machine* new = (Machine*)malloc(sizeof(Machine));

	if (new == NULL) // se não houver memória para alocar
	{
		return NULL;
	}

	new->machineId = machineId;
	new->time = time;
	new->next = NULL;

	return new;
}
/**
* @brief Insere Machine no final da lista
* @param [in] h		Inicio da Lista
* @param [in] new	Nova Machine a inserir
* @return	Inicio da Lista
*/
Machine* InsertMachineOnEnd(Machine* h, Machine* new) {

	if (ExisteMachine(h, new->machineId)) return h;

	if (h == NULL) {
		h = new;
	}
	else {
		Machine* aux = h;
		while (aux->next != NULL) {
			aux = aux->next;
		}

		aux->next = new;
	}
	return h;

}
/**@brief Insere Machine no final da Lista dentro de um Job
* @param[in] h		Inicio da Lista de Jobs
* @param[in] t	    Inicio da Lista de Operaçoes
* @param[in] c	    Inicio da Lista de Machines
* @param[in] id	    id do Jobs onde é desejado inserir operaçao
* @param[in] order	Order da Operation onde é desejado inserir Machine
* @return	NULL
*/
Job* InsertMachineOnOperation(Job* h,Operation* t, Machine* c, int id, int order) {

	if (h == NULL) return NULL;
	if (t == NULL) return NULL;
	if (c == NULL) return h;

	Job* aux = SearchJob(h, id);
	if(aux) {
		Operation* aux1 = SearchOperation(t, order);
		if (aux1) {
			aux1->Machine = InsertMachineOnEnd(aux1->Machine, c);
			nummachines++;
		}
		
	}
	
	return NULL;
}
/**
* @brief Altera tipo de Machine
* @param [in]	h	Apontador para inicio da Lista de Jobs
* @param [in]	machineid	MachineId da Machine a alterar
*  @param [in]	new    Apontador pra machine pra inserir
* @return	Apontador para Lista de Jobs
*/
Job* Changemachine(Job* h, int machineid, Machine* new) {
	if (h == NULL) return NULL;
	if (new == NULL) return h;

	Job* aux = h;

	while (aux) {

		Operation* aux1 = aux->operation;

		while (aux1) {

			Machine* aux2 = aux1->Machine;

			while (aux2) {
				if (aux2->machineId == machineid) {
						aux2->machineId = new->machineId;
						aux2->time = new->time;
				}
				aux2 = aux2->next;
				}
			
			aux1 = aux1->next;
		}
		aux = aux->next;
	}

	return h;
}
/**
* @brief Remove MAchine
* @param [in]	h	Apontador para inicio da Lista de JObs
* @param [in]	c	Apontador para inicio da Lista de Operations
* @param [in]	id	Ordem do id do Job da Operation.
* @param [in]	MachineId	MachineId do Operation a remover.
* @return	Apontador para Lista
*/
Job* RemoveMachine(Job* h, Machine* c, int id, int machineId) {


	if (h == NULL) return NULL;			//Lista vazia


	if ((h->operation->Machine->machineId == machineId) ) {		//remove no inicio da lista
		Operation* aux = h->operation;
		h->operation = h->operation->next;
		nummachines--;
		free(aux);
	}
	else
	{
		Machine* aux = h->operation->Machine;
		Machine* auxAnt = aux;
		while (aux && aux->machineId != machineId) {	//procura para revover
			auxAnt = aux;
			aux = aux->next;
		}
		if (aux != NULL) {					//se encontrou, remove
			auxAnt->next = aux->next;
			nummachines--;
			free(aux);
		}
	}
	return h;


}
/**
* @brief Conta o numero de maquinas Por Operaçao
* @param [in]	h	Apontador para inicio da Lista de Jobs
* @param [in]	id	Id do Job onde esta a operaçao com a Machines
* @param [in]	Order	Ordem da Operaçao que contem as MAchines.
* @return	Apontador para Lista
*/
int CountMachines(Job* h, int id, int order)
{
	if (h == NULL) return NULL;
	int c=0;
	Job* aux = h;
	while (aux) {
		if(aux->id == id){
			Operation* aux1 = aux->operation;
			while (aux1)
			{
				if(aux1->order == order){
					Machine* aux2 = aux1->Machine;
						while (aux2) { c++; aux2 = aux2->next; }
					
				}
				aux1 = aux1->next;
			}
			
		}
		aux = aux->next;
	}
	return c;
}



