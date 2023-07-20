#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "views.h"
#include "utils.h"
#include "listaaviao.h"
#include "listaaeroporto.h"
#include "listavoos.h"
#include "listabilhete.h"

PlainNode* plains = NULL;
AirportNode* airports = NULL;
FlightNode* flights = NULL;
TicketNode* tickets = NULL;

void gestaoaviao();
void gestaoaeroporto();
void gestaovoo();
void gestaobilhete();

void options();
void savegestaodados();

void gestaodados() {
    printf("Gestao de Dados \n Pretende gerir:\n");
    printf("1. Avioes.\n");
    printf("2. Aeroportos.\n");
    printf("3. Voos.\n");
    printf("4. Bilhetes.\n");

    int choice;
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            gestaoaviao();
            break;
        case 2:
            gestaoaeroporto();
            break;
        case 3:
            gestaovoo();
            break;
        case 4:
            gestaobilhete();
            break;
        default:
            tryAgain();
            gestaodados();
    }

    printf("Deseja efetuar qualquer outra operacao?\n");
    printf("1. Sim.\n");
    printf("2. Nao.\n");

    scanf("%d", &choice);

    switch(choice) {
        case 1:
            gestaodados();
            break;
        case 2:
            savegestaodados();
            break;
        default:
            tryAgain();
            gestaodados();
    }
};

void gestaoaviao() {
    options();

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            addPlain(&plains);
            printf("a");
            break;
        case 2:
            printf("Insira o numero do aviao que deseja remover.\n");

            int registrationCode;
            scanf("%d", &registrationCode);

            removePlain(&plains, registrationCode);
        case 3:
            changePlain(&plains);
            break;
        case 4:
            printPlains(&plains);
            break;
        case 5:
            printf("Insira o codigo do aviao que deseja encontrar.\n");

            int registrationCode1;
            scanf("%d", &registrationCode1);

            Plain* plain = NULL;

            getPlain(&plains, &plain, registrationCode1);
            printPlain(&plain);

            break;
    }
};

void gestaoaeroporto() {
    options();

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            addAirport(&airports);
            break;
        case 2:
            printf("Insira o numero do aviao que deseja remover.\n");

            char iataCode[3];
            scanf("%s", iataCode);

            removeAirport(&airports, iataCode);
            break;
        case 3:
            changeAirport(&airports);
            break;
        case 4:
            printAirports(&airports);
            break;
        case 5:
            printf("Insira o codigo do aviao que deseja encontrar.\n");

            char iataCode1[3];
            scanf("%s", iataCode1);

            Airport* airport = NULL;

            getAirport(&airports, &airport, iataCode1);
            printAirport(&airport);

            break;
    }
};

void gestaovoo() {
    options();

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            addFlight(&flights);
            break;
        case 2:
            printf("Insira o numero do aviao que deseja remover.\n");

            int number;
            scanf("%d", &number);

            removeFlight(&flights, number);
            break;
        case 3:
            changeFlight(&flights);
            break;
        case 4:
            printFlights(&flights);
            break;
        case 5:
            printf("Insira o codigo do aviao que deseja encontrar.\n");

            int number1;
            scanf("%d", &number1);

            Flight* flight = NULL;
            getFlight(&flights, &flight, number1);
            printFlight(&flight);

            break;
    }
};

void gestaobilhete() {
    options();

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            addTicket(&tickets);
            break;
        case 2:
            printf("Insira o numero do aviao que deseja remover.\n");

            long idCitizenship;
            scanf("%ld", &idCitizenship);

            removeTicket(&tickets, idCitizenship);
            break;
        case 3:
            changeTicket(&tickets);
            break;
        case 4:
            printTickets(&tickets);
            break;
        case 5:
            printf("Insira o codigo do aviao que deseja encontrar.\n");

            long idCitizenship1;
            scanf("%ld", &idCitizenship1);

            Ticket* ticket = NULL;

            getTicket(&tickets, &ticket, idCitizenship1);

            break;
    }
};

void options() {
    printf("1. Adicionar.\n");
    printf("2. Remover.\n");
    printf("3. Mudar.\n");
    printf("4. Listar.\n");
    printf("5. Procurar.\n");
}

void savegestaodados() {
    savePlains(&plains);
    saveAirports(&airports);
    saveFlights(&flights);
    saveTickets(&tickets);
};
