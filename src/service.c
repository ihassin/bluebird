#include "malloc.h"

#ifndef __SERVICE_H__
#include "service.h"
#endif

Service *service_create()
{
    Service *service = malloc(sizeof(Service));
    service->id = -1;
    
    return(service);
}

void service_destroy(Service *theService)
{
    free(theService);
}

int service_add_characteristic(Service *theService, Characteristic *theCharacteristic)
{
    return(0);
}
