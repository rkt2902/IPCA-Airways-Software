#include <time.h>
#include "utils.h"

typedef struct myFlight
{
    int number;
    struct tm departureTime;
    struct tm arriveTime;
    char* source;
    char* destination;
    int plainCode;
} Flight;

typedef struct myFlightNode
{
    Flight data;
    struct myFlightNode *next;
} FlightNode;

void addFlight(FlightNode** headRef);

void addFlightOnRuntime(FlightNode** headRef, Flight* newData);

void removeFlight(FlightNode** headRef, int number);

void getFlight(FlightNode** headRef, Flight** dataToGet, int number);

void changeFlight(FlightNode** headRef);

void printFlight(Flight** flight);

void printFlights(FlightNode** headRef);

void readFlights(FlightNode** flights);

void saveFlights(FlightNode** flights);