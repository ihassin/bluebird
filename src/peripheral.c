#include "malloc.h"

#ifndef __PERIPHERAL_H__
#include "peripheral.h"
#endif

Peripheral *peripheral_create()
{
    Peripheral *peripheral = malloc(sizeof(Peripheral));
    peripheral->id = -1;

    return(peripheral);
}
void peripheral_remove(Peripheral *peripheral)
{
    free(peripheral);
}
