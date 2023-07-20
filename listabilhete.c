#include "listabilhete.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
int mkdir(const char *pathname, mode_t mode);
#define TICKET_FILE "./Resources/tickets.txt"
#define LINE_TO_WRITE "%s_%ld_%d_%d_%lf_%lf"

void addTicket(TicketNode** headRef) {
    TicketNode *newNode = (TicketNode*) malloc(sizeof(TicketNode));
    TicketNode *lastNode = (*headRef);

    Ticket *newTicket = (Ticket*) malloc(sizeof(Ticket));

    char* passengerName = (char*) malloc(sizeof(char*));
    printf("Nome do passageiro: ");
    scanf(" %[^\t\n]s", passengerName);
    newTicket->passengerName = passengerName;

    long idCitizenship;
    printf("Cartao cidadao: ");
    scanf("%ld", &idCitizenship);
    newTicket->idCitizenship = idCitizenship;

    int flightNumber;
    printf("Numero de voo: ");
    scanf("%d", &flightNumber);
    newTicket->flightNumber = flightNumber;

    int seat;
    printf("Lugar: ");
    scanf("%d", &seat);
    newTicket->seat = seat;

    double price;
    printf("Preco: ");
    scanf("%lf", &price);
    newTicket->price = price;

    double miles;
    printf("Milhas: ");
    scanf("%lf", &miles);
    newTicket->miles = miles;

    newNode->data = (*newTicket);

    if ((*headRef) == NULL)
    {
       (*headRef) = newNode;

    } else {
        while (lastNode->next != NULL)

        {
            lastNode = lastNode->next;
        }

        lastNode->next = newNode;
    }
};

void addTicketOnRuntime(TicketNode** headRef, Ticket* newData) {
    TicketNode *newNode = (TicketNode*) malloc(sizeof(TicketNode));
    TicketNode *lastNode = (*headRef);

    newNode->data = (*newData);

    if ((*headRef) == NULL)
    {
       (*headRef) = newNode;

    } else {
        while (lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }

        lastNode->next = newNode;
    }
};

void removeTicket(TicketNode** headRef, long idCitizenship) {
    TicketNode *temp = *headRef, *prev;

    if (temp != NULL && temp->data.idCitizenship == idCitizenship) {
        *headRef = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data.idCitizenship != idCitizenship) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return;
    }

    prev->next = temp->next;

    free(temp);
};

void getTicket(TicketNode** headRef, Ticket** dataToGet, long idCitizenship) {
    TicketNode *temp = (*headRef);

    if ((*headRef) == NULL) {
        return;
    }

    while (temp != NULL) {
        if (temp->data.idCitizenship == idCitizenship) {
            (*dataToGet) = &(temp->data);
            break;
        }

        temp = temp->next;
    }
};

void changeTicket(TicketNode** headRef) {
    TicketNode *temp = (*headRef);
    Ticket *dataToChange = NULL;

    printf("Codigo do bilhete que pretende remover.\n");

    long idCitizenship;
    scanf("%ld", &idCitizenship);

    if ((*headRef) == NULL) {
        return;
    }

    while (temp != NULL) {

        if (temp->data.idCitizenship == idCitizenship) {
            dataToChange = &(temp->data);
            break;
        }

        temp = temp->next;
    }

    if (dataToChange != NULL) {
        char* passengerName = (char*) malloc(sizeof(char*));
        printf("Nome do passageiro: ");
        scanf("%[^\n]%*s", passengerName);
        dataToChange->passengerName = passengerName;

        int flightNumber;
        printf("Numero de voo: ");
        scanf("%d", &flightNumber);
        dataToChange->flightNumber = flightNumber;

        int seat;
        printf("Lugar: ");
        scanf("%d", &seat);
        dataToChange->seat = seat;

        double price;
        printf("Preco: ");
        scanf("%lf", &price);
        dataToChange->price = price;

        double miles;
        printf("Milhas: ");
        scanf("%lf", &miles);
        dataToChange->miles = miles;
    }
};

void printTicket(Ticket** ticket) {

    printf("\n");

    if ((*ticket) != NULL)
    {

        printf("Name: %s\n", (*ticket)->passengerName);
        printf("Cartao cidadao: %ld\n", (*ticket)->idCitizenship);
        printf("Numero de voo: %d\n", (*ticket)->flightNumber);
        printf("Lugar: %d\n", (*ticket)->seat);
        printf("Preco: %f\n", (*ticket)->price);
        printf("Milhas: %f\n", (*ticket)->miles);
    }

};

void printTickets(TicketNode** headRef) {
    TicketNode *temp = (*headRef);
    Ticket *data;

    printf("\n");

    while (temp != NULL)
    {
        data = &(temp->data);

        printf("Name: %s\n", data->passengerName);
        printf("Cartao cidadao: %ld\n", data->idCitizenship);
        printf("Numero de voo: %d\n", data->flightNumber);
        printf("Lugar: %d\n", data->seat);
        printf("Preco: %f\n", data->price);
        printf("Milhas: %f\n", data->miles);

        temp = temp->next;
    }

    free(temp);
};

void readTickets(TicketNode** tickets) {
    FILE* myFile;

    myFile = fopen(TICKET_FILE, "r");

    if (myFile == NULL)
    {
        printf("Error : Failed to open file - \n");
        exit(1);
    }


    if ((*tickets) == NULL) {
        (*tickets) = (TicketNode*) malloc(sizeof(TicketNode));
    }

    Ticket currentTicket = *(Ticket*) malloc(sizeof(Ticket));

    char* passengerName = (char*) malloc(sizeof(char));

    while(fscanf(myFile, "%[^_]_%ld_%d_%d_%lf_%lf", passengerName,
        &(currentTicket.idCitizenship),
        &(currentTicket.flightNumber),
        &(currentTicket.seat),
        &(currentTicket.price),
        &(currentTicket.miles)
        ) != EOF) {

        Ticket ticketToAdd = *(Ticket*) malloc(sizeof(Ticket));

        ticketToAdd.passengerName = (char*) malloc(sizeof(char));
        strcpy(ticketToAdd.passengerName, passengerName);
        ticketToAdd.idCitizenship = currentTicket.idCitizenship;
        ticketToAdd.flightNumber = currentTicket.flightNumber;
        ticketToAdd.seat = currentTicket.seat;
        ticketToAdd.price = currentTicket.price;
        ticketToAdd.miles = currentTicket.miles;

        addTicketOnRuntime(tickets, &ticketToAdd);

        free(passengerName);
        passengerName = (char*) malloc(sizeof(char));
    };

    fclose(myFile);
};

void saveTickets(TicketNode** tickets) {
   FILE *myFile;

    mkdir("./Resources", 0777);

    myFile = fopen(TICKET_FILE, "a");

    if(myFile == NULL) {
        perror("Not possible to open file");
        exit(1);
    }

    TicketNode *temp = (*tickets);
    Ticket *currentTicket = &(temp->data);

    if (ftell(myFile) != 0) {
        fprintf(myFile, "%s", "\n");
    }

    while (temp != NULL) {

        fprintf(myFile, LINE_TO_WRITE,
            currentTicket->passengerName,
            currentTicket->idCitizenship,
            currentTicket->flightNumber,
            currentTicket->seat,
            currentTicket->price,
            currentTicket->miles
        );

        temp = temp->next;

        if (temp != NULL) {
            fprintf(myFile, "%s", "\n");
        }

        currentTicket = &(temp->data);
    }


    fclose(myFile);
};
