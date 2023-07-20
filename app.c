#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "views.h"
#include "listaaviao.h"
#include "listaaeroporto.h"
#include "listavoos.h"
#include "listabilhete.h"

PlainNode* plainsApp = NULL;
FlightNode* flightsApp = NULL;
TicketNode* ticketsApp = NULL;
AirportNode* airportsApp = NULL;

void flightProfit();
void availablePlains();
void loadData();
void saveDataApp();
void features();
void route();
int isFuture(struct tm dateNow, struct tm dt);

void app() {
    loadData();

    features();
}

void features() {
    printf("1. Fucionalidade 3\n");
    printf("2. Fucionalidade 4\n");
    printf("3. Fucionalidade 5\n");

    int choice;
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            flightProfit();
            break;
        case 2:
            availablePlains();
            break;
        case 3:
            route();
            break;
        case 4:
            saveDataApp();
            break;
        default:
            tryAgain();
            features();
            break;
    }

    printf("Deseja ralizar outra operacao?\n");
    printf("1. Sim.\n");
    printf("2. Nao.\n");

    scanf("%d", &choice);

    switch(choice) {
        case 1:
            features();
            break;
        case 2:
            saveDataApp();
            break;
        default:
            tryAgain();
            features();
    }
}

void flightProfit() {

    const double FUEL_PER_MILE = 0.0406; //2.0709/51()
    const double AIRPORT_TAX = 5000;
    const double CREW_TAX = 400;

    Flight* flight = NULL;

    printf("Insira o numero do voo.\n");

    int flightNumb;
    scanf("%d", &flightNumb);

    getFlight(&flightsApp, &flight, flightNumb);

    if (flight != NULL) {
        Plain* plain = NULL;

        getPlain(&plainsApp, &plain, flight->plainCode);

        if (plain != NULL) {
            double ticketsValue = 0;

            TicketNode* currentTicket = ticketsApp;

            while (currentTicket != NULL)
            {
                if (flight->number == currentTicket->data.flightNumber) {
                    ticketsValue += currentTicket->data.price;
                }

                currentTicket = currentTicket->next;
            }

            time_t arriveTm = mktime(&(flight->arriveTime));
            time_t departureTm = mktime(&(flight->departureTime));

            double flightSeconds = difftime(arriveTm, departureTm);
            double flightHours = flightSeconds / 3600.0;
            double distance = plain->cruiseSpeed * flightHours;
            double totalFuel = distance * FUEL_PER_MILE + plain->seats * FUEL_PER_MILE;
            double cost = totalFuel + AIRPORT_TAX + CREW_TAX;
            double totalProfit = ticketsValue - cost;

            if (totalProfit > 0) {
                printf("O voo teve um lucro de %lf\n", totalProfit);
            } else if (totalProfit < 0) {
                double val = fabs(totalProfit);
                printf("O voo teve um prejuizo de %lf\n", val);
            } else {
                printf("Equilibrio\n");
            }
        }

    }

    printf("\n");

    pressEnter();
};

void availablePlains() {


    PlainNode *tempApp = plainsApp;
    PlainNode *availablePlains = NULL;
    FlightNode *tempFlight = flightsApp;
    TicketNode *tempTicket = ticketsApp;

    Flight *flight = NULL;
    Ticket ticket;

    printf("Numero de voo? ");

    int flightNumber;
    scanf("%d", &flightNumber);

    getFlight(&flightsApp, &flight, flightNumber);

    int flightTickets = 0;

    while (tempTicket != NULL) {
        if (tempTicket->data.flightNumber == flight->number) {
            flightTickets++;
        }

        tempTicket = tempTicket->next;
    }

    // Calcular o tempo atual
    time_t my_time;
    struct tm * timeNow;
    time (&my_time);
    timeNow = localtime (&my_time);

    int onFuture = isFuture(*timeNow, flight->departureTime); // verificar se o voo ja foi realliazdo

    while (tempApp != NULL)
    {
        Plain currentPlain = tempApp->data;

        if (onFuture == 0 && flight->plainCode != currentPlain.registrationCode && currentPlain.seats > flightTickets) {
            addPlainOnRuntime(&availablePlains, &currentPlain);
        }

        tempApp = tempApp->next;
    }

    printPlains(&availablePlains);

    pressEnter();

    free(availablePlains);
};

void route() {
    char* sourceCity = (char*) malloc(sizeof(char));

    printf("Cidade de origem");
};

void loadData() {
    readPlains(&plainsApp);
    readAirports(&airportsApp);
    readFlights(&flightsApp);
    readTickets(&ticketsApp);
}

void saveDataApp() {
    savePlains(&plainsApp);
    saveAirports(&airportsApp);
    saveFlights(&flightsApp);
    saveTickets(&ticketsApp);
}

int isFuture(struct tm dateNow, struct tm dt) {
    int currentYear = dateNow.tm_year + 1900;

    // Quando retornar 0 é para voos que ainda nao foram realizados e retorna 1 para voos ja realizados

    if (currentYear > dt.tm_year) {
        return 1;
    } else if (currentYear < dt.tm_year) {
        return 0;
    }

    if (dateNow.tm_mon > dt.tm_mon) {
        return 1;
    } else if (dateNow.tm_mon < dt.tm_mon) {
        return 0;
    }

    if (dateNow.tm_yday > dt.tm_yday) {
        return 1;
    } else if (dateNow.tm_yday < dt.tm_yday) {
        return 0;
    }

    if (dateNow.tm_hour > dt.tm_hour) {
        return 1;
    } else if (dateNow.tm_hour < dt.tm_hour) {
        return 0;
    }

    if (dateNow.tm_min > dt.tm_min) {
        return 1;
    } else if (dateNow.tm_min < dt.tm_min) {
        return 0;
    }

    return 0;
}
