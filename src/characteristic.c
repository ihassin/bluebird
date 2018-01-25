#include "malloc.h"

#ifndef __CHARACTERISTIC_H__
#include "characteristic.h"
#endif

Characteristic *characteristic_create()
{
    Characteristic *characteristic = malloc(sizeof(Characteristic));
    characteristic->id = -1;

    return(characteristic);
}

void characteristic_destroy(Characteristic *theCharacteristic)
{
    free(theCharacteristic);
}
