/**
* Author: Henrique Azevedo
* Email: henrique.aazevedo29@gmail.com
* Date: 19-03-2022
* Desc: Dados gerais.
*
*/

#pragma once
#ifndef dados;
#define Hash_size 8
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

int numoperations;
int nummachines;



#pragma region Structs

/**
 * @brief Estrutura para armazenar uma Machine sem apontador.
 *
 * Um jogo contém um machineId (@@machineId), Tempo (@@time).
 */
typedef struct MachineFile {
    int machineId;
    int time;

}MachineFile;
/**
 * @brief Estrutura para armazenar uma Operation sem apontador.
 *
 * Um jogo contém uma order (@@order).
 */
typedef struct OperationFile {
    int order;

}OperationFile;

/**
 * @brief Estrutura para armazenar um Job sem apontador.
 *
 * Um jogo contém um Identificador (@@id).
 */
typedef struct JobFile {
    int id;
}JobFile;



/**
 * @brief Estrutura para armazenar uma Machine
 *
 * Uma Maquina contém um MachineId (@@machineId), tempo (@@time).
 * Contém apontador para próxima MAchine
 */

typedef struct Machine {
    int machineId;
    int time;
    struct Machine* next;
}Machine;

/**
 * @brief Estrutura para armazenar uma Operation
 *
 * Uma Operation contém um Order(@@order)
 *  Contem apontador para Lista das Maquinas.
 * Contém apontador para próxima operaçao.
 */

typedef struct Operation{
    int order;  //ordem da operaçao
    Machine* Machine; //todas as maquinas da operaçao
    struct Operation* next; //Ligaçao para a prox operaçao
}Operation;
/**
 * @brief Estrutura para armazenar um Job.
 *
 * Um Job contém um Id(@@id)
 *  Contem apontador para Lista das Operation
 * Contém apontador para próximo job.
 */
typedef struct Job {
    int id;  //id do job
    struct Operation* operation; //Todas as operaçoes do Job
    struct Job* next; //Ligaçao ao proximo job
}Job;

/**
 * @brief Estrutura para Usar um Job na Hash table.
 *
 * Um Job contém um Id(@@id)
 *  Contem apontador para Lista das Operation
 * Contém apontador para próximo job.
 */
typedef struct JobIn {
    int id;  //id do job
    struct Operation* operation; //Todas as operaçoes do Job
}JobI;



#pragma endregion

#pragma region Functions 
//Job Functions
bool ExisteJob(Job* h, int id);
Job* newJob(int id);
Job* InsertJobStart(Job* h, Job* new);
Job* InsertJobEnd(Job* h, Job* new);
Job* RemoveJob(Job* h, int id);
Job* SearchJob(Job* h, int id);
Job* ChangeJob(Job* h, int id, Job* new);



//Operation Functions
Job* RemoveOperation(Job* h, Operation* c, int id, int order);
bool ExisteOperation(Operation* h, int order);
Operation* newOperation(int order, Machine* h);
Operation* InsertOperationEnd(Operation* h, Operation* new);
Job* InsertOperationOnJob(Job* h, Operation* c, int id);
Operation* SearchOperation(Operation* h, int order);
Job* ChangeOperation(Job* h, int order, Operation* new);
Operation* ChangeOperationMachine(Operation* op, int order, int time, int machineid);
Operation* removeOperation(Operation* operations, int order);

//Machine Functions
Machine* InsertMachineOnEnd(Machine* h, Machine* new);
Job* InsertMachineOnOperation(Job* h, Operation* t, Machine* c, int id, int order);
bool ExisteMachine(Machine* h, int machineId);
Machine* newMachine(int machineId, int time);
Job* Changemachine(Job* h, int machineid, Machine* new);
Job* RemoveMachine(Job* h, Machine* c, int id, int machineId);

//Read and Save
Job* Savedatatxt(char* nomeFicheiro, Job* h);
Job* Readdatatxt(char* nomeFicheiro);



//Get Machine Data
int getmintime(Job* h);
int getmaxtime(Job* h);
int getavgtime(Job* h);
int CountMachines(Job* h, int id, int order);
int ProcessPlanMinTime(Job* table[], int size);
int numberofJobs(Job* h);
int numberofoperationspJob(Job* h, int id);


//Hash Functions
int HashFunction(int id);
void BuildHash(Job* table[], int size);
JobI** AddJobHash(JobI* h, JobI* table[]);
Job** removeHashJob(int id, Job* table[]);
Job** InsertOponJob(Job* table[], Operation* operation, int id);
Job** RemoveOpJob(Job* table[], int order, int id);
Job** ChangeOp(Job* table[], int id, int order, int machineId, int time);
#pragma endregion

#endif