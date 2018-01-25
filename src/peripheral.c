#include "malloc.h"

#ifndef __PERIPHERAL_H__
#include "peripheral.h"
#endif

#ifndef __SERVICE_H__
#include "service.h"
#endif

Peripheral *peripheral_create()
{
    Peripheral *peripheral = malloc(sizeof(Peripheral));
    peripheral->id = -1;

    return(peripheral);
}

void peripheral_destroy(Peripheral *thePeripheral)
{
    free(thePeripheral);
}

int peripheral_add_service(Service *theService)
{
    return(0);
}
