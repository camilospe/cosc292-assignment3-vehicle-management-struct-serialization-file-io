#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdio.h>

typedef unsigned char BYTE;

#define VIN_SIZE	18
#define MAKE_SIZE	25
#define MODEL_SIZE	25

typedef struct
{
	// All char arrays are null-terminated strings.
	BYTE VIN[VIN_SIZE];
	BYTE Make[MAKE_SIZE];
	BYTE Model[MODEL_SIZE];
	BYTE* Description;
}Vehicle;

typedef struct
{
	Vehicle** Vehicles;
	unsigned short NumVehicles;
}Garage;

Vehicle* createVehicle(BYTE bVin[], BYTE bMake[], BYTE bModel[], BYTE* bDescription);
void addVehicleToGarage(Garage* g, Vehicle* vPtr);
void displayVehicle(Vehicle v);
void displayGarage(Garage g);
BYTE* serializeVehicle(Vehicle* vPtr);
void writeGarageToFile(Garage g, FILE* filePtr);
void readGarageFromFile(Garage* g, FILE* filePtr);

#endif // !STRUCTS_H
