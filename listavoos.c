#include "listavoos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
int mkdir(const char *pathname, mode_t mode);
#define FLIGHT_FILE "./Resources/flights.txt"
#define LINE_TO_WRITE "%d_%d/%d/%d_%d:%d_%d/%d/%d_%d:%d_%s_%s_%d"

void addFlight(FlightNode** headRef) {
    FlightNode *newNode = (FlightNode*) malloc(sizeof(FlightNode));
    FlightNode *lastNode = (*headRef);

    Flight *newFlight = (Flight*) malloc(sizeof(Flight));

    int number;
    printf("Numero do voo: ");
    scanf("%d", &number);
    newFlight->number = number;

    time_t departureTime = (time_t) malloc(sizeof(time_t));
    int day;
    int month;
    int year;
    int hour;
    int minutes;

    printf("Hora de partida: ");
    scanf("%d/%d/%d %d:%d", &day, &month, &year, &hour, &minutes);
    newFlight->departureTime.tm_yday = day;
    newFlight->departureTime.tm_mon = month;
    newFlight->departureTime.tm_year = year;
    newFlight->departureTime.tm_hour = hour;
    newFlight->departureTime.tm_min = minutes;

    printf("Hora de chegada: ");
    scanf("%d/%d/%d %d:%d", &day, &month, &year, &hour, &minutes);
    newFlight->arriveTime.tm_yday = day;
    newFlight->arriveTime.tm_mon = month;
    newFlight->arriveTime.tm_year = year;
    newFlight->arriveTime.tm_hour = hour;
    newFlight->arriveTime.tm_min = minutes;

    char* source = (char*) malloc(sizeof(char));
    printf("Procede de: ");
    scanf("%s", source);
    newFlight->source = source;

    char* destination = (char*) malloc(sizeof(char));
    printf("Destino: ");
    scanf("%s", destination);
    newFlight->destination = destination;

    int plainCode;
    printf("Codigo aviao: ");
    scanf("%d", &plainCode);
    newFlight->plainCode = plainCode;

    newNode->data = (*newFlight);

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

void addFlightOnRuntime(FlightNode** headRef, Flight* newData) {
    FlightNode *newNode = (FlightNode*) malloc(sizeof(FlightNode));
    FlightNode *lastNode = (*headRef);

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
}

void removeFlight(FlightNode** headRef, int number) {
    FlightNode *temp = *headRef, *prev;

    if (temp != NULL && temp->data.number == number) {
        *headRef = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data.number != number) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return;
    }

    prev->next = temp->next;

    free(temp);
};

void getFlight(FlightNode** headRef, Flight** dataToGet, int number) {
    FlightNode *temp = (*headRef);

    if ((*headRef) == NULL) {
        return;
    }

    while (temp != NULL) {

        if (temp->data.number == number) {
            (*dataToGet) = &(temp->data);
            break;
        }

        temp = temp->next;
    }
};

void changeFlight(FlightNode** headRef) {
    FlightNode *temp = (*headRef);
    Flight *dataToChange = NULL;

    printf("Codigo do voo que pretende remover.\n");

    int number;
    scanf("%d", &number);

    if ((*headRef) == NULL) {
        return;
    }

    while (temp != NULL) {

        if (temp->data.number == number) {
            dataToChange = &(temp->data);
            break;
        }

        temp = temp->next;
    }

    if (dataToChange != NULL) {
        time_t departureTime = (time_t) malloc(sizeof(time_t));
        int day;
        int month;
        int year;
        int hour;
        int minutes;

        printf("Hora de partida: ");
        scanf("%d/%d/%d %d:%d", &day, &month, &year, &hour, &minutes);
        dataToChange->departureTime.tm_yday = day;
        dataToChange->departureTime.tm_mon = month;
        dataToChange->departureTime.tm_year = year;
        dataToChange->departureTime.tm_hour = hour;
        dataToChange->departureTime.tm_min = minutes;

        printf("Hora de chegada: ");
        scanf("%d/%d/%d %d:%d", &day, &month, &year, &hour, &minutes);
        dataToChange->arriveTime.tm_yday = day;
        dataToChange->arriveTime.tm_mon = month;
        dataToChange->arriveTime.tm_year = year;
        dataToChange->arriveTime.tm_hour = hour;
        dataToChange->arriveTime.tm_min = minutes;

        char* source = (char*) malloc(sizeof(char));
        printf("Procede de: ");
        scanf("%s", source);
        dataToChange->source = source;

        char* destination = (char*) malloc(sizeof(char));
        printf("Destino: ");
        scanf("%s", destination);
        dataToChange->destination = destination;

        int plainCode;
        printf("Codigo aviao: ");
        scanf("%d", &plainCode);
        dataToChange->plainCode = plainCode;
    }

};

