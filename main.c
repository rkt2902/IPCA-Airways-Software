#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataStructures.h"
#include "utils.h"
#include "views.h"

typedef struct
{
    int optNumber;
    char* description;
} MenuOption;

void mainMenu();

int main() {

    printf("Bem-vindo ao IPCA Airways\n");

    pressEnter();

    mainMenu();
}

void mainMenu() {
    printf("Escolha uma das seguintes opcoes:\n");
    int totalOptions = 2;

    MenuOption* options = malloc(sizeof(MenuOption) * totalOptions);

    options[0].description = (char*) malloc(sizeof(char*));
    options[0].description = "1. Gestao de dados";

    options[1].description = (char*) malloc(sizeof(char*));
    options[1].description = "2. Aplicacao";

    for(int i = 0; i < totalOptions; i++) {
        printf("%s \n", options[i].description);
    }

    int choice;
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            gestaodados();
            break;
        case 2:
            app();
            break;
        default:
            printf("Opcao incorreta. \n\n");
            mainMenu();
    }
}
