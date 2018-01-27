#ifndef __UNITY_TESTS_H__
#define __UNITY_TESTS_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#ifndef UNITY_FRAMEWORK_H
#include "../unity/src/unity.h"
#endif

#ifndef __SERVICE_H__
#include "../service.h"
#endif

#ifndef __PERIPHERAL_H__
#include "../peripheral.h"
#endif

#ifndef __CHARACTERISTIC_H__
#include "../characteristic.h"
#endif

void test_canary(void);

/*
 Service tests
 */
void test_service_creation(void);
void test_service_init(void);
void test_service_add_characteristic(void);

/*
 Peripheral tests
 */
void test_peripheral_creation(void);
void test_peripheral_init(void);
void test_peripheral_add_service(void);

/*
 Characteristic tests
 */
void test_characteristic_creation(void);
void test_characteristic_init(void);

/*
 HCI tests
 */
void test_hci(void);

#endif
