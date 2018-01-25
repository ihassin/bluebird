#ifndef __CHARACTERISTIC_H__
#define __CHARACTERISTIC_H__

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

typedef struct Characteristic
{
    int id;
} Characteristic;

Characteristic *characteristic_create();
void characteristic_destroy(Characteristic *theCharacteritic);

#endif
