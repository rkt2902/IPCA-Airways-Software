#include "listaaeroporto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
int mkdir(const char *pathname, mode_t mode);
#define AIRPORT_FILE "./Resources/airports.txt"
#define LINE_TO_WRITE "%s_%s_%s_%lf"

void addAirport(AirportNode** headRef) {
    AirportNode *newNode = (AirportNode*) malloc(sizeof(AirportNode));
    AirportNode *lastNode = (*headRef);

    Airport *newAirport = (Airport*) malloc(sizeof(Airport));

    char* iataCode = (char*) malloc(sizeof(char));
    printf("Codigo iata: ");
    scanf("%s", iataCode);
    newAirport->iataCode = iataCode;

    char* city = (char*) malloc(sizeof(char));
    printf("Cidade: ");
    scanf(" %[^\t\n]s", city);
    newAirport->city = city;

    char* name=  (char*) malloc(sizeof(char));
    printf("Nome: ");
    scanf(" %[^\t\n]s", name);
    newAirport->name= name;

    double height;
    printf("Peso: ");
    scanf("%lf", &height);
    newAirport->height = height;

    newNode->data = (*newAirport);

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

void addAirportOnRuntime(AirportNode** headRef, Airport* newData) {
    AirportNode *newNode = (AirportNode*) malloc(sizeof(AirportNode));
    AirportNode *lastNode = (*headRef);

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

void removeAirport(AirportNode** headRef, char iataCode[3]) {
    AirportNode *temp = *headRef, *prev;

    if (temp != NULL && strcmp(temp->data.iataCode, iataCode) == 0) {
        *headRef = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && strcmp(temp->data.iataCode, iataCode) == 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return;
    }

    prev->next = temp->next;

    free(temp);
};

void getAirport(AirportNode** headRef, Airport** dataToGet, char iataCode[3]) {
    AirportNode *temp = (*headRef);

    if ((*headRef) == NULL) {
        return;
    }

    while (temp != NULL) {
        if (strcmp(temp->data.iataCode, iataCode) == 0) {
            (*dataToGet) = &(temp->data);
            break;
        }

        temp = temp->next;
    }
};

void changeAirport(AirportNode** headRef) {
    AirportNode *temp = (*headRef);
    Airport *dataToChange = NULL;

    printf("Codigo do aeroporto que pretende remover.\n");

    char iataCode[3];
    scanf("%s", iataCode);

    if ((*headRef) == NULL) {
        return;
    }

    while (temp != NULL) {

        if (strcmp(temp->data.iataCode,iataCode) == 0) {
            dataToChange = &(temp->data);
            break;
        }

        temp = temp->next;
    }

    if (dataToChange != NULL) {

        char* city = (char*) malloc(sizeof(char));
        printf("Cidade: ");
        scanf(" %[^\t\n]s", city);
        dataToChange->city = city;

        char* name=  (char*) malloc(sizeof(char));
        printf("Nome: ");
        scanf(" %[^\t\n]s", name);
        dataToChange->name= name;

        double height;
        printf("Peso: ");
        scanf("%lf", &height);
        dataToChange->height = height;
    }
};

void printAirport(Airport** airport) {

    if ((*airport) != NULL)
    {
        printf("Codigo iata: %s\n", (*airport)->iataCode);
        printf("Cidade: %s\n", (*airport)->city);
        printf("Nome: %s\n", (*airport)->name);
        printf("Peso %f\n", (*airport)->height);
    }

}

void printAirports(AirportNode** headRef) {
    AirportNode *temp = (*headRef);
    Airport *data;

    printf("\n");

    while (temp != NULL)
    {
        data = &(temp->data);

        printf("Codigo iata: %s\n", data->iataCode);
        printf("Cidade: %s\n", data->city);
        printf("Nome: %s\n", data->name);
        printf("Peso %f\n", data->height);

        temp = temp->next;
    }

    free(temp);
}

void readAirports(AirportNode** Airports) {
    FILE* myFile;

    myFile = fopen(AIRPORT_FILE, "r");

    if (myFile == NULL)
    {
        printf("Error : Failed to open file - \n");
        exit(1);
    }


    if ((*Airports) == NULL) {
        (*Airports) = (AirportNode*) malloc(sizeof(AirportNode));
    }

    char* iataCode = (char*) malloc(sizeof(char));
    char* name = (char*) malloc(sizeof(char));
    char* city = (char*) malloc(sizeof(char));
    double height;

    while(fscanf(myFile, "%[^_]_%[^_]_%[^_]_%lf",
        iataCode,
        name,
        city,
        &height
        ) != EOF) {

        Airport airportToAdd = *(Airport*) malloc(sizeof(Airport));

        airportToAdd.iataCode = malloc(sizeof(char));
        strcpy(airportToAdd.iataCode, iataCode);
        airportToAdd.name = malloc(sizeof(char));
        strcpy(airportToAdd.name, name);
        airportToAdd.city = malloc(sizeof(char));
        strcpy(airportToAdd.city, city);
        airportToAdd.height = height;

        addAirportOnRuntime(Airports, &airportToAdd);

        free(iataCode);
        free(name);
        free(city);

        iataCode = (char*) malloc(sizeof(char));
        name = (char*) malloc(sizeof(char));
        city = (char*) malloc(sizeof(char));
    };

    free(iataCode);
    free(name);
    free(city);

    fclose(myFile);
};

void saveAirports(AirportNode** Airports) {
  FILE *myFile;

    mkdir("./Resources", 0777);

    myFile = fopen(AIRPORT_FILE, "a");

    if(myFile == NULL) {
        perror("Not possible to open file");
        exit(1);
    }

    AirportNode *temp = (*Airports);
    Airport *currentAirport = &(temp->data);

    if (ftell(myFile) != 0) {
        fprintf(myFile, "%s", "\n");
    }

    while (temp != NULL) {

        fprintf(myFile, LINE_TO_WRITE,
            currentAirport->iataCode,
            currentAirport->city,
            currentAirport->name,
            currentAirport->height
        );

        temp = temp->next;

        if (temp != NULL) {
            fprintf(myFile, "%s", "\n");
        }

        currentAirport = &(temp->data);
    }


    fclose(myFile);
};
