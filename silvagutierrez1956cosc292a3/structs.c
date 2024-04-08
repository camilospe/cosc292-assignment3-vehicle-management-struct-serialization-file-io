#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <crtdbg.h>
#include <string.h> 
#include "structs.h"

/// <summary>
/// Dynamically allocates and initializes a Vehicle structure with the provided attributes.
/// Each string parameter (bVin, bMake, bModel, bDescription) must be null-terminated.
/// The VIN, Make, and Model sizes include the null terminator, thus allowing for 17, 24, and 24 characters respectively.
/// </summary>
/// <param name="bVin">: null terminated char array with the VIN of the vehicle (17 bytes + 1) </param>
/// <param name="bMake">: null terminated char array with the make of the vehicle (24 bytes + 1)</param>
/// <param name="bModel">: null terminated char array with the model of the vehicle (24 bytes + 1) </param>
/// <param name="bDescription">: null terminated string with the description of the vehicle</param>
/// <returns></returns>
Vehicle* createVehicle(BYTE bVin[], BYTE bMake[], BYTE bModel[], BYTE* bDescription)
{
	//Create a pointer and allocating the space in the heap
	Vehicle* vPtr = NULL;
	vPtr = (Vehicle*)malloc(sizeof(Vehicle));

	if (vPtr != NULL)
	{
		//Allocate the values given 

		strcpy_s(vPtr->VIN, 18, bVin);
		strcpy_s(vPtr->Make, 25, bMake);
		strcpy_s(vPtr->Model, 25, bModel);

		//Because the description is a pointer  we allocate the space for the description and then the value

		vPtr->Description = (BYTE*)malloc((strlen((char*)bDescription) + 1) * sizeof(BYTE));
		strcpy_s(vPtr->Description, strlen((char*)bDescription) + 1, bDescription );
	}
	return vPtr;
}


/// <summary>
/// This function will display the different parameters of a vehicle to the console
/// </summary>
/// <param name="v">vehicle struct to be displayed (not a pointer)</param>
void displayVehicle(Vehicle v)
{
	printf("VIN: %s\n", v.VIN );
	printf("Make: %s\n", v.Make);
	printf("Model: %s\n", v.Model);
	printf("%s\n", v.Description);
}

/// <summary>
/// This function will add a vehicle pointer to a struct called garage
/// </summary>
/// <param name="g">pointer to the garage struct, this struct stores an array of vehicles pointers</param>
/// <param name="vPtr">pointer to a vehicle</param>
void addVehicleToGarage(Garage* g, Vehicle* vPtr)
{
    // Check if this is the first vehicle being added
    if (g->NumVehicles == 0)
    {
        // Allocate memory for one vehicle pointer
        g->Vehicles = (Vehicle**)malloc(sizeof(Vehicle*));
    }
    else
    {
        // Reallocate the Vehicles array to fit one more Vehicle*
        g->Vehicles = (Vehicle**)realloc(g->Vehicles, (g->NumVehicles + 1) * sizeof(Vehicle*));
    }
    // Check if the memory allocation (or reallocation) was successful
    if (g->Vehicles != NULL)
    {
        // Add the new vehicle pointer to the array
        g->Vehicles[g->NumVehicles] = vPtr;

        // Increment the number of vehicles in the garage
        g->NumVehicles += 1;
    }
    else
    {
        // Handle memory allocation failure; in a real application, you might want to log this or exit
        printf("Failed to allocate memory for a new vehicle in the garage.\n");
    }

}