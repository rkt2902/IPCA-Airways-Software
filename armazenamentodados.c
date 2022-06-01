/**
*  @file armazenamentodados.c
 * @author Henrique Azevedo
 * @email henrique.aazevedo29@gmail.com
 * @date 2022
 * @brief Trabalho Pratico
 *
 *	Armazenamento das Estruturas e dos Dados Inseridos

 * @bug bugs desconhecidos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Dados.h"

/**
*	@brief Ler os dados atravez de um ficheiro de texto
*
*	Lê da memoria dados previamente inseridos em um ficheiro
*
*	@param nomeFicheiro Nome do ficheiro de texto que se pretende ler

*/
Job* Readdatatxt(char* nomeFicheiro)
{
	char c[100];
	FILE* fp = NULL;
	fp = fopen(nomeFicheiro, "r");
	if (fp == NULL) {
		perror("Erro ao abrir o ficheiro\n");
		getche();
		return(-1);
	}
	int jobinserted = 0;
	int l = 0;
	int linesop = 0;
	Job* Job1 = NULL;
	Operation* First = NULL;
	Machine* machines = NULL;
	int id;
	int linesjobs;
	while (fscanf(fp, "%[^\n] ", c) != EOF) {
		if (l == 0) {
			int numjobs;
			int x = sscanf(c, "%d\0", &numjobs);
			linesjobs = numjobs;
			l++;
			continue;
			
		}

		if(linesjobs != 0) {
			if (jobinserted == 0) {
				int numoperation;
				int x = sscanf(c, "%d,%d", &id, &numoperation);
				linesop = numoperation;

				Job* new = newJob(id);
				Job1 = InsertJobEnd(Job1, new);
				jobinserted++;
				continue;
				
			}
			

			if (linesop > 0) {
				int order, nmachines;
				int x = sscanf(c, "%d,%d(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)\0", &order, &nmachines);

				Operation* nova = newOperation(order, NULL);
				First = InsertOperationOnJob(Job1, nova, id);

				int i = 1;
				for (i; i <= nmachines; i++) {
					int machineid, time;

					if (i == 1) {
						int x = sscanf(c, "%*d,%*d(%d,%d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)\0", &machineid, &time);
						Machine* Mach = newMachine(machineid, time);
						machines = InsertMachineOnOperation(Job1, nova, Mach, id, order);
					}
					else if (i == 2) {
						int x = sscanf(c, "%*d,%*d(%*d,%*d)(%d,%d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)\0", &machineid, &time);
						Machine* Mach = newMachine(machineid, time);
						machines = InsertMachineOnOperation(Job1, nova, Mach, id, order);
					}
					else if (i == 3) {
						int x = sscanf(c, "%*d,%*d(%*d,%*d)(%*d,%*d)(%d,%d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)\0", &machineid, &time);
						Machine* Mach = newMachine(machineid, time);
						machines = InsertMachineOnOperation(Job1, nova, Mach, id, order);
					}
					else if (i == 4) {
						int x = sscanf(c, "%*d,%*d(%*d,%*d)(%*d,%*d)(%*d,%*d)(%d,%d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)\0", &machineid, &time);
						Machine* Mach = newMachine(machineid, time);
						machines = InsertMachineOnOperation(Job1, nova, Mach, id, order);
					}
					else if (i == 5) {
						int x = sscanf(c, "%*d,%*d(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%d,%d)(%*d,%*d)(%*d,%*d)(%*d,%*d)\0", &machineid, &time);
						Machine* Mach = newMachine(machineid, time);
						machines = InsertMachineOnOperation(Job1, nova, Mach, id, order);
					}
					else if (i == 6) {
						int x = sscanf(c, "%*d,%*d(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%d,%d)(%*d,%*d)(%*d,%*d)\0", &machineid, &time);
						Machine* Mach = newMachine(machineid, time);
						machines = InsertMachineOnOperation(Job1, nova, Mach, id, order);
					}
					else if (i == 7) {
						int x = sscanf(c, "%*d,%*d(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%d,%d)(%*d,%*d)\0", &machineid, &time);
						Machine* Mach = newMachine(machineid, time);
						machines = InsertMachineOnOperation(Job1, nova, Mach, id, order);
					}
					else if (i == 8) {
						int x = sscanf(c, "%*d,%*d(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%*d,%*d)(%d,%d)\0", &machineid, &time);
						Machine* Mach = newMachine(machineid, time);
						machines = InsertMachineOnOperation(Job1, nova, Mach, id, order);
					}

				}



				linesop--;
				continue;
			}
			jobinserted--;
			linesjobs--;
		}
		
	}
	fclose(fp);
	
	return Job1;
}
/**
*	@brief Guardar dados num ficheiro de texto
*
*	Guarda em memoria os dados inseridos/carregados.
*
*	@param nomeFicheiro Nome do ficheiro de texto onde se pretende guardar dados.
*   @param h Inicio da Lista

*/
Job* Savedatatxt(char* nomeFicheiro, Job* h) {
	
	if (h == NULL) return false;

	char c[100];
	FILE* fp = NULL;

	fp = fopen(nomeFicheiro, "w");
	if (fp == NULL) {
		perror("Erro ao abrir o ficheiro\n");
		getche();
		return(-1);
	}
	int numberofjobs = numberofJobs(h);
	Job* aux = h;
	

	fprintf(fp,"%d\n", numberofjobs);
	while(aux){
		
	Operation* aux1 = aux->operation;
	
	int l = 1;
			if (l == 1) {
				fprintf(fp,"%d,%d\n", aux->id, numberofoperationspJob(aux, aux->id));
				l++;
				if (aux->id > 1) {
					fprintf(fp, "%d,%d\n", aux->id, numberofoperationspJob(aux, aux->id));
				}
				
						}
			if (l > 1) {
				
				while (aux1) {
					Machine* aux2 = aux1->Machine;
					int nummach = CountMachines(aux, aux->id, aux1->order);
					fprintf(fp,"%d,%d", aux1->order, nummach);

					while(aux2) {
						fprintf(fp,"(%d,%d)", aux2->machineId, aux2->time);
						aux2 = aux2->next;
					}

					
					fprintf(fp, "\n");
				aux1 = aux1->next;
				
				}		
					}
	aux = aux->next;
			fprintf(fp, "\n");
	}


	fclose(fp);
	return true;
}
