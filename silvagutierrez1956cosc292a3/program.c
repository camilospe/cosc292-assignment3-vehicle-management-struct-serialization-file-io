#include <stdio.h>
#include "structs.h"
#include "fileio.h"
#define MAX_DESCRIPTION	255
#define BUFFERSIZE 57



/// <summary>
/// This test will create multiple vehicles and add them to a garage. then it will display the values
/// </summary>
void testCreateAndDisplayGarage()
{
    printf("testCreateAndDisplayGarage------------\n\n");

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

    // Create and add famous cars
    for (int i = 0; i < 5; ++i) {
        Vehicle* vehicle = createVehicle(vins[i], makes[i], models[i], descriptions[i]);
        addVehicleToGarage(&g, vehicle);
    }

    // Display all vehicles in the garage
    displayGarage(g);
    
}

/// <summary>
/// This test will write a garage to a file and read it.
/// </summary>
/// <returns></returns>
int testWriteGarageToFileAndread()
{

    printf("testWriteGarageToFileAndread------------\n\n");
    Garage g = { NULL, 0 };

    const char* filePath = "cars.txt";

    FILE* printfl = openFile(filePath, "wb");

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

    // Create and add famous cars
    for (int i = 0; i < 5; ++i) {
        Vehicle* vehicle = createVehicle(vins[i], makes[i], models[i], descriptions[i]);
        addVehicleToGarage(&g, vehicle);
    }

    writeGarageToFile(g, printfl);
    
    fclose(printfl);

    FILE* readfl = openFile("cars.txt", "rb");

    Garage g2 = { NULL, 0 };

    readGarageFromFile(&g2, readfl);

    if (g2.NumVehicles != 5)
    {
        printf("Incorrect number of vehicles\n");
        return -1;
    }
    else
    {
        printf("correct number of vehicles on read file\n");
    }


    for (int v = 0; v < g.NumVehicles; v++)
    {
        printf("written/read\n");
        
        printf("%s / %s\n", g.Vehicles[v]->VIN, g2.Vehicles[v]->VIN);
        printf("%s / %s\n", g.Vehicles[v]->Make, g2.Vehicles[v]->Make);
        printf("%s / %s\n", g.Vehicles[v]->Model, g2.Vehicles[v]->Model);
        printf("%s / %s\n\n", g.Vehicles[v]->Description, g2.Vehicles[v]->Description);

    }
    return 0;
}


//This test will create a vehicle and display the values 
void testCreateAndDisplayVehicle() {
    printf("testCreateAndDisplayVehicle------------\n\n");

    // Initial car for setup
    BYTE vin1[] = "1234567";
    BYTE make1[] = "Toyota";
    BYTE model1[] = "Corolla";
    BYTE description1[] = "A specific car.";

    Vehicle* myVehicle = createVehicle(vin1, make1, model1, description1);
    printf("vehicle description: %s\n", myVehicle->Description);
    printf("vehicle vin: %s\n", myVehicle->VIN);
    printf("vehicle make: %s\n", myVehicle->Make);
    printf("vehicle model: %s\n\n", myVehicle->Model);
    
    displayVehicle(*myVehicle);

    free(myVehicle);
}



/// <summary>
/// This test will create a file and will put regular content in it
/// </summary>
/// <returns></returns>
int testOpenAndWriteFile()
{
    printf("testOpenAndWriteFile------------\n\n");

    const char* filePath = "example.txt";
    const char* content = "Hello, this is a test file. this is so much test to read";
    int contentSize = strlen(content) + 1; // +1 for the null terminator

    FILE* file = openFile(filePath, "wb");

    if (!file) {
        printf("Failed to open file for writing.\n");
        return -2;
    }

    int writeReturn = writeFile(file, content, contentSize);

    switch (writeReturn)
    {
    case -1:
        printf("Data wasnt written successfully \n");
        return -1;
    case 1:
        printf("Error writing to file\n");
        return 1;
    case 2:
        printf("Error when writing to file\n");
        return 2;
    default:
        printf("File written successfully\n");
        break;
    }

    fclose(file);
    printf("File successfully openened, modified, and closed\n\n");

    return 0; // Success
}

/// <summary>
/// This test will open and read a file. If there is an error it will provide the appropiate message
/// </summary>
/// <returns></returns>
int testOpenAndReadFile()
{
    printf("testOpenAndReadFile------------\n\n");

    const char* filePath = "example.txt";

    FILE* file = openFile(filePath, "rb");

    if (!file) {
        printf("Failed to open file for reading.\n");
        return -1;
    }

    BYTE buffer[BUFFERSIZE];

    int readReturn = readFile(file, buffer, BUFFERSIZE);

    switch (readReturn)
    {
    case -1:
        printf("File or data are null \n");
        return 1;
    case 1:
        printf("Error reading file\n");
        return 2;
    case 2:
        printf("End of file reached before the data was saved successfully\n");
        return 3;
    default:
        printf("File read successfully\n");
        break;
    }
    printf("File Contents: %s\n", buffer);

    fclose(file);

    printf("File read and closed successfully \n\n");

    return 0;
}


int main() {

    testCreateAndDisplayVehicle();

    testCreateAndDisplayGarage();

    testOpenAndWriteFile();

    testOpenAndReadFile();

    testWriteGarageToFileAndread();

    return 0;

}
