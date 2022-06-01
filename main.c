/**
*  @file main.c
 * @author Henrique Azevedo
 * @email henrique.aazevedo29@gmail.com
 * @date 2022
 * @brief Trabalho Pratico
 *
 *	Manipulação Das estruturas dinamicas de dados.

 * @bug bugs desconhecidos.
*/

#include <stdio.h>
#include <stdlib.h>
#include "Dados.h"
#include "functions.h"



int main() {

	setlocale(LC_ALL, "Portuguese");
	
	Job* Job1 = Readdatatxt("data.txt");
	
	JobI* job1 = Job1;
	JobI* job2 = Job1->next;
	JobI* job3 = Job1->next->next;
	JobI* job4 = Job1->next->next->next;
	JobI* job5 = Job1->next->next->next->next;
	JobI* job6 = Job1->next->next->next->next->next;
	JobI* job7 = Job1->next->next->next->next->next->next;
	JobI* job8 = Job1->next->next->next->next->next->next->next;
	
	

	JobI* hashTable[Hash_size];

	BuildHash(hashTable, Hash_size);

	*hashTable = AddJobHash(job1, hashTable);
	*hashTable = AddJobHash(job2, hashTable);
	*hashTable = AddJobHash(job3, hashTable);
	*hashTable = AddJobHash(job4, hashTable);
	*hashTable = AddJobHash(job5, hashTable);
	*hashTable = AddJobHash(job6, hashTable);
	*hashTable = AddJobHash(job7, hashTable);
	*hashTable = AddJobHash(job8, hashTable);

	Machine* Mach1 = newMachine(2, 2);
	Operation* Op1 = newOperation(4, Mach1);
	
	InsertOperationOnJob(hashTable, Op1, 6);
	RemoveOpJob(hashTable, 4, 6);

	ChangeOp(hashTable, 1, 1, 1, 8);

	int minProcessPlan = ProcessPlanMinTime(hashTable, Hash_size);
	//Job* Job1 = ReadbinFile("datab.bin");

	int min = getmintime(Job1);
	int max = getmaxtime(Job1);
	int avg = getavgtime(Job1);

	
	//SavebinFile("datab.bin", Job1);
	
	Savedatatxt("dataaa.txt", Job1);

	int c = CountMachines(Job1, 1, 1);
	

	
}

