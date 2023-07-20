typedef struct myPlain
{
    int registrationCode;
    char* brand;
    char* model;
    int seats;
    double cruiseSpeed;
    double fuelPerMile;
} Plain;

typedef struct myPlainNode
{
    Plain data;
    struct myPlainNode *next;
} PlainNode;

void addPlain(PlainNode** headRef);

void addPlainOnRuntime(PlainNode** headRef, Plain* newData);

void removePlain(PlainNode** headRef, int registrationCode);

void getPlain(PlainNode** headRef, Plain** plainToGet, int registrationCode);

void changePlain(PlainNode** headRef);

void printPlain(Plain** plain);

void printPlains(PlainNode** headRef);

void readPlains(PlainNode** plains);

void savePlains(PlainNode** plains);