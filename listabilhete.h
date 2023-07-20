typedef struct myTicket
{
    char* passengerName;
    long idCitizenship;
    int flightNumber;
    int seat;
    double price;
    double miles;
} Ticket;

typedef struct myTicketNode
{
    Ticket data;
    struct myTicketNode *next;
} TicketNode;

void addTicket(TicketNode** headRef);

void addTicketOnRuntime(TicketNode** headRef, Ticket* newData);

void removeTicket(TicketNode** headRef, long idCitizenship);

void getTicket(TicketNode** headRef, Ticket** dataToGet, long idCitizenship);

void changeTicket(TicketNode** headRef);

void printTickets(TicketNode** headRef);

void readTickets(TicketNode** Tickets);

void saveTickets(TicketNode** Tickets);