void printFlight(Flight** flight) {

    if ((*flight) != NULL)
    {

        printf("Numero do voo: %d\n", (*flight)->number);
        printf("Hora de partida: %d/%d/%d %d:%d\n", (*flight)->departureTime.tm_yday,
            (*flight)->departureTime.tm_yday,
            (*flight)->departureTime.tm_mon,
            (*flight)->departureTime.tm_year,
            (*flight)->departureTime.tm_hour,
            (*flight)->departureTime.tm_min);
        printf("Hora de chegada: %d/%d/%d %d:%d\n", (*flight)->arriveTime.tm_yday,
            (*flight)->arriveTime.tm_yday,
            (*flight)->arriveTime.tm_mon,
            (*flight)->arriveTime.tm_year,
            (*flight)->arriveTime.tm_hour,
            (*flight)->arriveTime.tm_min);
        printf("Procede de: %s\n", (*flight)->source);
        printf("Destino: %s\n", (*flight)->destination);
        printf("Codigo do aviao: %d\n", (*flight)->plainCode);
    }
};

void printFlights(FlightNode** headRef) {
    FlightNode *temp = (*headRef);
    Flight *data;

    printf("\n");

    while (temp != NULL)
    {
        data = &(temp->data);

        printf("Numero do voo: %d\n", data->number);
        printf("Hora de partida: %d/%d/%d %d:%d\n", data->departureTime.tm_yday,
            data->departureTime.tm_yday,
            data->departureTime.tm_mon,
            data->departureTime.tm_year,
            data->departureTime.tm_hour,
            data->departureTime.tm_min);
        printf("Hora de chegada: %d/%d/%d %d:%d\n", data->arriveTime.tm_yday,
            data->arriveTime.tm_yday,
            data->arriveTime.tm_mon,
            data->arriveTime.tm_year,
            data->arriveTime.tm_hour,
            data->arriveTime.tm_min);
        printf("Procede de: %s\n", data->source);
        printf("Destino: %s\n", data->destination);
        printf("Codigo do aviao: %d\n", data->plainCode);

        temp = temp->next;
    }

    free(temp);
};

void readFlights(FlightNode** flights) {
    FILE* myFile;

    myFile = fopen(FLIGHT_FILE, "r");

    if (myFile == NULL)
    {
        printf("Error : Failed to open file - \n");
        exit(1);
    }


    if ((*flights) == NULL) {
        (*flights) = (FlightNode*) malloc(sizeof(FlightNode));
    }

    Flight currentFlight = *(Flight*) malloc(sizeof(Flight));

    char* source = (char*) malloc(sizeof(char));
    char* destination = (char*) malloc(sizeof(char));

    while(fscanf(myFile, "%d_%d/%d/%d_%d:%d_%d/%d/%d_%d:%d_%[^_]_%[^_]_%d", &(currentFlight.number),
        &(currentFlight.departureTime.tm_yday), &(currentFlight.departureTime.tm_mon), &(currentFlight.departureTime.tm_year), &(currentFlight.departureTime.tm_hour), &(currentFlight.departureTime.tm_min),
        &(currentFlight.arriveTime.tm_yday), &(currentFlight.arriveTime.tm_mon), &(currentFlight.arriveTime.tm_year), &(currentFlight.arriveTime.tm_hour), &(currentFlight.arriveTime.tm_min),
        source, destination, &(currentFlight.plainCode)) != EOF) {

        Flight flightToAdd = *(Flight*) malloc(sizeof(Flight));

        flightToAdd.number = currentFlight.number;
        flightToAdd.departureTime = currentFlight.departureTime;
        flightToAdd.arriveTime = currentFlight.arriveTime;
        flightToAdd.source = (char*) malloc(sizeof(char));
        flightToAdd.destination = (char*) malloc(sizeof(char));
        strcpy(flightToAdd.source, source);
        strcpy(flightToAdd.destination, destination);
        flightToAdd.plainCode = currentFlight.plainCode;

        addFlightOnRuntime(flights, &flightToAdd);

        free(destination);
        free(source);

        source = malloc(sizeof(char));
        destination = malloc(sizeof(char));
    };

    fclose(myFile);
};

void saveFlights(FlightNode** flights) {
    FILE *myFile;

    mkdir("./Resources", 0777);

    myFile = fopen(FLIGHT_FILE, "a");

    if(myFile == NULL) {
        perror("Not possible to open file");
        exit(1);
    }

    FlightNode *temp = (*flights);
    Flight *currentFlight = &(temp->data);
    currentFlight->departureTime = temp->data.departureTime;
    currentFlight->arriveTime = temp->data.arriveTime;

    if (ftell(myFile) != 0) {
        fprintf(myFile, "%s", "\n");
    }

    while (temp != NULL) {

        fprintf(myFile, LINE_TO_WRITE, currentFlight->number,
        currentFlight->departureTime.tm_yday, currentFlight->departureTime.tm_mon, currentFlight->departureTime.tm_year, currentFlight->departureTime.tm_hour, currentFlight->departureTime.tm_min,
        currentFlight->arriveTime.tm_yday, currentFlight->arriveTime.tm_mon, currentFlight->arriveTime.tm_year, currentFlight->arriveTime.tm_hour, currentFlight->arriveTime.tm_min,
        currentFlight->source, currentFlight->destination, currentFlight->plainCode);

        temp = temp->next;

        if (temp != NULL) {
            fprintf(myFile, "%s", "\n");
        }

        currentFlight = &(temp->data);
        currentFlight->departureTime = temp->data.departureTime;
        currentFlight->arriveTime = temp->data.arriveTime;
    }


    fclose(myFile);
};
