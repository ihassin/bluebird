#ifndef __SERVICE_H__
#define __SERVICE_H__

#ifndef __CHARACTERISTIC_H__
#include "characteristic.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

typedef struct Service {
    int id;
} Service;

Service *service_create();
void service_destroy(Service *theService);

int service_add_characteristic(Service *theService, Characteristic *theCharacteristic);

#endif
