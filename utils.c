#include <stdio.h>
#include <time.h>
#include "utils.h"
#include <sys/stat.h>
void pressEnter() {
    int ch;
	while ((ch = getchar()) != '\n' && ch != EOF); 
	printf("\nPressione Enter para continuar.");
	while ((ch = getchar()) != '\n' && ch != EOF);
};

void tryAgain() {
	printf("Opcao incorrecta. \n");
};