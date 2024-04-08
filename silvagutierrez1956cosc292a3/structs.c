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


