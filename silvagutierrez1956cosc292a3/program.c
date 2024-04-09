#include <stdio.h>
#include "structs.h"

void testCreateAndDisplayVehicle()
{
    BYTE vin[] = "12345678901234567";
    BYTE make[] = "Toyota";
    BYTE model[] = "Corolla";
    BYTE description[] = "A reliable family car.";

    Vehicle* myVehicle = createVehicle(vin, make, model, description);


    displayVehicle(*myVehicle);

    Garage g = { NULL, 0 };

    addVehicleToGarage(&g, myVehicle);

    displayGarage(g);

}



int main() {

    testCreateAndDisplayVehicle();

    return 0;




}
