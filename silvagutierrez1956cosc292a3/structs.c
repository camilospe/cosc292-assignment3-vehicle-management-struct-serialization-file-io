#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <crtdbg.h>
#include <string.h> 
#include "structs.h"
#include "fileio.h"

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


/// <summary>
/// This function will display to the console the content of all vehicles in the pointer array
/// </summary>
/// <param name="g">Garage struct containing an array of pointers to vehicles and a counter of vehicles. </param>
void displayGarage(Garage g)
{
    printf("There are %d vehicles\n", g.NumVehicles);
    for (size_t i = 0; i < g.NumVehicles; i++) {

        // grab the vehicle from the array 
        Vehicle* currentVehicle = g.Vehicles[i]; 

        //print the values
        printf("VIN: %s\n", currentVehicle->VIN);
        printf("Make: %s\n", currentVehicle->Make);
        printf("Model: %s\n", currentVehicle->Model);
        printf("Description: %s\n\n", currentVehicle->Description); 
    }
}


/// <summary>
/// This function will serialize a vehicle struc so it can be passed through a network or a file
/// </summary>
/// <param name="vPtr">pointer to a vehicle</param>
/// <returns>pointer to a serialized vehicle</returns>
BYTE* serializeVehicle(Vehicle* vPtr)
{
    //get the size of the description
    int nSize = strlen(vPtr->Description);

    int totalSize = nSize + 1 + 18 + 25 + 25 + 4;// description + null terminator + Vin + Make + Model + int for size of description


    BYTE* serializedVehicle = (BYTE*)malloc(totalSize * sizeof(BYTE));

    BYTE* svPtr = serializedVehicle;

    //we add everyvalue to the memory and move the pointer to the new location
    memcpy(svPtr, vPtr->VIN, VIN_SIZE);
    svPtr += VIN_SIZE;
    memcpy(svPtr, vPtr->Make, MAKE_SIZE);
    svPtr += MAKE_SIZE;
    memcpy(svPtr, vPtr->Model, MODEL_SIZE);
    svPtr += MODEL_SIZE;
    memcpy(svPtr,&nSize,sizeof(int));
    svPtr += sizeof(int);
    memcpy(svPtr, vPtr->Description, nSize + 1);

    //return the original pointer that wasnt moved
    return serializedVehicle;
}

/// <summary>
/// This function loops through a garage, serializes each vehicle, and prints them to the file.
/// </summary>
/// <param name="g">The garage to loop through.</param>
/// <param name="filePtr">Pointer to an open file.</param>
void writeGarageToFile(Garage g, FILE* filePtr)
{
    //we write the number of vehicles.
    writeFile(filePtr, &(g.NumVehicles), 2*sizeof(char));

    for (size_t i = 0; i < g.NumVehicles; i++)
    {
        // grab the vehicle from the array 
        Vehicle* currentVehicle = g.Vehicles[i];

        //serialize the vehicle

        BYTE* currentSVehicle = serializeVehicle(currentVehicle);

        // Calculate the size of the serialized vehicle dynamically
        int descriptionLength = strlen(currentVehicle->Description);
        int totalSize = VIN_SIZE + MAKE_SIZE + MODEL_SIZE + sizeof(int) + descriptionLength + 1; // +1 for null terminator of the description

        writeFile(filePtr, currentSVehicle, totalSize);
    }
}



/// <summary>
/// This function is meant to read an open file consisting of a serialized garage
/// the function will both save the vehicles to the garage and print them to console
/// </summary>
/// <param name="g"></param>
/// <param name="filePtr"></param>
void readGarageFromFile(Garage* g, FILE* filePtr)
{
    short numVehicles;
    // Read 2 bytes from the file
    size_t bytesRead = fread(&numVehicles, sizeof(short), 1, filePtr);
    if (bytesRead == 1) {
        // Successfully read the number, print it
        printf("Number of vehicles: %d\n", numVehicles);
        //loop for each vehicle

        for (size_t i = 0; i < numVehicles; i++)
        {

            BYTE bVin[VIN_SIZE];
            BYTE bMake[MAKE_SIZE];
            BYTE bModel[MODEL_SIZE];
            int descriptionLenght;

            // get the values from the file
            readFile(filePtr, bVin, VIN_SIZE);
            readFile(filePtr, bMake, MAKE_SIZE);
            readFile(filePtr, bModel, MODEL_SIZE);
            readFile(filePtr, &descriptionLenght, 4);

            //print the values because why not
            printf("VIN: %s\n", bVin);
            printf("Make: %s\n", bMake);
            printf("Model: %s\n", bModel);
            printf("lenght: %d\n", descriptionLenght);

            //get the description
            char* description = (char*)malloc((descriptionLenght + 1) * sizeof(char));
            readFile(filePtr, description, descriptionLenght + 1);
            printf("%s\n\n", description);
            Vehicle* vehicle = createVehicle(bVin, bMake, bModel, description);

            addVehicleToGarage(g, vehicle);

            free(description);
        }
    }
    else {
        if (feof(filePtr)) {
            fprintf(stderr, "Unexpected end of file\n");

        }
        else if (ferror(filePtr)) {
            fprintf(stderr, "Error reading file\n");
        }
    }
}