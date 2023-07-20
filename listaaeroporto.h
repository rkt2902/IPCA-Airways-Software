typedef struct myAirport
{
    char* iataCode;
    char* name;
    char* city;
    double height;
} Airport;

typedef struct myAirportNode
{
    Airport data;
    struct myAirportNode *next;
} AirportNode;

void addAirport(AirportNode** headRef);

void addAirportOnRuntime(AirportNode** headRef, Airport* newData);

void removeAirport(AirportNode** headRef, char iataCode[3]);

void getAirport(AirportNode** headRef, Airport** dataToGet, char iataCode[3]);

void changeAirport(AirportNode** headRef);

void printAirport(Airport** airport);

void printAirports(AirportNode** headRef);

void readAirports(AirportNode** Airports);

void saveAirports(AirportNode** Airports);