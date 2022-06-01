/**
*  @file gestor.c
 * @author Henrique Azevedo
 * @email henrique.aazevedo29@gmail.com
 * @date 2022
 * @brief Trabalho Pratico
 *
 *	Funçoes com o objetivo de gerir e verificar como funcionam as operaçoes.

 * @bug bugs desconhecidos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Dados.h"

/**
*	@brief  Determinar a quantidade minima de tempo pra completar um Job
*
*	Devolve o tempo minimo pra completar um job
*
*	@param h Inicio da Lista
*
*/
int getmintime(Job* h) {
	int result = 0;

	Operation* Op = h->operation;

	if (Op == NULL) return result;
	while (Op) {
		Machine* MACH = Op->Machine;

		int maxtime = MACH->time;
		MACH = MACH->next;

		while (MACH) {
			int time = MACH->time;

			if (maxtime > time) maxtime = time;

			MACH = MACH->next;
		}

		result += maxtime;
		Op = Op->next;
	}
	return result;
}
/**
*	@brief  Determinar a quantidade maximo de tempo pra completar um Job
*
*	Devolve o tempo maximo pra completar um job
*
*	@param h Inicio da Lista
*
*/
int getmaxtime(Job* h) {
	int result = 0;

	Operation* Op = h->operation;

	if (Op == NULL) return result;
	while (Op) {
		Machine* MACH = Op->Machine;

		int maxtime = MACH->time;
		MACH = MACH->next;

		while (MACH) {
			int time = MACH->time;

			if (maxtime < time) maxtime = time;

			MACH = MACH->next;
		}

		result += maxtime;
		Op = Op->next;
	}
	return result;
}
/**
*	@brief  Determinar a quantidade media de tempo pra completar um Job
*
*	Devolve o tempo medio pra completar um job
*
*	@param h Inicio da Lista
*
*/
int getavgtime(Job* h) {
	if (h == NULL) return NULL;

	int min = getmintime(h);
	int max = getmaxtime(h);

	return ((min + max) / 2);
}

/**
*	@brief  Determinar a quantidade minima de tempo pra completar o processplan
*
*	Devolve o tempo minimo pra completar o processplan
*
*	@param table Inicio da HashTable
*   @param size tamanho da hashtable
*
*/
int ProcessPlanMinTime(Job* table[], int size) {
	int result = 0;

	for (int i = 0; i < size; i++) {
		Job* aux = table[i];

		if (aux == NULL) continue;

		while (aux) {
			result += getmintime(aux);
			aux = aux->next;
		}

	}
	return result;
}

/**
*	@brief  Determinar a quantidade de Jobs existentes
*
*	Devolve a quantidade de Jobs existentes
*
*	@param h Inicio da Lista
*
*/

int numberofJobs(Job* h) {
	if (h == NULL) return NULL;

	Job* aux = h;
	int numbjobs = 0;
	while(aux){ 
		numbjobs++;
		aux = aux->next;
	}
	return numbjobs;
}
/**
*	@brief  Determinar a quantidade de operacoes num determinado JOB
*
*	Devolve a quantidade de operacoes num determinado JOB
*
*	@param h Inicio da Lista
*   @param id Id do job para analisar.
*
*/
int numberofoperationspJob(Job* h, int id) {
	if (h == NULL) return NULL;

	Job* job = SearchJob(h, id);
	Job* aux = job->operation;
	int numbop = 0;
	while (aux) {
		numbop++;
		aux = aux->next;
	}
	return numbop;
}