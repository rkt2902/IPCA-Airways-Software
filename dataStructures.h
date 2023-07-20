
#include <time.h>

typedef struct myFlight
{
    int number;
    time_t departureTime;
    time_t arriveTime;
    char* sourceAirportName;
    char* destinationAirportName;
    int plainRegistrationCode;
} Flight;

typedef struct myTicket
{
    char* passengerName;
    long idCitizenship;
    int flightNumber;
    int seat;
    double price;
    double miles;
} Ticket;