#ifndef __PERIPHERAL_H__
#define __PERIPHERAL_H__

#ifndef __SERVICE_H__
#include "service.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

typedef struct Peripheral
{
    int id;
} Peripheral;

Peripheral *peripheral_create();
void peripheral_destroy(Peripheral *thePeripheral);

int peripheral_add_service(Service *theService);

#endif
