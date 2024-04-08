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
}



int main() {

    testCreateAndDisplayVehicle();

    return 0;




}
