#include <stdio.h>
#include "structs.h"
#define MAX_DESCRIPTION	255

void enterVehicles(Garage* g)
{
	BYTE bVin[VIN_SIZE];
	BYTE bMake[MAKE_SIZE];
	BYTE bModel[MODEL_SIZE];
	BYTE bDescription[MAX_DESCRIPTION];

	for (int i = 0; i < 3; i++)
	{
		printf("Enter a VIN: ");
		gets_s(bVin, VIN_SIZE);
		printf("Enter a make: ");
		gets_s(bMake, MAKE_SIZE);
		printf("Enter a model: ");
		gets_s(bModel, MODEL_SIZE);
		printf("Enter a description: ");
		gets_s(bDescription, MAX_DESCRIPTION);

		Vehicle* temp = createVehicle(bVin, bMake, bModel, bDescription);
		addVehicleToGarage(g, temp);
	}
}
void testCreateAndDisplayVehicle() {
    // Initial car for setup
    BYTE vin1[] = "1234567";
    BYTE make1[] = "Toyota";
    BYTE model1[] = "Corolla";
    BYTE description1[] = "A specific car.";

    Garage g = { NULL, 0 };

    // Array of famous cars
    BYTE* vins[] = { "DMC1982", "BAT1234", "DB51964", "FER1961", "MUS1968" };
    BYTE* makes[] = { "DeLorean", "Wayne Enterprises", "Aston Martin", "Ferrari", "Ford" };
    BYTE* models[] = { "DMC-12", "Batmobile", "DB5", "250 GT California", "Mustang GT Fastback" };
    BYTE* descriptions[] = {
        "The iconic car from Back to the Future.",
        "The Dark Knight's ride.",
        "James Bond's stylish car in Goldfinger.",
        "Ferris Bueller's day off car.",
        "Steve McQueen's car in Bullitt."
    };

    // Create and add initial vehicle
    Vehicle* myVehicle = createVehicle(vin1, make1, model1, description1);
    addVehicleToGarage(&g, myVehicle);

    // Create and add famous cars
    for (int i = 0; i < 5; ++i) {
        Vehicle* vehicle = createVehicle(vins[i], makes[i], models[i], descriptions[i]);
        addVehicleToGarage(&g, vehicle);
    }

    // Display all vehicles in the garage
    displayGarage(g);
}

int main() {

    testCreateAndDisplayVehicle();

    return 0;

}
