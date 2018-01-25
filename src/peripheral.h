#ifndef __PERIPHERAL_H__
#define __PERIPHERAL_H__

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
void peripheral_remove(Peripheral *peripheral);

#endif /* PERIPHERAL_H */

