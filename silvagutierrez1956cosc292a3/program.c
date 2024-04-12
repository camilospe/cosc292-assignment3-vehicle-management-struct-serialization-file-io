#include <stdio.h>
#include "structs.h"
#include "fileio.h"
#define MAX_DESCRIPTION	255
#define BUFFERSIZE 57

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

    const char* filePath = "cars.txt";

    FILE* printfl = openFile(filePath, "wb");

    writeGarageToFile(g, printfl);

    FILE* printfl2 = openFile("cars2.txt", "rb");

    readGarageFromFile(&g, printfl2);
}
// Function to write predefined content to a new file
int createFileWithContent(const char* filePath, const BYTE* content, int contentSize) {
    FILE* file = openFile(filePath, "wb");
    if (!file) {
        printf("Failed to open file for writing.\n");
        return -1;
    }

    if (writeFile(file, content, contentSize) != 0) {
        printf("Failed to write to file.\n");
        fclose(file);
        return -1;
    }

    fclose(file);
    return 0; // Success
}

// Function to read a file and print its contents
int printFileContents(const char* filePath) {
    BYTE buffer[BUFFERSIZE];
    FILE* file = openFile(filePath, "rb");
    if (!file) {
        printf("Failed to open file for reading.\n");
        return -1;
    }

    if (readFile(file, buffer, BUFFERSIZE) != 0) {
        printf("Failed to read file.\n");
        fclose(file);
        return -1;
    }

    // Assuming the content is text for demonstration purposes
    printf("File Contents: %s\n", buffer);
    fclose(file);
    return 0;
}

int main() {
    const char* filePath = "example.txt";
    const char* content = "Hello, this is a test file. this is so much test to read";
    int contentSize = strlen(content) + 1; // +1 for the null terminator

    // Create a file and write predefined content to it
    if (createFileWithContent(filePath, (BYTE*)content, contentSize) == 0) {
        printf("File created successfully.\n");
    }
    else {
        printf("Failed to create file.\n");
        return -1;
    }

    // Read the newly created file and print its contents
    if (printFileContents(filePath) == 0) {
        printf("File read successfully.\n");
    }
    else {
        printf("Failed to read file.\n");
    }

    testCreateAndDisplayVehicle();

    return 0;

}
