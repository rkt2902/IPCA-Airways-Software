#include "listaaviao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

       int mkdir(const char *pathname, mode_t mode);

#define PLAIN_FILE "./Resources/plains.txt"
#define LINE_TO_WRITE "%d_%s_%s_%d_%lf_%lf"

void
addPlain(PlainNode** headRef) {
    PlainNode *newNode = (PlainNode*) malloc(sizeof(PlainNode));
    PlainNode *lastNode = (*headRef);

    Plain *newPlain = (Plain*) malloc(sizeof(Plain));

    int registrationCode;
    printf("Codigo: ");
    scanf("%d", &registrationCode);
    newPlain->registrationCode = registrationCode;

    char* brand = (char*) malloc(sizeof(char*));
    printf("Marca: ");
    scanf("%s", brand);
    newPlain->brand = brand;

    char* md = (char*) malloc(sizeof(char*));
    printf("Modelo: ");
    scanf("%s", md);
    newPlain->model = md;

    int seats;
    printf("Numero de lugares: ");
    scanf("%d", &seats);
    newPlain->seats = seats;

    double cruiseSpeed;
    printf("Velocidade cruzeiro: ");
    scanf("%lf", &cruiseSpeed);
    newPlain->cruiseSpeed = cruiseSpeed;

    double fuelPerMile;
    printf("Comb por milha: ");
    scanf("%lf", &fuelPerMile);
    newPlain->fuelPerMile = fuelPerMile;

    newNode->data = (*newPlain);

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

void addPlainOnRuntime(PlainNode** headRef, Plain* newData) {
    PlainNode *newNode = (PlainNode*) malloc(sizeof(PlainNode));
    PlainNode *lastNode = (*headRef);

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


void removePlain(PlainNode** headRef, int registrationCode) {
    PlainNode *temp = (*headRef), *prev;
    Plain plainToDelete = temp->data;

    if (temp != NULL && plainToDelete.registrationCode == registrationCode) {
        (*headRef) = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data.registrationCode != registrationCode) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return;
    }

    prev->next = temp->next;

    free(temp);
};

void getPlain(PlainNode** headRef, Plain** dataToGet, int registrationCode) {
    PlainNode *temp = (*headRef);

    if ((*headRef) == NULL) {
        return;
    }

    while (temp != NULL) {
        if (temp->data.registrationCode == registrationCode) {
            (*dataToGet) = &(temp->data);
            break;
        }

        temp = temp->next;
    }

    free(temp);
};

void changePlain(PlainNode** headRef) {
    PlainNode *temp = (*headRef);
    Plain *dataToChange = NULL;

    printf("Codigo do aviao que pretende alterar. \n");

    int registrationCode;
    scanf("%d", &registrationCode);

    if ((*headRef) == NULL) {
        return;
    }

    while (temp != NULL) {

        if (temp->data.registrationCode == registrationCode) {
            dataToChange = &(temp->data);
            break;
        }

        temp = temp->next;
    }

    if (dataToChange != NULL) {
        char* brand = (char*) malloc(sizeof(char*));
        printf("Marca: ");
        scanf("%s", brand);
        dataToChange->brand = brand;

        char* md = (char*) malloc(sizeof(char*));
        printf("Modelo: ");
        scanf("%s", md);
        dataToChange->model = md;

        int seats;
        printf("Numero de lugares: ");
        scanf("%d", &seats);
        dataToChange->seats = seats;

        double cruiseSpeed;
        printf("Velocidade cruzeiro: ");
        scanf("%lf", &cruiseSpeed);
        dataToChange->cruiseSpeed = cruiseSpeed;

        double fuelPerMile;
        printf("Comb por milha: ");
        scanf("%lf", &fuelPerMile);
        dataToChange->fuelPerMile = fuelPerMile;
    }
};

void printPlain(Plain** plain) {
    if ((*plain) != NULL)
    {

        printf("Registration code: %d\n", (*plain)->registrationCode);
        printf("Brand: %s\n", (*plain)->brand);
        printf("Model: %s\n", (*plain)->model);
        printf("Seats %d\n", (*plain)->seats);
        printf("Cruise speed: %f\n", (*plain)->cruiseSpeed);

    }
};

void printPlains(PlainNode** headRef) {
    PlainNode *temp = *headRef;
    Plain *data;

    printf("\n");

    while (temp != NULL)
    {
        data = &(temp->data);

        printf("Registration code: %d\n", data->registrationCode);
        printf("Brand: %s\n", data->brand);
        printf("Model: %s\n", data->model);
        printf("Seats %d\n", data->seats);
        printf("Cruise speed: %f\n", data->cruiseSpeed);

        temp = temp->next;
    }

    free(temp);
}

void savePlains(PlainNode** plains) {
    FILE *myFile;

    mkdir("./Resources", 0777);

    myFile = fopen(PLAIN_FILE, "a");

    if(myFile == NULL) {
        perror("Not possible to open file");
        exit(1);
    }

    PlainNode *temp = (*plains);
    Plain *currentPlain = &(temp->data);

    if (ftell(myFile) != 0) {
        fprintf(myFile, "%s", "\n");
    }

    while (temp != NULL) {

        fprintf(myFile, LINE_TO_WRITE,
            currentPlain->registrationCode,
            currentPlain->brand,
            currentPlain->model,
            currentPlain->seats,
            currentPlain->cruiseSpeed,
            currentPlain->fuelPerMile
        );

        temp = temp->next;

        if (temp != NULL) {
            fprintf(myFile, "%s", "\n");
        }

        currentPlain = &(temp->data);
    }


    fclose(myFile);
};

void readPlains(PlainNode** plains) {
    FILE* myFile;

    myFile = fopen(PLAIN_FILE, "r");

    if (myFile == NULL)
    {
        printf("Error : Failed to open file - \n");
        exit(1);
    }


    if ((*plains) == NULL) {
        (*plains) = (PlainNode*) malloc(sizeof(PlainNode));
    }

    Plain currentPlain = *(Plain*) malloc(sizeof(Plain));

    char* brand = (char*) malloc(sizeof(char));
    char* model = (char*) malloc(sizeof(char));

    while(fscanf(myFile, "%d_%[^_]_%[^_]_%d_%lf_%lf", &(currentPlain.registrationCode),
        brand,
        model,
        &(currentPlain.seats),
        &(currentPlain.cruiseSpeed),
        &(currentPlain.fuelPerMile)
        ) != EOF) {

        Plain plainToAdd = *(Plain*) malloc(sizeof(Plain));

        plainToAdd.registrationCode = currentPlain.registrationCode;
        plainToAdd.brand = (char*) malloc(sizeof(char));
        plainToAdd.model = (char*) malloc(sizeof(char));
        strcpy(plainToAdd.brand, brand);
        strcpy(plainToAdd.model, model);
        plainToAdd.seats = currentPlain.seats;
        plainToAdd.cruiseSpeed = currentPlain.cruiseSpeed;
        plainToAdd.fuelPerMile = currentPlain.fuelPerMile;

        addPlainOnRuntime(plains, &plainToAdd);

        free(brand);
        free(model);
        brand = (char*) malloc(sizeof(char));
        model = (char*) malloc(sizeof(char));
    };

    fclose(myFile);
};
