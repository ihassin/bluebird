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
void service_remove(Service *theService);

#endif /* SERVICE_H */

