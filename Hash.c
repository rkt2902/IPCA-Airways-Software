/**
*  @file Hash.c
 * @author Henrique Azevedo
 * @email henrique.aazevedo29@gmail.com
 * @date 2022
 * @brief Trabalho Pratico
 *
 *	

 * @bug bugs desconhecidos.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dados.h"

/**
* @brief FunçaoHash
* @param [in]	id	Id do job
*
* @return	resultado da função Hash, que determina a posiçao onde fica o job
*/
int HashFunction(int id) {
    int result;
    result = id % Hash_size;
    return (result);
}

/**
* @brief Construir a tabela hash
* @param [in]	table[]	tabela hash
* @param [in]	size tamanho da tabela	
*/

void BuildHash(Job* table[], int size) {

    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
}

/**
* @brief Adicionar um Job à tabela hash
* @param [in]	h Inicio da Lista dos Jobs
* @param [in]	table[]	tabela hash
* 
*@return	tabela hash
*/
JobI** AddJobHash(JobI* h, JobI* table[]) {
    int indice = HashFunction(h->id);

    table[indice] = h;
    
    return *table;
}

/**
* @brief Remover Um job da Hash table
* @param [in]	id ID jo Job
*  @param [in]	table[]	tabela hash	
* 
* *@return	tabela hash
*/
Job** removeHashJob(int id, Job* table[]) {

    int indice = HashFunction(id);

    if (indice < 0) {
        return *table;
    }

    table[indice] = RemoveJob(table[indice], id);

    return *table;
}

/**
* @brief Inserir Operação no Job
* @param [in]	table[]	tabela hash
* @param [in]	order Ordem da Operação
* @param [in]	id    Id do Job
*
* *@return	tabela hash
*/
Job** InsertOponJob(Job* table[], Operation* operation, int id) {
    int indice = HashFunction(id);

    if (indice < 0) {
        return *table;
    }

    Job* job = SearchJob(table[indice], id);

    if (job != NULL) {
        job->operation = InsertOperationEnd(job->operation, operation);
    }

    return *table;
}

/**
* @brief Remover Operação do Job
* @param [in]	table[]	tabela hash
* @param [in]	order Ordem da Operação
* @param [in]	id    Id do Job	
* 
* *@return	tabela hash
*/
Job** RemoveOpJob(Job* table[], int order, int id) {

    int indice = HashFunction(id);
    if (indice < 0) {
        return *table;
    }

    Job* job = SearchJob(table[indice], id);

    if (job != NULL) {
        job->operation = removeOperation(job->operation, order);
    }
    return *table;
}

/**
* @brief Mudar Operação do Job
* @param [in]	table[]	tabela hash
* @param [in]	id    Id do Job
* @param [in]	order Ordem da Operação
* @param [in]	machineId    Id da maquina
* @param [in]	time    tempo da maquina
*
* *@return	tabela hash
*/
Job** ChangeOp(Job* table[], int id, int order, int machineId, int time) {
    int indice = HashFunction(id);
    if (indice < 0) {
        return *table;
    }
    JobI* job = SearchJob(table[indice], id);

    if (job != NULL) {
        job->operation = ChangeOperationMachine(job->operation, order, machineId, time);
    }
    return *table;
}

