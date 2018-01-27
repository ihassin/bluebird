#ifndef __UNITY_TESTS_H__
#include "unity-tests.h"
#endif

void test_hci(void)
{
    int dev_id;
    int sock;

    dev_id = hci_get_route(NULL);
    sock = hci_open_dev(dev_id);
    if ((dev_id < 0) || (sock < 0)) {
        TEST_FAIL_MESSAGE("Cannot open socket");
    }
    close(sock);
    TEST_ASSERT_GREATER_THAN_INT(0, sock);
}
