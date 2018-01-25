#ifndef __SERVICE_H__
#define __SERVICE_H__

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

#endif

